#pragma once
#include <memory>
#include <rttrpcpp/trackables/Trackable.h>

namespace RTTrPCpp {

class TrackableFactory
{
public:
    std::shared_ptr<TrackableGeneric> generateFromBytes(uint8_t * const buf);

    template <class TrackableClass>
    std::shared_ptr<TrackableClass> generate(uint8_t * const buf)
    {
        static_assert(std::is_base_of<TrackableGeneric, TrackableClass>::value);
        return std::make_shared<TrackableClass>(buf);
    }
};

} // namespace RTTrPCpp