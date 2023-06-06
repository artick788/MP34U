#pragma once

#include "../Utils.hpp"

namespace mp34u{

    class ID3Frame{
    public:
        ID3Frame(std::string id, int32_t size, int16_t flags, std::ifstream& file);

        ID3Frame(std::string id, const std::string& value);

        ~ID3Frame();

        template<typename... Args>
        ID3Frame* setNext(Args&&... args){
            m_Next = std::make_unique<ID3Frame>(std::forward<Args>(args)...);
            return m_Next.get();
        }

        [[nodiscard]] const std::string& getID() const;

        [[nodiscard]] int32_t getFrameSize() const;

        [[nodiscard]] int32_t getFrameDataSize() const;

        [[nodiscard]] int16_t getFlags() const;

        [[nodiscard]] const std::unique_ptr<ID3Frame>& getNext() const;

        ID3Frame* searchFrame(const std::string& id);

        std::string getValue();

        void setValue(const std::string& value);

        void save(std::ofstream& file);

    private:
        // frame header
        std::string m_ID;
        int32_t m_FrameDataSize;
        int16_t m_Flags;

        // frame data
        UP<char[]> m_Data;

        // next frame
        UP<ID3Frame> m_Next;
    };
}