#include "MP3File.hpp"

namespace mp34u{

    MP3File::MP3File(const std::string &path):
    MusicFile(MusicFileType::MP3),
    m_Path(path),
    m_ID3FrameHeader(nullptr),
    m_FrameCount(0),
    m_FileSize(0),
    m_DataSize(0),
    m_CurrHeader(nullptr){
        std::ifstream file(path, std::ios::binary);
        // get the file size
        file.seekg(0, std::ios::end);
        m_FileSize = static_cast<uint32_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        if(!file){
            throw std::runtime_error("Failed to open file: " + path);
        }

        if(!readID3Tag(file)){
            throw std::runtime_error("Failed to read ID3 version from file: " + path + " (ID3 header not found)");
        }
        // now we can read the frames, store the header as a linked list
        readMetaDataHeader(file);
        parseMetaData();
        file.close();
    }

    MP3File::~MP3File() {

    }

    void MP3File::save(const std::string &path) {
        updateMetaDataHeader();
        auto frameSize = m_ID3FrameHeader->getFrameSize();
        std::ofstream file(path, std::ios::binary);
        file.write(m_ID3v24Header.ID, 3);
        file.write(reinterpret_cast<char*>(&m_ID3v24Header.version), 1);
        file.write(reinterpret_cast<char*>(&m_ID3v24Header.revision), 1);
        file.write(reinterpret_cast<char*>(&m_ID3v24Header.flags), 1);
        file.write(reinterpret_cast<char*>(&frameSize), 4);
        m_ID3FrameHeader->write(file);
        file.write(m_Data.get(), m_DataSize);
        file.close();
    }

    void MP3File::updateMetaDataHeader() {
        setValue("TIT2", m_Title);
        setValue("TPE1", m_Artist);
        setValue("TALB", m_Album);
        setValue("TCON", m_Genre);
        setValue("TYER", std::to_string(m_Year));
        setValue("COMM", m_Comment);
        setValue("TKEY", m_Key);
        setValue("TBPM", std::to_string(m_BPM));
    }

    bool MP3File::readID3Tag(std::ifstream &file) {
        // first 10 bytes of the file are the ID3 header
        file.seekg(0, std::ios::beg);
        char header[10];
        file.read(header, 10);
        if(header[0] == 'I' && header[1] == 'D' && header[2] == '3') {
            // we have an ID3 tag
            m_ID3v24Header.ID[0] = header[0];
            m_ID3v24Header.ID[1] = header[1];
            m_ID3v24Header.ID[2] = header[2];
            // set rest of info
            m_ID3v24Header.version = static_cast<int8_t>(header[3]); // byte 4 is the ID3 version
            m_ID3v24Header.revision = static_cast<int8_t>(header[4]); // byte 5 is the ID3 revision
            m_ID3v24Header.flags = static_cast<int8_t>(header[5]); // byte 6 is the ID3 flags
            m_ID3v24Header.size = static_cast<int32_t>(header[6] << 21 | header[7] << 14 | header[8] << 7 | header[9]); // bytes 7-10 are the tag size
            return true;
        }
        return false;
    }

    void MP3File::readMetaDataHeader(std::ifstream &file) {
        int32_t increment = 10; // frame header is 10 bytes
        uint32_t pos = 10;
        for (pos = 10; pos < m_ID3v24Header.size; pos += increment){
            char frameID[4];
            file.seekg(pos, std::ios::beg);
            file.read(frameID, 4);
            char fSize[4];
            file.seekg(pos + 4, std::ios::beg);
            file.read(fSize, 4);
            char fFlags[2];
            file.seekg(pos + 8, std::ios::beg);
            file.read(fFlags, 2);
            auto frameSize = static_cast<int32_t>(fSize[0] << 24 | fSize[1] << 16 | fSize[2] << 8 | fSize[3]);
            auto flags = static_cast<int16_t>(fFlags[0] << 8 | fFlags[1]);
            file.seekg(pos + 10, std::ios::beg); // skip the header
            if (m_CurrHeader){
                m_CurrHeader = m_CurrHeader->setNext(frameID, frameSize, flags, file);
            }
            else{
                m_ID3FrameHeader = std::make_unique<ID3FrameHeader>(frameID, frameSize, flags, file);
                m_CurrHeader = m_ID3FrameHeader.get();
            }
            increment = frameSize + 10;
            m_FrameCount++;
        }

        // now store the rest of the data
        m_DataSize = m_FileSize - m_ID3v24Header.size;
        m_Data = std::make_unique<char[]>(m_DataSize);
        file.read(m_Data.get(), m_FileSize - m_ID3v24Header.size);
    }

    void MP3File::parseMetaData() {
        auto retrieveStringValue = [this](const std::string& key, std::string& buffer){
            auto frame = m_ID3FrameHeader->search(key);
            if (frame){
                // data is stored as little endian, so we read from the end of the data
                auto ptr = frame->getData().get() + frame->getSize() - 1;
                while (*ptr != '\0'){
                    buffer += *ptr;
                    ptr--;
                }
                // convert to big endian
                std::reverse(buffer.begin(), buffer.end());
            }
        };
        auto retrieveIntValue = [retrieveStringValue](const std::string& key, int32_t& buffer){
            std::string buf;
            retrieveStringValue(key, buf);
            if (!buf.empty()){
                buffer = std::stoi(buf);
            }
        };
        retrieveStringValue("TIT2", m_Title);
        retrieveStringValue("TPE1", m_Artist);
        retrieveStringValue("TALB", m_Album);
        retrieveIntValue("TYER", m_Year);
        retrieveStringValue("COMM", m_Comment);
        retrieveStringValue("TCON", m_Genre);
        retrieveStringValue("TKEY", m_Key);
        retrieveIntValue("TBPM", m_BPM);
    }

    void MP3File::setValue(const std::string &frameID, const std::string &value) {
        if (value.empty()){
            return;
        }
        // first format the buffer correctly
        auto ptr = std::make_unique<char[]>(value.size() + 1);
        ptr[0] = '\0';
        for (int32_t i = 0; i < value.size(); i++){
            ptr[i + 1] = value[i];
        }
        // check if the frame exists
        auto frame = m_ID3FrameHeader->search(frameID);
        if (frame){
            frame->setData(ptr.get(), value.size() + 1);
        }
        else{
            m_CurrHeader = m_CurrHeader->setNext(frameID.c_str(), value.size() + 1, 0, ptr);
        }


    }
}
