#pragma once

#include "../../Core/Include.hpp"
#include "InstallerPanel.hpp"

namespace mp34u{

    class InstallerGUI{
    public:
        InstallerGUI();

        ~InstallerGUI();

        void run();

    private:
        EasyIni::Configuration m_Configuration;
        MP34U_INSTALLER_GUI_STATE m_State;
        std::vector<UP<InstallerPanel>> m_Panels;

        Resource<SyriusWindow> m_Window;
        ResourceView<Context> m_Context;
    };
}