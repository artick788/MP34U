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
        zeroMemory();
    }

    DownloadWindow::~DownloadWindow() {
    }

    void DownloadWindow::onRender() {
        beginImGuiWindow("Download");

        ImGui::InputText("URL", m_URL, 512);
        if (ImGui::Button("Output Directory", ImVec2(430, 20))){
            m_OutputDir = getDirectoryDialog();
        }
        ImGui::SameLine();
        ImGui::Text(m_OutputDir.c_str());
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

                    std::string newFileName = m_OutputDir + "\\" + std::string(m_Artist) + " - " + std::string(m_Title) + ".mp3";
                    musicFile->save(newFileName);
                }
            });
        }

        renderEndSection();
    }

    std::string DownloadWindow::getDirectoryDialog() {
        BROWSEINFO browseInfo = {};
        browseInfo.hwndOwner = nullptr; // Set the owner window handle if necessary
        browseInfo.pidlRoot = nullptr; // Set the root folder if necessary
        browseInfo.pszDisplayName = nullptr; // Output buffer for the selected folder
        browseInfo.lpszTitle = TEXT("Select a folder"); // Title of the dialog
        browseInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE; // Flags for the dialog

        LPITEMIDLIST selectedFolder = SHBrowseForFolder(&browseInfo);
        if (selectedFolder != nullptr) {
            TCHAR folderPath[MAX_PATH];
            SHGetPathFromIDList(selectedFolder, folderPath);

            // Display the selected folder path
            std::string retVal(folderPath);

            // Free the allocated memory
            CoTaskMemFree(selectedFolder);
            return retVal;
        }
        return "";
    }

    void DownloadWindow::zeroMemory() {
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
}
