#include <rttrpcpp/modules/orientation/OrientationEuler.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

OrientationEuler::OrientationEuler(const OrientationEuler &other)
{
    *this = other;
}

OrientationEuler::OrientationEuler(uint16_t latency, uint16_t order, Euler euler) :
    m_order(order)
{
    m_latency = latency;
    m_euler = euler;
}

size_t OrientationEuler::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);

    memcpy(&buf[ret], &m_latency, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&buf[ret], &m_order, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_euler.toBytes(&buf[ret]);

    return ret;
}

size_t OrientationEuler::fromBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::fromBytes(buf);

    memcpy(&m_latency, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    memcpy(&m_order, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_euler.fromBytes(&buf[ret]);

    log_debug("  Latency:   %u", m_latency);
    log_debug("  Order:     %u", m_order);
    log_debug("  R1:         %.5f", m_euler.x);
    log_debug("  R2:         %.5f", m_euler.y);
    log_debug("  R3:         %.5f", m_euler.z);

    return ret;
}

const OrientationEuler &OrientationEuler::operator=(const OrientationEuler &other)
{
    m_order = other.m_order;
    m_latency = other.m_latency;
    m_euler = other.m_euler;

    return *this;
}

bool OrientationEuler::operator==(const OrientationEuler &other) const
{
    return m_euler == other.m_euler
        && m_latency == other.m_latency
        && m_order == other.m_order;
}