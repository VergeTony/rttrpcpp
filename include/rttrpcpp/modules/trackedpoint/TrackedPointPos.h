#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/trackedpoint/TrackedPoint.h>

namespace RTTrPCpp {

class TrackedPointPos : public Module<0x06>, public TrackedPoint
{
public:
    TrackedPointPos() = default;
    TrackedPointPos(uint16_t latency, Position pos, uint8_t index);
    TrackedPointPos(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 0x1E; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    bool operator==(const TrackedPointPos &other) const;
};

} // namespace RTTrPCpp