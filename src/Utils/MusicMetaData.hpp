#pragma once

#include <string>

namespace mp34u{

    struct MusicMetaData{
        std::string title;
        std::string artist;
        std::string album;
        std::string year;
        std::string genre;
        std::string track;
        std::string comment;
        std::string bpm;
        std::string key;
    };
}