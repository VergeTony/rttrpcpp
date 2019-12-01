#pragma once
#include <cstdint>
#include <rttrpcpp/core/Vector3.h>

namespace RTTrPCpp {

using Position = Vector3<double>;
using Velocity = Vector3<float>;
using Acceleration = Vector3<float>;

class LocationModule
{
public:
    const Position &getPosition() const { return m_position; }
    const Velocity &getVelocity() const { return m_velocity; }
    const Acceleration &getAcceleration() const { return m_acceleration; }

protected:
    Position m_position = {};
    Acceleration m_acceleration = {};
    Velocity m_velocity = {};
};

} // namespace RTTrPCpp
