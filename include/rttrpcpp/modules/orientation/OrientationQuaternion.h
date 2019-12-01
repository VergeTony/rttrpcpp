#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/OrientationModule.h>

namespace RTTrPCpp {

class OrientationQuaternion : public Module<0x03>, public OrientationModule
{
public:
    OrientationQuaternion() = default;
    OrientationQuaternion(const OrientationQuaternion &other);
    OrientationQuaternion(uint16_t latency, Quaternion q);
    OrientationQuaternion(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 37; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    const OrientationQuaternion &operator=(const OrientationQuaternion &other);
    bool operator==(const OrientationQuaternion &other) const;
};

} // namespace RTTrPCpp