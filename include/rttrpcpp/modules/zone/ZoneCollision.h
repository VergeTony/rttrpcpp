#pragma once
#include <string>
#include <rttrpcpp/modules/Module.h>

namespace RTTrPCpp {

class ZoneCollision : public Module<0x22>
{
public:
    ZoneCollision() = default;
    ZoneCollision(std::string collisions);
    ZoneCollision(uint8_t * const buf) { fromBytes(buf); }

    uint16_t getSize() const final;

    size_t toBytes(uint8_t * const buf) final;
    size_t fromBytes(uint8_t * const buf) final;

    bool operator==(const ZoneCollision &other) const;
private:
    /* type = 1, size = 2, length = 2 */
    static const size_t ZONE_COLLISION_HEADER_SIZE = 5;

    std::string m_collisions;
};

} // namespace RTTrPCpp