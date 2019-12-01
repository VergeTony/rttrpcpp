#pragma once
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <rttrpcpp/core/Vector3.h>

namespace RTTrPCpp {

template<class T>
class Vector4 : public Vector3<T>
{
public:
    Vector4() = default;
    Vector4(T X, T Y, T Z, T W) : Vector3<T>(X, Y, Z), w(W) {}
    T w = 0;

    size_t toBytes(uint8_t * const buffer) final
    {
        size_t ret = Vector3<T>::toBytes(buffer);
        memcpy(&buffer[ret], &w, sizeof(T));
        return ret + sizeof(T);
    }

    size_t fromBytes(uint8_t * const buffer) final
    {
        size_t ret = Vector3<T>::fromBytes(buffer);
        memcpy(&w, &buffer[ret], sizeof(T));
        return ret + sizeof(T);
    }

    bool operator==(const class Vector4<T> &other) const
    {
        return this->x == other.x
            && this->y == other.y
            && this->z == other.z
            && w == other.w;
    }

    static Vector4<T> generateRandom()
    {
        struct timespec tv;
        clock_gettime(CLOCK_MONOTONIC, &tv);
        srand(tv.tv_nsec);
        Vector4<T> ret;

        if (std::is_integral<T>::value)
        {
            ret.x = static_cast<T>(rand());
            ret.y = static_cast<T>(rand());
            ret.z = static_cast<T>(rand());
            ret.w = static_cast<T>(rand());
        }
        else
        {
            ret.x = static_cast<T>(rand()) / RAND_MAX;
            ret.y = static_cast<T>(rand()) / RAND_MAX;
            ret.z = static_cast<T>(rand()) / RAND_MAX;
            ret.w = static_cast<T>(rand()) / RAND_MAX;
        }

        return ret;
    }
};

} // namespace RTTrPCpp
