#include <rttrpcpp/modules/centroid/CentroidPos.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

CentroidPos::CentroidPos(uint16_t latency, Position pos)
{
    m_latency = latency;
    m_position = pos;
}

size_t CentroidPos::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);

    memcpy(&buf[ret], &m_latency, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_position.toBytes(&buf[ret]);

    return ret;
}

size_t CentroidPos::fromBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::fromBytes(buf);

    memcpy(&m_latency, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_position.fromBytes(&buf[ret]);

    log_debug("  Latency:   %u", m_latency);
    log_debug("  X:         %.5f", m_position.x);
    log_debug("  Y:         %.5f", m_position.y);
    log_debug("  Z:         %.5f", m_position.z);

    return ret;
}

bool CentroidPos::operator==(const CentroidPos &other) const
{
    return m_position == other.m_position
        && m_latency == other.m_latency;
}
