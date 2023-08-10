#pragma once

#include "../../Core/Include.hpp"

namespace mp34u{

    typedef uint32_t MP34U_INSTALLER_GUI_STATE;

    class InstallerPanel{
    public:
        InstallerPanel(EasyIni::Configuration& configuration, MP34U_INSTALLER_GUI_STATE& state, Resource<SyriusWindow> &window);

        virtual ~InstallerPanel();

        virtual void run() = 0;

    protected:

        void beginImGuiWindow(const char* name);

        void renderEndSection();

    protected:
        EasyIni::Configuration& m_Configuration;
        MP34U_INSTALLER_GUI_STATE& m_State;
        Resource<SyriusWindow>& m_Window;
    };

    class WelcomePanel : public InstallerPanel{
    public:
        WelcomePanel(EasyIni::Configuration& configuration, MP34U_INSTALLER_GUI_STATE& state, Resource<SyriusWindow> &window);

        ~WelcomePanel() override;

        void run() override;
    };
}