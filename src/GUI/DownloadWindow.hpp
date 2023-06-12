#pragma once

#include "AbstractWindow.hpp"
#include "../Utils/ThreadPool.hpp"
#include "../FileTagger/FileFactory.hpp"
#include "../Downloader/DownloadFactory.hpp"

namespace mp34u{

    class DownloadWindow: public AbstractWindow{
    public:

        DownloadWindow(Resource<SyriusWindow>& window, ResourceView<Context>& context, GUIState& state);

        ~DownloadWindow() override;

        void onRender() override;

    private:
        UP<MusicFile> m_MusicFile;
        ThreadPool m_ThreadPool;

        char m_URL[512];

        char m_Title[256];
        char m_Artist[256];
        char m_Album[256];
        char m_Year[256];
        char m_Genre[256];
        char m_Key[10];
        char m_Comment[256];
        char m_BPM[10];
    };

}