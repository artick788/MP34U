#include "InstallerPanel.hpp"

namespace mp34u{

    InstallerPanel::InstallerPanel(EasyIni::Configuration &configuration, MP34U_INSTALLER_GUI_STATE &state, Resource<SyriusWindow> &window):
    m_Configuration(configuration),
    m_State(state),
    m_Window(window) {

    }

    InstallerPanel::~InstallerPanel() {

    }

    void InstallerPanel::run() {

    }

    void InstallerPanel::beginImGuiWindow(const char *name) {
        auto windowWidth = static_cast<float>(m_Window->getWidth());
        auto windowHeight = static_cast<float>(m_Window->getHeight());
        ImGui::Begin(name, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
    }

    void InstallerPanel::renderEndSection() {
        ImGui::NewLine();
        if (ImGui::Button("Previous", ImVec2(210, 20))){
            m_State--;
        }
        ImGui::SameLine();
        if (ImGui::Button("Next", ImVec2(210, 20))){
            m_State++;
        }
        ImGui::End();

    }

    WelcomePanel::WelcomePanel(EasyIni::Configuration &configuration, MP34U_INSTALLER_GUI_STATE &state, Resource<SyriusWindow> &window):
    InstallerPanel(configuration, state, window) {

    }

    WelcomePanel::~WelcomePanel() {

    }

    void WelcomePanel::run() {
        beginImGuiWindow("Welcome");

        auto centerText = [](const std::string& text){
            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth   = ImGui::CalcTextSize(text.c_str()).x;
            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
            ImGui::Text(text.c_str());
        };

        centerText("Welcome to the MP34U installer!");
        ImGui::NewLine();
        centerText("This installer will guide you through the installation process.");
        ImGui::NewLine();
        centerText("Press next to continue.");

        if (ImGui::Button("Next", ImVec2(210, 20))){
            m_State++;
        }
        ImGui::End();
    }
}
