#pragma once

#include "../Core/SyriusCoreInclude.hpp"
#include "../Utils/Image.hpp"
#include "../Utils/Resource.hpp"

namespace Syrius{

    // shader types
    typedef enum SR_SHADER_TYPE {
        SR_SHADER_VERTEX                 = 0x01,
        SR_SHADER_FRAGMENT               = 0x02,
        SR_SHADER_PIXEL                  = 0x02,
        SR_SHADER_GEOMETRY               = 0x03,
        SR_SHADER_TESSELATION_EVALUATION = 0x04,
        SR_SHADER_TESSELATION_CONTROL    = 0x05,
        SR_SHADER_COMPUTE                = 0x06
    } SR_SHADER_TYPE;

    typedef enum SR_SHADER_CODE_TYPE {
        SR_SHADER_CODE_NONE           = 0x00,
        SR_SHADER_CODE_GLSL           = 0x01,
        SR_SHADER_CODE_HLSL           = 0x02,
        SR_SHADER_CODE_SPIRV          = 0x03
    } SR_SHADER_CODE_TYPE;

    // buffer access types
    typedef enum SR_BUFFER_TYPE {
        SR_BUFFER_DEFAULT       = 0x01,
        SR_BUFFER_DYNAMIC       = 0x02,
        SR_BUFFER_STATIC        = 0x03

    } SR_BUFFER_TYPE;

    // drawing modes
    typedef enum SR_DRAW_TYPE {
        SR_DRAW_POINTS          = 0x01,
        SR_DRAW_LINES           = 0x02,
        SR_DRAW_LINES_STRIP     = 0x03,
        SR_DRAW_TRIANGLES       = 0x04,
        SR_DRAW_TRIANGLE_STRIP  = 0x05
    } SR_DRAW_MODE;

    // depth functions
    typedef enum SR_COMPARISON_FUNC {
        SR_COMPARISON_FUNC_ALWAYS        = 0x01,
        SR_COMPARISON_FUNC_NEVER         = 0x02,
        SR_COMPARISON_FUNC_LESS          = 0x03,
        SR_COMPARISON_FUNC_EQUAL         = 0x04,
        SR_COMPARISON_FUNC_LESS_EQUAL    = 0x05,
        SR_COMPARISON_FUNC_GREATER       = 0x06,
        SR_COMPARISON_FUNC_GREATER_EQUAL = 0x07,
        SR_COMPARISON_FUNC_NOT_EQUAL     = 0x08
    } SR_COMPARISON_FUNC;

    // stencil operations
    typedef enum SR_STENCIL_FUNC{
        SR_STENCIL_FUNC_KEEP             = 0x01,
        SR_STENCIL_FUNC_ZERO             = 0x02,
        SR_STENCIL_FUNC_REPLACE          = 0x03,
        SR_STENCIL_FUNC_INCR             = 0x04,
        SR_STENCIL_FUNC_INCR_WRAP        = 0x05,
        SR_STENCIL_FUNC_DECR             = 0x06,
        SR_STENCIL_FUNC_DECR_WRAP        = 0x07,
        SR_STENCIL_FUNC_INVERT           = 0x08
    } SR_STENCIL_FUNC;

    typedef enum SR_TEXTURE_FILTER{
        SR_TEXTURE_FILTER_NONE      = 0x00,
        SR_TEXTURE_FILTER_LINEAR    = 0x01,
        SR_TEXTURE_FILTER_POINT     = 0x02
    } SR_TEXTURE_FILTER;

    typedef enum SR_TEXTURE_WRAP{
        SR_TEXTURE_WRAP_NONE            = 0x00,
        SR_TEXTURE_WRAP_REPEAT          = 0x01,
        SR_TEXTURE_WRAP_MIRROR_REPEAT   = 0x02,
        SR_TEXTURE_WRAP_CLAMP_EDGE      = 0x03,
        SR_TEXTURE_WRAP_CLAMP_BORDER    = 0x04
    } SR_TEXTURE_ADDRESS_WRAP;

    std::string SR_CORE_API getShaderTypeString(SR_SHADER_TYPE type);

}




