#include "MP3File.hpp"

namespace mp34u{

    MP3File::MP3File(const std::string &path):
    MusicFile(MusicFileType::MP3),
    m_Path(path),
    m_FileSize(0),
    m_DataSize(0){
        std::ifstream file(path, std::ios::binary);
        if(!file){
            throw std::runtime_error("Failed to open file: " + path);
        }

        // get the file frameSize
        file.seekg(0, std::ios::end);
        m_FileSize = static_cast<uint32_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        // read the ID3 tag
        m_ID3Tag = createUP<ID3Tag>(file);

        retrieveTagInfo();

        // read the data
        m_DataSize = m_FileSize - m_ID3Tag->getTagSize();
        m_Data = createUP<char[]>(m_DataSize);
        file.read(m_Data.get(), m_DataSize);

        file.close();
    }

    MP3File::~MP3File() {

    }

    void MP3File::save(const std::string &path) {
        updateTag();

        std::ofstream file(path, std::ios::binary);
        m_ID3Tag->save(file);
        file.write(m_Data.get(), m_DataSize);
    }

    void MP3File::updateTag() {
        m_ID3Tag->setValue("TIT2", m_Title);
        m_ID3Tag->setValue("TPE1", m_Artist);
        m_ID3Tag->setValue("TALB", m_Album);
        m_ID3Tag->setValue("TYER", m_Year);
        m_ID3Tag->setValue("COMM", m_Comment);
        m_ID3Tag->setValue("TCON", m_Genre);
        m_ID3Tag->setValue("TKEY", m_Key);
        m_ID3Tag->setValue("TBPM", m_BPM);
    }

    void MP3File::retrieveTagInfo() {
        m_Title = m_ID3Tag->getValue("TIT2");
        m_Artist = m_ID3Tag->getValue("TPE1");
        m_Album = m_ID3Tag->getValue("TALB");
        m_Year = m_ID3Tag->getValue("TYER");
        m_Comment = m_ID3Tag->getValue("COMM");
        m_Genre = m_ID3Tag->getValue("TCON");
        m_Key = m_ID3Tag->getValue("TKEY");
        m_BPM = m_ID3Tag->getValue("TBPM");
    }

}
