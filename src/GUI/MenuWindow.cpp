#include "MenuWindow.hpp"

namespace mp34u{

    MenuWindow::MenuWindow(Resource<SyriusWindow>& window, ResourceView<Context>& context, GUIState& state):
    AbstractWindow(window, context, state){
    }

    MenuWindow::~MenuWindow(){
    }

    void MenuWindow::onRender() {
        beginImGuiWindow("Menu");

        auto windowWidth = static_cast<float>(m_Window->getWidth());
        auto windowHeight = static_cast<float>(m_Window->getHeight());
        auto buttonWidth = windowWidth / 2.0f;
        auto buttonHeight = 30.0f;

        auto buttonX = (windowWidth - buttonWidth) / 2.0f;
        auto buttonY = (windowHeight - buttonHeight) / 3.0f;

        auto buttonDrawer = [this, &buttonX, &buttonY, &buttonWidth, &buttonHeight](const char* text, GUIState state){
            ImGui::SetCursorPosX(buttonX);
            ImGui::SetCursorPosY(buttonY);
            if (ImGui::Button(text, ImVec2(buttonWidth, buttonHeight))){
                m_State = state;
            }
            buttonY += buttonHeight + 10.0f;
        };

        buttonDrawer("File Tagger", GUIState::FileTagger);
        buttonDrawer("Download", GUIState::Download);
        buttonDrawer("About", GUIState::About);
        buttonY += 20.0f;
        ImGui::SetCursorPosX(buttonX);
        ImGui::SetCursorPosY(buttonY);
        if (ImGui::Button("Exit", ImVec2(buttonWidth, buttonHeight))){
            m_Window->close();
        }

        ImGui::End();
    }
}