#pragma once

#include "AbstractWindow.hpp"

namespace mp34u{

    class MenuWindow : public AbstractWindow{
    public:
        MenuWindow(Resource<SyriusWindow>& window, ResourceView<Context>& context, GUIState& state);

        ~MenuWindow() override;

        void onRender() override;

        void onResize(uint32_t width, uint32_t height) override;
    };
}