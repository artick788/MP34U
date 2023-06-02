#include "MP3File.hpp"

namespace mp34u{

    MP3File::MP3File(const std::string &path):
    MusicFile(MusicFileType::MP3),
    m_Path(path),
    m_ID3FrameHeader(nullptr),
    m_FrameCount(0){
        std::ifstream file(path, std::ios::binary);
        if(!file){
            throw std::runtime_error("Failed to open file: " + path);
        }

        if(!readID3Tag(file)){
            throw std::runtime_error("Failed to read ID3 version from file: " + path + " (ID3 header not found)");
        }
        // now we can read the frames, store the header as a linked list
        readHeader(file);
        parseHeader();
    }

    MP3File::~MP3File() {

    }

    void MP3File::save(const std::string &path) {

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

    void MP3File::readHeader(std::ifstream &file) {
        int32_t increment = 10; // frame header is 10 bytes
        ID3FrameHeader* current = nullptr;
        for (uint32_t i = 10; i < m_ID3v24Header.size; i += increment){
            char frameID[4];
            file.seekg(i, std::ios::beg);
            file.read(frameID, 4);
            char fSize[4];
            file.seekg(i + 4, std::ios::beg);
            file.read(fSize, 4);
            char fFlags[2];
            file.seekg(i + 8, std::ios::beg);
            file.read(fFlags, 2);
            auto frameSize = static_cast<int32_t>(fSize[0] << 24 | fSize[1] << 16 | fSize[2] << 8 | fSize[3]);
            auto flags = static_cast<int16_t>(fFlags[0] << 8 | fFlags[1]);
            file.seekg(i + 10, std::ios::beg); // skip the header
            if (current){
                current = current->setNext(frameID, frameSize, flags, file);
            }
            else{
                m_ID3FrameHeader = std::make_unique<ID3FrameHeader>(frameID, frameSize, flags, file);
                current = m_ID3FrameHeader.get();
            }
            increment = frameSize + 10;
            m_FrameCount++;
        }
    }

    void MP3File::parseHeader() {
        m_Title = m_ID3FrameHeader->search("TIT2");
        m_Artist = m_ID3FrameHeader->search("TPE1");
        m_Album = m_ID3FrameHeader->search("TALB");
        m_Year = m_ID3FrameHeader->search("TYER");
        m_Comment = m_ID3FrameHeader->search("COMM");
        m_Genre = m_ID3FrameHeader->search("TCON");
        m_Key = m_ID3FrameHeader->search("TKEY");
        m_BPM = std::stoi(m_ID3FrameHeader->search("TBPM"));



    }
}
