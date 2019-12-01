#include <rttrpcpp/modules/orientation/OrientationQuaternion.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

OrientationQuaternion::OrientationQuaternion(const OrientationQuaternion &other)
{
    *this = other;
}

OrientationQuaternion::OrientationQuaternion(uint16_t latency, Quaternion q)
{
    m_latency = latency;
    m_quaternion = q;
}

size_t OrientationQuaternion::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);

    memcpy(&buf[ret], &m_latency, sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_quaternion.toBytes(&buf[ret]);

    return ret;
}

size_t OrientationQuaternion::fromBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::fromBytes(buf);

    memcpy(&m_latency, &buf[ret], sizeof(uint16_t));
    ret += sizeof(uint16_t);
    ret += m_quaternion.fromBytes(&buf[ret]);

    log_debug("  Latency:   %u", m_latency);
    log_debug("  Q0:         %.5f", m_quaternion.x);
    log_debug("  Q1:         %.5f", m_quaternion.y);
    log_debug("  Q2:         %.5f", m_quaternion.z);
    log_debug("  Q3:         %.5f", m_quaternion.w);

    return ret;
}

const OrientationQuaternion &OrientationQuaternion::operator=(const OrientationQuaternion &other)
{
    m_latency = other.m_latency;
    m_quaternion = other.m_quaternion;

    return *this;
}

bool OrientationQuaternion::operator==(const OrientationQuaternion &other) const
{
    return m_quaternion == other.m_quaternion
        && m_latency == other.m_latency;
}