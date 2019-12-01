#pragma once
#include <cstdint>
#include <rttrpcpp/modules/LocationModule.h>

namespace RTTrPCpp {

class TrackedPoint : public LocationModule
{
public:
    uint16_t getLatency() const { return m_latency; }
    uint8_t getIndex() const { return m_index; }

protected:
    uint16_t m_latency = 0;
    uint8_t m_index = 0;
};

} // namespace RTTrPCpp
