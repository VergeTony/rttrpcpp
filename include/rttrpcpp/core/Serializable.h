#pragma once
#include <vector>
#include <cstdint>
#include <cstring>

namespace RTTrPCpp {

class Serializable
{
public:
    virtual size_t toBytes(uint8_t * const buffer) = 0;
    virtual size_t fromBytes(uint8_t * const buffer) = 0;

    static uint16_t ntohs(uint16_t const net)
    {
        uint8_t data[2];
        memcpy(&data, &net, sizeof(uint16_t));

        return ((uint32_t) data[1] << 0)
            | ((uint32_t) data[0] << 8);
    }

    static uint16_t htons(uint16_t const net)
    {
        uint8_t data[2];
        memcpy(&data, &net, sizeof(uint16_t));

        return ((uint32_t) data[1] << 0)
            | ((uint32_t) data[0] << 8);
    }

    static uint32_t ntohl(uint32_t const net)
    {
        uint8_t data[4];
        memcpy(&data, &net, sizeof(uint32_t));

        return ((uint32_t) data[3] << 0)
            | ((uint32_t) data[2] << 8)
            | ((uint32_t) data[1] << 16)
            | ((uint32_t) data[0] << 24);
    }

    static uint32_t htonl(uint32_t const net)
    {
        uint8_t data[4];
        memcpy(&data, &net, sizeof(uint32_t));

        return ((uint32_t) data[3] << 24)
            | ((uint32_t) data[2] << 16)
            | ((uint32_t) data[1] << 8)
            | ((uint32_t) data[0] << 0);
    }
};

} // namespace RTTrPCpp