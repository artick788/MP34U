#pragma once

#include "Utils.hpp"
#include "MusicFile.hpp"

namespace mp34u{

    UP<MusicFile> createMP3File(const std::string& path);

}