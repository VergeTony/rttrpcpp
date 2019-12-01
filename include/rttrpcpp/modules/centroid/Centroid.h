#pragma once
#include <cstdint>
#include <rttrpcpp/modules/LocationModule.h>

namespace RTTrPCpp {

class Centroid : public LocationModule
{
public:
    uint16_t getLatency() const { return m_latency; }

protected:
    uint16_t m_latency = 0;
};

} // namespace RTTrPCpp
