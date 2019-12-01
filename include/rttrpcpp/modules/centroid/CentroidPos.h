#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/centroid/Centroid.h>

namespace RTTrPCpp {

class CentroidPos : public Module<0x02>, public Centroid
{
public:
    CentroidPos() = default;
    CentroidPos(uint16_t latency, Position pos);
    CentroidPos(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 0x1D; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    bool operator==(const CentroidPos &other) const;
};

} // namespace RTTrPCpp