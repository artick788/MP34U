#pragma once

#include "../FileTagger/FileFactory.hpp"
#include "AbstractWindow.hpp"

namespace mp34u{

    class FileTaggerWindow : public AbstractWindow{
    public:
        FileTaggerWindow(Resource<SyriusWindow>& window, ResourceView<Context>& context, GUIState& state);

        ~FileTaggerWindow() override;

        void onRender() override;

        void onResize(uint32_t width, uint32_t height) override;

    private:
        std::string m_FilePath;
        UP<MusicFile> m_MusicFile;

        char m_Title[256];
        char m_Artist[256];
        char m_Album[256];
        char m_Year[256];
        char m_Genre[256];
        char m_Key[256];
        char m_Comment[256];
        char m_BPM[256];
    };
}