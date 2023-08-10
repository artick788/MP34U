#include "InstallerGUI.hpp"

namespace mp34u{

    InstallerGUI::InstallerGUI():
    m_Configuration(s_ConfigFile),
    m_State(0){
        m_Configuration.addSection("General");

        WindowDesc wDesc;
        wDesc.width = 1280;
        wDesc.height = 720;
        wDesc.title = "MP34U - Installer";
        m_Window = createWindow(wDesc);
        ContextDesc cDesc;
        cDesc.api = SR_API_OPENGL;
        m_Context = m_Window->createContext(cDesc);
        m_Context->setVerticalSynchronisation(true);
        m_Window->createImGuiContext();

        m_Panels.emplace_back(createUP<WelcomePanel>(m_Configuration, m_State, m_Window));

    }

    InstallerGUI::~InstallerGUI() {
        m_Window->destroyImGuiContext();
        m_Window->destroyContext();

        m_Configuration.save();
    }

    void InstallerGUI::run() {
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
            m_Panels[m_State]->run();
            m_Window->onImGuiEnd();
            m_Context->swapBuffers();
        }

    }
}