#pragma once

#include "../Utils/ThreadPool.hpp"
#include "../FileTagger/FileFactory.hpp"
#include "../Utils/MusicMetaData.hpp"

namespace mp34u{

    class DownloadFactory{
    public:
        DownloadFactory();

        ~DownloadFactory();

        std::unique_ptr<MusicFile> download(const std::string& url, const MusicMetaData& metaData);

    private:
        ThreadPool m_ThreadPool;
    };

}