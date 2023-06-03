#include "ID3FrameHeader.hpp"

namespace mp34u{

    ID3FrameHeader::ID3FrameHeader(const char *ID, int32_t size, int16_t flags, std::ifstream& file):
    m_Size(size), m_Flags(flags), m_Next(nullptr){
        m_ID = std::string(ID, 4);
        m_Data = std::make_unique<char[]>(size);
        file.read(m_Data.get(), size);
    }

    ID3FrameHeader::ID3FrameHeader(const char *ID, int32_t size, int16_t flags, std::unique_ptr<char[]> &data):
    m_Size(size), m_Flags(flags), m_Next(nullptr){
        m_ID = std::string(ID, 4);
        m_Data = std::make_unique<char[]>(size);
        memcpy(m_Data.get(), data.get(), size);

    }

    ID3FrameHeader::~ID3FrameHeader() {

    }

    const std::string& ID3FrameHeader::getID() const {
        return m_ID;
    }

    int32_t ID3FrameHeader::getSize() const {
        return m_Size;
    }

    int16_t ID3FrameHeader::getFlags() const {
        return m_Flags;
    }

    const std::unique_ptr<ID3FrameHeader>& ID3FrameHeader::getNext() const {
        return m_Next;
    }

    const std::unique_ptr<char[]>& ID3FrameHeader::getData() const {
        return m_Data;
    }

    ID3FrameHeader* ID3FrameHeader::search(const std::string &ID) {
        if (ID == m_ID){
            return this;
        }
        if (m_Next){
            return m_Next->search(ID);
        }
        return nullptr;
    }

    void ID3FrameHeader::setData(char *buf, int32_t size) {
        m_Data = std::make_unique<char[]>(size);
        memcpy(m_Data.get(), buf, size);
        m_Size = size;
    }

    uint32_t ID3FrameHeader::getFrameSize() const {
        if (m_Next == nullptr){
            return m_Size + 10;
        }
        return m_Size + 10 + m_Next->getFrameSize();
    }

    void ID3FrameHeader::write(std::ofstream &file) {
        file.write(m_ID.c_str(), 4);
        file.write(reinterpret_cast<char*>(&m_Size), 4);
        file.write(reinterpret_cast<char*>(&m_Flags), 2);
        file.write(m_Data.get(), m_Size);
        if (m_Next){
            m_Next->write(file);
        }

    }
}

