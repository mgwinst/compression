#pragma once

#include <cstdint>

struct mgwhdr
{
    uint16_t magic_num = 0x134;
    const char *original_file_name;
    const char *compression_method;
    uint32_t window_size;
    uint32_t checksum;
    uint64_t original_byte_len;
    uint64_t compressed_byte_len;
    bool encryption;
};
