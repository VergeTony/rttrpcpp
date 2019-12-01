#pragma once
#include <cstdint>
#include <rttrpcpp/core/Vector3.h>
#include <rttrpcpp/core/Vector4.h>

namespace RTTrPCpp {

using Euler = Vector3<double>;
using Quaternion = Vector4<double>;

class OrientationModule
{
public:
    OrientationModule() :
        m_latency(0)
    {
        /* Union is non-trival. Initialize Quaternion because it is larger. */
        m_quaternion = {};
    }

    OrientationModule(const OrientationModule &other)
    {
        m_latency = other.m_latency;

        /* Union is non-trival. Copy Quaternion because it is larger. */
        m_quaternion = other.m_quaternion;
    }

    uint16_t getLatency() const { return m_latency; }
    Euler getEuler() const { return m_euler; }
    Quaternion getQuaternion() const { return m_quaternion; }

protected:
    uint16_t m_latency;
    union
    {
        Euler m_euler;
        Quaternion m_quaternion;
    };
};

} // namespace RTTrPCpp
