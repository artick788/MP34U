#pragma once

#include "../MusicFile.hpp"
#include "ID3FrameHeader.hpp"

namespace mp34u{

    struct ID3v24Header{
        char ID[3];
        int8_t version = 0;
        int8_t revision = 0;
        int8_t flags = 0;
        int32_t size = 0;
    };

    class MP3File: public MusicFile{
    public:
        explicit MP3File(const std::string& path);

        ~MP3File() override;

        void save(const std::string& path) override;

    private:
        bool readID3Tag(std::ifstream& file);

        void readHeader(std::ifstream& file);

        void parseHeader();

    private:
        std::string m_Path;
        ID3v24Header m_ID3v24Header;
        std::unique_ptr<ID3FrameHeader> m_ID3FrameHeader;
        uint32_t m_FrameCount;


    };

}