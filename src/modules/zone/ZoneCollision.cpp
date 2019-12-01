#include <rttrpcpp/modules/zone/ZoneCollision.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

ZoneCollision::ZoneCollision(std::string collisions) :
    m_collisions(collisions)
{

}

uint16_t ZoneCollision::getSize() const
{
    return ZONE_COLLISION_HEADER_SIZE + m_collisions.size();
}

size_t ZoneCollision::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);
    uint16_t length = Serializable::htons(m_collisions.size());

    memcpy(&buf[ret], &length, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], reinterpret_cast<const uint8_t*>(m_collisions.c_str()), m_collisions.size());

    return ret + m_collisions.size();
}

size_t ZoneCollision::fromBytes(uint8_t * const buf)
{
    uint8_t type = buf[0];
    assert(type == getType());

    uint16_t size;
    memcpy(&size, &buf[1], sizeof(uint16_t));
    size = Serializable::ntohs(size);

    log_debug("Module Header:");
    log_debug("  Type:      0x%02X", type);
    log_debug("  Size:      %u", size);

    int ret = sizeof(uint16_t) + sizeof(uint8_t);

    uint16_t length;
    memcpy(&length, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    length = Serializable::ntohs(length);

    m_collisions = std::string(reinterpret_cast<const char*>(&buf[ret]), length);

    assert(static_cast<size_t>(size) == getSize());

    log_debug("  ColLen:    %u", length);
    log_debug("  Col:       %s", m_collisions.c_str());

    return ret + m_collisions.size();
}

bool ZoneCollision::operator==(const ZoneCollision &other) const
{
    return m_collisions == other.m_collisions;
}
