#include <rttrpcpp/modules/trackedpoint/TrackedPointPosAccVel.h>
#include <rttrpcpp/core/Logging.h>

using namespace RTTrPCpp;

TrackedPointPosAccVel::TrackedPointPosAccVel(uint8_t idx, Position pos, Acceleration accel, Velocity vel)
{
    m_index = idx;
    m_position = pos;
    m_acceleration = accel;
    m_velocity = vel;
}

size_t TrackedPointPosAccVel::toBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::toBytes(buf);

    ret += m_position.toBytes(&buf[ret]);
    ret += m_acceleration.toBytes(&buf[ret]);
    ret += m_velocity.toBytes(&buf[ret]);
    memcpy(&buf[ret], &m_index, sizeof(uint8_t));
    ret += sizeof(uint8_t);

    return ret;
}

size_t TrackedPointPosAccVel::fromBytes(uint8_t * const buf)
{
    size_t ret = ModuleGeneric::fromBytes(buf);

    ret += m_position.fromBytes(&buf[ret]);
    ret += m_acceleration.fromBytes(&buf[ret]);
    ret += m_velocity.fromBytes(&buf[ret]);
    memcpy(&m_index, &buf[51], sizeof(uint8_t));
    ret += sizeof(uint8_t);

    log_debug("  X:         %.5f", m_position.x);
    log_debug("  Y:         %.5f", m_position.y);
    log_debug("  Z:         %.5f", m_position.z);
    log_debug("  AX:        %.5f", m_acceleration.x);
    log_debug("  AY:        %.5f", m_acceleration.y);
    log_debug("  AZ:        %.5f", m_acceleration.z);
    log_debug("  VX:        %.5f", m_velocity.x);
    log_debug("  VY:        %.5f", m_velocity.y);
    log_debug("  VZ:        %.5f", m_velocity.z);
    log_debug("  idx:       %u", m_index);

    return ret;
}

bool TrackedPointPosAccVel::operator==(const TrackedPointPosAccVel &other) const
{
    return m_position == other.m_position
        && m_acceleration == other.m_acceleration
        && m_velocity == other.m_velocity
        && m_index == other.m_index;
}
