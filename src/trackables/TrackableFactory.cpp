#include <rttrpcpp/trackables/TrackableFactory.h>
#include <rttrpcpp/trackables/TrackableDefault.h>

using namespace RTTrPCpp;

std::shared_ptr<TrackableGeneric> TrackableFactory::generateFromBytes(uint8_t * const buf)
{
    switch (buf[0])
    {
        case TrackableDefault::typeId:
            return generate<TrackableDefault>(buf);
        default:
            throw std::runtime_error("Trackable not implemented");
    }
}