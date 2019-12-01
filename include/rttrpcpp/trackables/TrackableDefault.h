#pragma once
#include <rttrpcpp/trackables/Trackable.h>

namespace RTTrPCpp {

class TrackableDefault : public Trackable<0x01>
{
public:
    TrackableDefault() = default;
    TrackableDefault(std::string name) : Trackable(name) {}
    TrackableDefault(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final;

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;
};

} // namespace RTTrPCpp