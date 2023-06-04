#pragma once

#include "../MusicFile.hpp"
#include "ID3Tag.hpp"

namespace mp34u{

    class MP3File: public MusicFile{
    public:
        explicit MP3File(const std::string& path);

        ~MP3File() override;

        void save(const std::string& path) override;

        void updateTag();

    private:

        void retrieveTagInfo();

    private:
        std::string m_Path;
        std::unique_ptr<ID3Tag> m_ID3Tag;


        uint32_t m_FileSize;
        uint32_t m_DataSize;

        std::unique_ptr<char[]> m_Data;


    };

}