#pragma once

#include "Viewport.hpp"
#include "ColorAttachment.hpp"
#include "DepthStencilAttachment.hpp"

namespace Syrius{

    class SR_CORE_API FrameBufferDescription{
    public:
        FrameBufferDescription();

        ~FrameBufferDescription() = default;

        void addViewportDesc(const ViewportDesc& desc);

        void addColorAttachmentDesc(const ColorAttachmentDesc& desc);

        void addDepthStencilAttachmentDesc(const DepthStencilAttachmentDesc& desc);

        void configure();

        [[nodiscard]] const std::vector<ViewportDesc>& getViewportDesc() const;

        [[nodiscard]] const std::vector<ColorAttachmentDesc>& getColorAttachmentDesc() const;

        [[nodiscard]] const std::vector<DepthStencilAttachmentDesc>& getDepthStencilAttachmentDesc() const;

    private:
        std::vector<ViewportDesc> m_ViewportDesc;
        std::vector<ColorAttachmentDesc> m_ColorAttachmentDesc;
        std::vector<DepthStencilAttachmentDesc> m_DepthStencilAttachmentDesc; // only one depth stencil attachment is allowed, so the last added will be used

    };

}
