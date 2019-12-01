#pragma once
#include <memory>
#include <modules/Modules.h>
#include <rttrpcpp/trackables/TrackableDefault.h>

class TrackableGenerator
{
public:
    static std::shared_ptr<RTTrPCpp::TrackableDefault> generateTrackable(int moduleCount)
    {
        srand(time(nullptr) + g_count++);

        std::shared_ptr<RTTrPCpp::TrackableDefault> trackable =
            std::make_shared<RTTrPCpp::TrackableDefault>(
                "Test" + std::to_string(rand() % 999));

        constexpr int packetCount = 7;
        for (int i = 0; i < moduleCount; i++)
        {
            std::shared_ptr<RTTrPCpp::ModuleGeneric> module;

            if (i % packetCount == 0)
            {
                module = std::make_shared<RTTrPCpp::TrackedPointPos>(
                    ModuleGenerator::generateTrackedPointPos());
            }
            else if (i % packetCount == 1)
            {
                module = std::make_shared<RTTrPCpp::CentroidPos>(
                    ModuleGenerator::generateCentroidPos());
            }
            else if (i % packetCount == 2)
            {
                module = std::make_shared<RTTrPCpp::CentroidPosAccVel>(
                    ModuleGenerator::generateCentroidPosAccVel());
            }
            else if (i % packetCount == 3)
            {
                module = std::make_shared<RTTrPCpp::TrackedPointPosAccVel>(
                    ModuleGenerator::generateTrackedPointPosAccVel());
            }
            else if (i % packetCount == 4)
            {
                module = std::make_shared<RTTrPCpp::OrientationEuler>(
                    ModuleGenerator::generateOrientationEuler());
            }
            else if (i % packetCount == 5)
            {
                module = std::make_shared<RTTrPCpp::OrientationQuaternion>(
                    ModuleGenerator::generateOrientationQuaternion());
            }
            else if (i % packetCount == 6)
            {
                module = std::make_shared<RTTrPCpp::ZoneCollision>(
                    ModuleGenerator::generateZoneCollision());
            }

            trackable->addModule(module);
        }

        return trackable;
    }
private:
    static int g_count;
};

int TrackableGenerator::g_count = 1;