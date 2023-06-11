#pragma once

#include "../Utils.hpp"
#include "ID3Frame.hpp"

namespace mp34u{

    class ID3Tag{
    public:
        explicit ID3Tag(std::ifstream& file);

        ~ID3Tag();

        [[nodiscard]] uint8_t getVersion() const;

        [[nodiscard]] uint8_t getRevision() const;

        [[nodiscard]] uint8_t getFlags() const;

        [[nodiscard]] int32_t getTagSize() const;

        std::string getValue(const std::string& id);

        void setValue(const std::string& id, const std::string& value);

        [[nodiscard]] int32_t getTagDataSize();

        void save(std::ofstream& file);

    private:

        void readTagHeader(std::ifstream& file);

        void readTagData(std::ifstream& file);

    private:
        // tag header
        int8_t m_Version;
        int8_t m_Revision;
        int8_t m_Flags;
        int32_t m_TagSize; // with padding

        // tag data
        UP<ID3Frame> m_Data;
        ID3Frame* m_LastFrame;

        // Utils
        uint32_t m_FrameCount;
    };

}

