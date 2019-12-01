#include <rttrpcpp/modules/trackedpoint/TrackedPointPos.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

TrackedPointPos::TrackedPointPos(uint16_t latency, Position pos, uint8_t index)
{
    m_latency = latency;
    m_position = pos;
    m_index = index;
}

size_t TrackedPointPos::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);

    memcpy(&buf[ret], &m_latency, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_position.toBytes(&buf[ret]);
    memcpy(&buf[ret], &m_index, sizeof(uint8_t));
    ret += sizeof(uint8_t);

    return ret;
}

size_t TrackedPointPos::fromBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::fromBytes(buf);

    memcpy(&m_latency, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_position.fromBytes(&buf[ret]);
    memcpy(&m_index, &buf[ret], sizeof(uint8_t));
    ret += sizeof(uint8_t);

    log_debug("  Latency:   %u", m_latency);
    log_debug("  X:         %.5f", m_position.x);
    log_debug("  Y:         %.5f", m_position.y);
    log_debug("  Z:         %.5f", m_position.z);
    log_debug("  Idx:       %u", m_index);

    return ret;
}

bool TrackedPointPos::operator==(const TrackedPointPos &other) const
{
    return m_position == other.m_position
        && m_latency == other.m_latency
        && m_index == other.m_index;
}
