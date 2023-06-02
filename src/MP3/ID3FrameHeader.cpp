#include "ID3FrameHeader.hpp"

namespace mp34u{

    ID3FrameHeader::ID3FrameHeader(char *ID, int32_t size, int16_t flags, std::ifstream& file):
    m_Size(size), m_Flags(flags), m_Next(nullptr){
        m_ID = std::string(ID, 4);
        m_Data = std::make_unique<char[]>(size);
        file.read(m_Data.get(), size);
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

    std::string ID3FrameHeader::search(const std::string &ID) {
        if (ID == m_ID){
            if (m_Data[0] == 0x00){
                return std::string(m_Data.get() + 1, m_Size - 1);
            }
            else if (m_Data[0] == 0x03){
                return std::string(m_Data.get() + 1, m_Size - 1);
            }
            else{
                return std::string(m_Data.get(), m_Size);
            }
        }
        else{
            if (m_Next){
                return m_Next->search(ID);
            }
            else{
                return "Unknown";
            }
        }
    }
}

