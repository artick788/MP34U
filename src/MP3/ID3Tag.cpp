#include "ID3Tag.hpp"

namespace mp34u{

    static std::unordered_set<std::string> s_KnownID3v24Tags = {
            "APIC", "COMM", "COMR", "ENCR", "EQU2", "ETCO", "GEOB", "GRID", "LINK", "MCDI", "MLLT", "OWNE", "PRIV",
            "PCNT", "POPM", "POSS", "RBUF", "RVAD", "RVRB", "SYLT", "SYTC", "TALB", "TBPM", "TCOM", "TCON", "TCOP",
            "TDAT", "TDLY", "TENC", "TEXT", "TFLT", "TIME", "TIT1", "TIT2", "TIT3", "TKEY", "TLAN", "TLEN", "TMED",
            "TOAL", "TOFN", "TOLY", "TOPE", "TORY", "TOWN", "TPE1", "TPE2", "TPE3", "TPE4", "TPOS", "TPUB", "TRCK",
            "TRDA", "TRSN", "TRSO", "TSIZ", "TSRC", "TSSE", "TYER", "TXXX", "UFID", "USER", "USLT", "WCOM", "WCOP",
            "WOAF", "WOAR", "WOAS", "WORS", "WPAY", "WPUB", "WXXX"
    };

    ID3Tag::ID3Tag(std::ifstream &file):
    m_Version(0),
    m_Revision(0),
    m_Flags(0),
    m_TagSize(0),
    m_Data(nullptr),
    m_LastFrame(nullptr),
    m_FrameCount(0){
        readTagHeader(file);
        readTagData(file);

    }

    ID3Tag::~ID3Tag() {

    }

    uint8_t ID3Tag::getVersion() const {
        return m_Version;
    }

    uint8_t ID3Tag::getRevision() const {
        return m_Revision;
    }

    uint8_t ID3Tag::getFlags() const {
        return m_Flags;
    }

    int32_t ID3Tag::getTagSize() const {
        return m_TagSize;
    }

    std::string ID3Tag::getValue(const std::string &id) {
        auto frame = m_Data->searchFrame(id);
        if (frame){
            return frame->getValue();
        }
        return "";
    }

    void ID3Tag::setValue(const std::string &id, const std::string &value) {
        if (value.empty()){
            return;
        }
        auto frame = m_Data->searchFrame(id);
        if (frame){
            frame->setValue(value);
        }
        else{
            // check if there is enough padding space, should almost never occur but just in case
            if (m_TagSize < getTagDataSize() + value.size() + 1){
                m_TagSize += value.size() + 1;
            }
            m_LastFrame = m_LastFrame->setNext(id, value);
            m_FrameCount++;
        }
    }

    int32_t ID3Tag::getTagDataSize() {
        auto pFrame = m_Data.get();
        int32_t size = 0;
        while (pFrame){
            size += pFrame->getFrameSize();
            pFrame = pFrame->getNext().get();
        }
        return size;
    }

    void ID3Tag::save(std::ofstream &file) {
        char header[] = {'I', 'D', '3', m_Version, m_Revision, m_Flags, 0, 0, 0, 0};
        header[6] =  static_cast<char>((m_TagSize >> 24) & 0xFF);
        header[7] = static_cast<char>((m_TagSize >> 16) & 0xFF);
        header[8] = static_cast<char>((m_TagSize >> 8) & 0xFF);
        header[9] = static_cast<char>(m_TagSize & 0xFF);
        file.write(header, 10);

        m_Data->save(file);

        for (uint32_t i = getTagDataSize(); i < m_TagSize; i++){
            file.write("\0", 1);
        }
    }

    void ID3Tag::readTagHeader(std::ifstream &file) {
        file.seekg(0, std::ios::beg);
        char buffer[10];
        file.read(buffer, 10);     // Must be "ID3"
        if (buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != '3'){
            throw std::runtime_error("Invalid ID3 tag");
        }
        m_Version = buffer[3];    // Version
        if (m_Version != 3 && m_Version != 4){
            throw std::runtime_error("Invalid ID3 version");
        }
        if (m_Version == 3){
            printf("ID3v2.3 support can cause issues, please use ID3v2.4\n");
        }
        m_Revision = buffer[4];   // Revision
        m_Flags = buffer[5];      // Flags
        m_TagSize = buffer[6] << 24 | buffer[7] << 16 | buffer[8] << 8 | buffer[9]; // Tag size
    }

    void ID3Tag::readTagData(std::ifstream &file) {
        uint32_t pos = 10;
        while (pos < m_TagSize){
            file.seekg(pos, std::ios::beg);
            char buffer[10];
            file.read(buffer, 10);
            std::string id(buffer, 4);
            uint32_t size = buffer[4] << 24 | buffer[5] << 16 | buffer[6] << 8 | buffer[7];
            uint16_t flags = buffer[8] << 8 | buffer[9];
            pos += 10;
            if (s_KnownID3v24Tags.find(id) == s_KnownID3v24Tags.end()){
                printf("Unknown ID3v2.4 tag: %s\n", id.c_str());
                break;
            }
            if (m_Data){
                m_LastFrame = m_LastFrame->setNext(id, size, flags, file);
            }
            else{
                m_Data = std::make_unique<ID3Frame>(id, size, flags, file);
                m_LastFrame = m_Data.get();
            }
            pos += size;
            m_FrameCount++;
        }

    }

}
