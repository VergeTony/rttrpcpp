#pragma once
#include <rttrpcpp/modules/centroid/CentroidPos.h>
#include <rttrpcpp/modules/centroid/CentroidPosAccVel.h>
#include <rttrpcpp/modules/trackedpoint/TrackedPointPos.h>
#include <rttrpcpp/modules/trackedpoint/TrackedPointPosAccVel.h>
#include <rttrpcpp/modules/orientation/OrientationEuler.h>
#include <rttrpcpp/modules/orientation/OrientationQuaternion.h>
#include <rttrpcpp/modules/zone/ZoneCollision.h>

class ModuleGenerator
{
public:
    static RTTrPCpp::CentroidPos generateCentroidPos()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::CentroidPos(
            static_cast<uint16_t>(rand()),
            RTTrPCpp::Position::generateRandom());
    }

    static RTTrPCpp::CentroidPosAccVel generateCentroidPosAccVel()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::CentroidPosAccVel(
            RTTrPCpp::Position::generateRandom(),
            RTTrPCpp::Acceleration::generateRandom(),
            RTTrPCpp::Velocity::generateRandom());
    }

    static RTTrPCpp::TrackedPointPos generateTrackedPointPos()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::TrackedPointPos(
            static_cast<uint16_t>(rand()),
            RTTrPCpp::Position::generateRandom(),
            static_cast<uint8_t>(rand()));
    }

    static RTTrPCpp::TrackedPointPosAccVel generateTrackedPointPosAccVel()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::TrackedPointPosAccVel(
            static_cast<uint8_t>(rand()),
            RTTrPCpp::Position::generateRandom(),
            RTTrPCpp::Acceleration::generateRandom(),
            RTTrPCpp::Velocity::generateRandom());
    }

    static RTTrPCpp::OrientationEuler generateOrientationEuler()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::OrientationEuler(
            static_cast<uint16_t>(rand()),
            static_cast<uint16_t>(rand()),
            RTTrPCpp::Euler::generateRandom());
    }

    static RTTrPCpp::OrientationQuaternion generateOrientationQuaternion()
    {
        srand(time(nullptr) + g_count++);

        return RTTrPCpp::OrientationQuaternion(
            static_cast<uint16_t>(rand()),
            RTTrPCpp::Quaternion::generateRandom());
    }

    static RTTrPCpp::ZoneCollision generateZoneCollision()
    {
        srand(time(nullptr) + g_count++);

        std::string collisions;
        int count = static_cast<int>(rand() % 4) + 1;

        for (int i = 0; i < count; i++)
        {
            collisions += "$" + std::to_string(static_cast<int>(rand()));
        }

        return RTTrPCpp::ZoneCollision(collisions);
    }
private:
    static int g_count;
};

int ModuleGenerator::g_count = 1;