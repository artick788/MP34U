#include "AbstractWindow.hpp"

namespace mp34u{

    AbstractWindow::AbstractWindow(Resource<SyriusWindow> &window, ResourceView<Context> &context, GUIState& state):
    m_Window(window),
    m_Context(context),
    m_State(state){

    }

    void AbstractWindow::beginImGuiWindow(const char* name) {
        auto windowWidth = static_cast<float>(m_Window->getWidth());
        auto windowHeight = static_cast<float>(m_Window->getHeight());
        ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    }

    void AbstractWindow::renderEndSection() {
        ImGui::NewLine();
        if (ImGui::Button("Menu", ImVec2(210, 20))){
            m_State = GUIState::Menu;
        }
        ImGui::SameLine();
        if (ImGui::Button("Exit", ImVec2(210, 20))){
            m_Window->close();
        }
        ImGui::End();
    }
}
