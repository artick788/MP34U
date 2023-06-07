#pragma once

#include "MenuWindow.hpp"
#include "FileTaggerWindow.hpp"


namespace mp34u{

    class GUI{
    public:
        GUI();

        ~GUI();

        void run();

    private:

        void setup();

        void render();

        void terminate();

    private:
        GUIState m_State;
        Resource<SyriusWindow> m_Window;
        ResourceView<Context> m_Context;

        UP<MenuWindow> m_MenuWindow;
        UP<FileTaggerWindow> m_FileTaggerWindow;

    };

}