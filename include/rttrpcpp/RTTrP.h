#pragma once
#include <cstdlib>
#include <cstdint>

namespace RTTrPCpp {

constexpr uint16_t RTTRPM_VERSION = 0x02;
constexpr uint16_t RTTRPL_VERSION = 0x03;

enum class RTTrPType : uint16_t
{
    None = 0,
    RTTrPM = RTTRPM_VERSION,
    RTTrPL = RTTRPL_VERSION,
};

enum class PacketFormat : uint8_t
{
    Raw = 0,
    Protobuf = 1,
    Thrift = 2,
};

constexpr size_t RTTRP_HEADER_SIZE = 18;

constexpr uint16_t RTTRP_INTEGER_SIGNATURE_BE = 0x4154;
constexpr uint16_t RTTRP_INTEGER_SIGNATURE_LE = 0x5441;
constexpr uint16_t RTTRP_FLOAT_SIGNATURE_BE = 0x4334;
constexpr uint16_t RTTRP_FLOAT_SIGNATURE_LE = 0x3443;

} // namespace RTTrPCpp
