#include "MP34UGui.hpp"

namespace mp34u{


    GUI::GUI():
    m_State(GUIState::Menu){
        syriusCoreInit();
        WindowDesc wDesc;
        wDesc.width = 1280;
        wDesc.height = 720;
        wDesc.title = "MP34U";
        m_Window = createWindow(wDesc);

        ContextDesc cDesc;
        cDesc.api = SR_API_OPENGL;
        m_Context = m_Window->createContext(cDesc);
        m_Context->setVerticalSynchronisation(true);
    }

    GUI::~GUI() {
        m_Window->destroyContext();
        m_Window.destroy();

        syriusCoreTerminate();
    }

    void GUI::run() {
        setup();
        while (m_Window->isOpen()){
            m_Window->pollEvents();
            while (m_Window->hasEvent()){
                auto event = m_Window->getEvent();
                if (event.type == SR_EVENT_WINDOW_CLOSED){
                    m_Window->close();
                }
                else if (event.type == SR_EVENT_WINDOW_RESIZED){

                }
            }

            m_Context->clear();
            m_Window->onImGuiBegin();
            render();
            m_Window->onImGuiEnd();
            m_Context->swapBuffers();
        }
        terminate();
    }

    void GUI::setup() {
        m_Window->createImGuiContext();

        m_MenuWindow = createUP<MenuWindow>(m_Window, m_Context, m_State);
        m_FileTaggerWindow = createUP<FileTaggerWindow>(m_Window, m_Context, m_State);
        m_DownloadWindow = createUP<DownloadWindow>(m_Window, m_Context, m_State);
    }

    void GUI::render() {
        switch (m_State) {
            case GUIState::Menu:
                m_MenuWindow->onRender();
                break;
            case GUIState::FileTagger:
                m_FileTaggerWindow->onRender();
                break;
            case GUIState::Download:
                m_DownloadWindow->onRender();
                break;
            case GUIState::About:
                printf("About is currently not implemented\n");
                m_State = GUIState::Menu;
                break;
        }

    }

    void GUI::terminate() {
        m_Window->destroyImGuiContext();
    }
}


