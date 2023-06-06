#include "Utils.hpp"

namespace mp34u{

    char* itob(int32_t value){
        int32_t size = 4;
        char* result = (char*) malloc(sizeof(char) * size);

        // We need to reverse the bytes because Intel uses little endian.
        char* aux = (char*) &value;

        for (int i = size - 1; i >= 0; i--) {
            result[size - 1 - i] = aux[i];
        }

        return result;
    }

    int32_t btoi(char* value, int32_t size){
        int32_t result = 0x00;

        for (int i = 0; i < size; i++) {
            result = result << 8;
            result = result | (unsigned char) value[i];
        }

        return result;
    }

    int32_t decode(int32_t value){
        int32_t a, b, c, d, result = 0x0;
        a = value & 0xFF;
        b = (value >> 8) & 0xFF;
        c = (value >> 16) & 0xFF;
        d = (value >> 24) & 0xFF;

        result = result | a;
        result = result | (b << 7);
        result = result | (c << 14);
        result = result | (d << 21);

        return result;
    }

    int32_t encode(int32_t value){
        int32_t out, mask = 0x7F;

        while (mask ^ 0x7FFFFFFF)
        {
            out = value & ~mask;
            out <<= 1;
            out |= value & mask;
            mask = ((mask + 1) << 8) - 1;
            value = out;
        }

        return out;
    }
}
