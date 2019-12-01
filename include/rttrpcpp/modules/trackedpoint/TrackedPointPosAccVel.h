#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/trackedpoint/TrackedPoint.h>

namespace RTTrPCpp {

class TrackedPointPosAccVel : public Module<0x21>, public TrackedPoint
{
public:
    TrackedPointPosAccVel() = default;
    TrackedPointPosAccVel(uint8_t idx, Position pos, Acceleration accel, Velocity vel);
    TrackedPointPosAccVel(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 0x34; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    bool operator==(const TrackedPointPosAccVel &other) const;
};

} // namespace RTTrPCpp