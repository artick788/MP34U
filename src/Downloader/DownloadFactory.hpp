#pragma once

#include "../Utils/ThreadPool.hpp"
#include "../FileTagger/FileFactory.hpp"
#include "../Utils/MusicMetaData.hpp"
#include "Downloader.hpp"

namespace mp34u{


    /**
     * @brief Downloads the music file from youtube and returns the path to the file
     * @param url
     * @return The path to the downloaded file
     */
    std::string dowloadFromYoutube(const std::string& url);

}