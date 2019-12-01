#pragma once
#include <rttrpcpp/modules/Module.h>
#include <rttrpcpp/modules/OrientationModule.h>

namespace RTTrPCpp {

class OrientationEuler : public Module<0x04>, public OrientationModule
{
public:
    OrientationEuler() = default;
    OrientationEuler(const OrientationEuler &other);
    OrientationEuler(uint16_t latency, uint16_t order, Euler euler);
    OrientationEuler(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final { return 31; }

    uint16_t getOrder() const { return m_order; }

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    const OrientationEuler &operator=(const OrientationEuler &other);
    bool operator==(const OrientationEuler &other) const;

private:
    uint16_t m_order;
};

} // namespace RTTrPCpp