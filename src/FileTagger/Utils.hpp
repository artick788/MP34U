#pragma once

#include "../Include.hpp"

#define ID3V2_HEADER_SIZE 10
#define ID3V2_EXTENDED_HEADER_SIZE 10
#define ID3V2_FRAME_HEADER_SIZE 10
#define ID3V2_FRAME_ENCODING_LENGTH 1

namespace mp34u{

    char* itob(int32_t value);

    int32_t btoi(char* value, int32_t size = 4);

    int32_t decode(int32_t value);

    int32_t encode(int32_t value);



}