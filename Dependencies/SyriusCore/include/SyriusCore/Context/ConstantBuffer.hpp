#pragma once

#include "Utils.hpp"
#include "Shader.hpp"

namespace Syrius{

    struct SR_CORE_API ConstantBufferDesc{
        std::string name;
        uint32 size                 = 0;
        uint32 slot                 = 0;
        const void* data            = nullptr;
        SR_BUFFER_TYPE type         = SR_BUFFER_DEFAULT;
        SR_SHADER_TYPE shaderStage  = SR_SHADER_VERTEX;
    };

    class SR_CORE_API ConstantBuffer{
    public:
        explicit ConstantBuffer(const ConstantBufferDesc& desc);

        virtual ~ConstantBuffer() = default;

        virtual void bind() = 0;

        virtual void setData(const void* data) = 0;

        [[nodiscard]] virtual uint64 getIdentifier() const = 0;

        [[nodiscard]] const std::string& getBlockName() const;

        [[nodiscard]] uint32 getSize() const;

        [[nodiscard]] uint32 getBindingIndex() const;

        [[nodiscard]] SR_BUFFER_TYPE getBufferType() const;

    protected:
        uint32 m_Size;
        uint32 m_BindingIndex;
        SR_BUFFER_TYPE m_Type;
        std::string m_BlockName;

    };

}

