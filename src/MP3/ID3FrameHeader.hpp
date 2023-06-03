#pragma once

#include <string>
#include <memory>
#include <fstream>
#include <string>

namespace mp34u{

    class ID3FrameHeader{
    public:
        ID3FrameHeader(const char* ID, int32_t size, int16_t flags, std::ifstream& file);

        ID3FrameHeader(const char* ID, int32_t size, int16_t flags, std::unique_ptr<char[]>& data);

        ~ID3FrameHeader();

        template<typename... Args>
        ID3FrameHeader* setNext(Args&&... args){
            m_Next = std::make_unique<ID3FrameHeader>(std::forward<Args>(args)...);
            return m_Next.get();
        }

        ID3FrameHeader* search(const std::string& ID);

        [[nodiscard]] const std::string& getID() const;

        [[nodiscard]] int32_t getSize() const;

        [[nodiscard]] int16_t getFlags() const;

        [[nodiscard]] const std::unique_ptr<ID3FrameHeader>& getNext() const;

        [[nodiscard]] const std::unique_ptr<char[]>& getData() const;

        void setData(char* buf, int32_t size);

        uint32_t getFrameSize() const;

        void write(std::ofstream& file);

    private:
        std::string m_ID;
        int32_t m_Size;
        int16_t m_Flags;
        std::unique_ptr<ID3FrameHeader> m_Next;
        std::unique_ptr<char[]> m_Data;

    };

}