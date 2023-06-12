#include "DownloadWindow.hpp"

namespace mp34u{


    DownloadWindow::DownloadWindow(Resource<SyriusWindow> &window, ResourceView<Context> &context, GUIState &state):
    AbstractWindow(window, context, state),
    m_MusicFile(nullptr),
    m_URL(),
    m_Title(),
    m_Artist(),
    m_Album(),
    m_Year(),
    m_Genre(),
    m_Key(),
    m_Comment(),
    m_BPM(){
        memset(m_URL, 0, 512);
        memset(m_Title, 0, 256);
        memset(m_Artist, 0, 256);
        memset(m_Album, 0, 256);
        memset(m_Year, 0, 256);
        memset(m_Genre, 0, 256);
        memset(m_Key, 0, 10);
        memset(m_Comment, 0, 256);
        memset(m_BPM, 0, 10);
    }

    DownloadWindow::~DownloadWindow() {
    }

    void DownloadWindow::onRender() {
        beginImGuiWindow("Download");

        ImGui::InputText("URL", m_URL, 512);
        ImGui::NewLine();

        ImGui::InputText("Artist", m_Artist, 256);
        ImGui::InputText("Title", m_Title, 256);
        ImGui::InputText("Album", m_Album, 256);
        ImGui::InputText("Year", m_Year, 256);
        ImGui::InputText("Genre", m_Genre, 256);
        ImGui::InputText("Comment", m_Comment, 256);
        ImGui::InputText("Key", m_Key, 10);
        ImGui::InputText("BPM", m_BPM, 10);

        ImGui::NewLine();
        if (ImGui::Button("Download", ImVec2(430, 20))){
            m_ThreadPool.addTask([this]{
                auto musicFilepath = dowloadFromYoutube(m_URL);
                if (!musicFilepath.empty()){
                    auto musicFile = createMP3File(musicFilepath);
                    musicFile->setTitle(m_Title);
                    musicFile->setArtist(m_Artist);
                    musicFile->setAlbum(m_Album);
                    musicFile->setYear(m_Year);
                    musicFile->setGenre(m_Genre);
                    musicFile->setKey(m_Key);
                    musicFile->setComment(m_Comment);
                    musicFile->setBPM(m_BPM);

                    std::string newFileName = std::string(m_Artist) + " - " + std::string(m_Title) + ".mp3";
                    musicFile->save(newFileName);
                }
            });
        }

        renderEndSection();
    }
}
