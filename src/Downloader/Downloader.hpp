#pragma once

#include "../Utils/MusicMetaData.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace mp34u{

    namespace py = pybind11;

    std::string callYoutubeDownloader(const std::string& url);
}