#include <exception>
#include <rttrpcpp/modules/ModuleFactory.h>

#include <rttrpcpp/modules/trackedpoint/TrackedPointPos.h>
#include <rttrpcpp/modules/trackedpoint/TrackedPointPosAccVel.h>
#include <rttrpcpp/modules/centroid/CentroidPos.h>
#include <rttrpcpp/modules/centroid/CentroidPosAccVel.h>
#include <rttrpcpp/modules/orientation/OrientationEuler.h>
#include <rttrpcpp/modules/orientation/OrientationQuaternion.h>
#include <rttrpcpp/modules/zone/ZoneCollision.h>

using namespace RTTrPCpp;

std::shared_ptr<ModuleGeneric> ModuleFactory::generateFromBytes(uint8_t * const buf)
{
    switch (buf[0])
    {
        case TrackedPointPos::typeId:
            return generate<TrackedPointPos>(buf);
        case CentroidPos::typeId:
            return generate<CentroidPos>(buf);
        case CentroidPosAccVel::typeId:
            return generate<CentroidPosAccVel>(buf);
        case TrackedPointPosAccVel::typeId:
            return generate<TrackedPointPosAccVel>(buf);
        case OrientationEuler::typeId:
            return generate<OrientationEuler>(buf);
        case OrientationQuaternion::typeId:
            return generate<OrientationQuaternion>(buf);
        case ZoneCollision::typeId:
            return generate<ZoneCollision>(buf);
        default:
            throw std::runtime_error("Module not implemented");
    }
}