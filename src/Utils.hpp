#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <algorithm>
#include <unordered_set>

namespace mp34u{

    char* itob(int32_t value);

    int32_t btoi(char* value, int32_t size = 4);

    int32_t decode(int32_t value);

    int32_t encode(int32_t value);



}