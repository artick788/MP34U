#include "FileTaggerWindow.hpp"

namespace mp34u{

    FileTaggerWindow::FileTaggerWindow(Resource<SyriusWindow> &window, ResourceView<Context> &context, GUIState &state):
    AbstractWindow(window, context, state),
    m_FilePath(),
    m_MusicFile(nullptr),
    m_Title(),
    m_Artist(),
    m_Album(),
    m_Year(),
    m_Genre(),
    m_Key(),
    m_Comment(),
    m_BPM(){

    }

    FileTaggerWindow::~FileTaggerWindow() {

    }

    void FileTaggerWindow::onRender() {
        beginImGuiWindow("File Tagger");
        if (m_FilePath.empty()){
            if (ImGui::Button("Select File")){
                m_FilePath = m_Window->openFileDialog("MP3 Files\0*.mp3\0");
                if (!m_FilePath.empty()){
                    m_MusicFile = createMP3File(m_FilePath);
                    memcpy(m_Artist, m_MusicFile->getArtist().c_str(), m_MusicFile->getArtist().size());
                    memcpy(m_Title, m_MusicFile->getTitle().c_str(), m_MusicFile->getTitle().size());
                    memcpy(m_Album, m_MusicFile->getAlbum().c_str(), m_MusicFile->getAlbum().size());
                    memcpy(m_Year, m_MusicFile->getYear().c_str(), m_MusicFile->getYear().size());
                    memcpy(m_Genre, m_MusicFile->getGenre().c_str(), m_MusicFile->getGenre().size());
                    memcpy(m_Key, m_MusicFile->getKey().c_str(), m_MusicFile->getKey().size());
                    memcpy(m_Comment, m_MusicFile->getComment().c_str(), m_MusicFile->getComment().size());
                    memcpy(m_BPM, m_MusicFile->getBPM().c_str(), m_MusicFile->getBPM().size());
                }
            }
        }
        else{
            ImGui::Text("File: %s", m_FilePath.c_str());

            ImGui::InputText("Title", m_Title, 256);
            ImGui::InputText("Artist", m_Artist, 256);
            ImGui::InputText("Album", m_Album, 256);
            ImGui::InputText("Year", m_Year, 256);
            ImGui::InputText("Genre", m_Genre, 256);
            ImGui::InputText("Key", m_Key, 256);
            ImGui::InputText("Comment", m_Comment, 256);
            ImGui::InputText("BPM", m_BPM, 256);

            ImGui::NewLine();
            if (ImGui::Button("Save")){
                m_MusicFile->setTitle(m_Title);
                m_MusicFile->setArtist(m_Artist);
                m_MusicFile->setAlbum(m_Album);
                m_MusicFile->setYear(m_Year);
                m_MusicFile->setGenre(m_Genre);
                m_MusicFile->setKey(m_Key);
                m_MusicFile->setComment(m_Comment);
                m_MusicFile->setBPM(m_BPM);
                m_MusicFile->save(m_FilePath);
            }

        }

        renderEndSection();
    }

}