#include "ID3Frame.hpp"

namespace mp34u{

    ID3Frame::ID3Frame(std::string id, int32_t size, int16_t flags, std::ifstream& file):
    m_ID(std::move(id)), m_FrameDataSize(size), m_Flags(flags){
        m_Data = std::make_unique<char[]>(m_FrameDataSize);
        file.read(m_Data.get(), m_FrameDataSize);
    }

    ID3Frame::ID3Frame(std::string id, const std::string &value):
    m_ID(std::move(id)), m_FrameDataSize(value.size() + 1), m_Flags(0){
        setValue(value);
    }

    ID3Frame::~ID3Frame() {

    }

    const std::string &ID3Frame::getID() const {
        return m_ID;
    }

    int32_t ID3Frame::getFrameSize() const {
        return m_FrameDataSize + 10;
    }

    int32_t ID3Frame::getFrameDataSize() const {
        return m_FrameDataSize;
    }

    int16_t ID3Frame::getFlags() const {
        return m_Flags;
    }

    const std::unique_ptr<ID3Frame> &ID3Frame::getNext() const {
        return m_Next;
    }

    ID3Frame *ID3Frame::searchFrame(const std::string &id) {
        if (id == m_ID){
            return this;
        }
        else{
            if (m_Next){
                return m_Next->searchFrame(id);
            }
            return nullptr;
        }
    }

    std::string ID3Frame::getValue() {
        auto pData = m_Data.get() + m_FrameDataSize - 1;
        std::string retVal;
        uint32_t i = 0;
        // data is stored in reverse order (little endian), so we have to scan backwards until we find a null terminator
        // ETX symbol
        while (*pData != '\0' and *pData != '\03'){ // ASCII 0x03 is ETX (End of Text)
            retVal += *pData--;
            i++;
            if (i == m_FrameDataSize){ // if the file should be corrupted, we don't want to get stuck in an infinite loop
                break;
            }
        }
        std::reverse(retVal.begin(), retVal.end());
        return retVal;
    }

    void ID3Frame::setValue(const std::string &value) {
        m_FrameDataSize = value.size() + 1; // +1 for null terminator
        m_Data = std::make_unique<char[]>(m_FrameDataSize);
        m_Data[0] = '\03'; // ASCII 0x03 is ETX (End of Text)
        std::copy(value.begin(), value.end(), m_Data.get() + 1);
    }

    void ID3Frame::save(std::ofstream &file) {
        char header[10];
        std::copy(m_ID.begin(), m_ID.end(), header);
        header[4] = static_cast<char>((m_FrameDataSize >> 24) & 0xFF);
        header[5] = static_cast<char>((m_FrameDataSize >> 16) & 0xFF);
        header[6] = static_cast<char>((m_FrameDataSize >> 8) & 0xFF);
        header[7] = static_cast<char>(m_FrameDataSize & 0xFF);
        header[8] = static_cast<char>((m_Flags >> 8) & 0xFF);
        header[9] = static_cast<char>(m_Flags & 0xFF);
        file.write(header, 10);

        file.write(m_Data.get(), m_FrameDataSize);
        if (m_Next){
            m_Next->save(file);
        }
    }
}