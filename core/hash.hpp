#pragma once

#include <cstdint>

uint64_t djb2_hash(const uint8_t *input)
{
    uint64_t hash = 5381;
    for (int i = 0; i < 3; i++) {
        hash = (hash * 33) + input[i];
    }
    return hash;
}