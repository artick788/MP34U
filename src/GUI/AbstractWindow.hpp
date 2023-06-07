#pragma once

#include "../FileTagger/FileFactory.hpp"
#include <SyriusCore/SyriusCore.hpp>

namespace mp34u{
    using namespace Syrius;

    enum class GUIState{
        Menu,
        FileTagger,
        Download,
        About
    };

    class AbstractWindow{
    public:
        AbstractWindow(Resource<SyriusWindow>& window, ResourceView<Context>& context, GUIState& state);

        virtual ~AbstractWindow() = default;

        virtual void onRender() = 0;

        virtual void onResize(uint32_t width, uint32_t height) = 0;

    protected:

        void beginImGuiWindow(const char* name);

        void renderEndSection();

    protected:
        GUIState& m_State;
        Resource<SyriusWindow>& m_Window;
        ResourceView<Context>& m_Context;


    };



}