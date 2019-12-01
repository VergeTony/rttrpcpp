#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/centroid/Centroid.h>

namespace RTTrPCpp {

class CentroidPosAccVel : public Module<0x20>, public Centroid
{
public:
    CentroidPosAccVel() = default;
    CentroidPosAccVel(Position pos, Acceleration accel, Velocity vel);
    CentroidPosAccVel(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 0x33; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    bool operator==(const CentroidPosAccVel &other) const;
};

} // namespace RTTrPCpp