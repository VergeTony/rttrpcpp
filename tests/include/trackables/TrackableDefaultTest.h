#pragma once
#include <modules/Modules.h>
#include <rttrpcpp/trackables/TrackableDefault.h>

TEST(TrackableDefault, Create)
{
    using namespace RTTrPCpp;

    TrackableDefault trackable("Test");
    trackable.addModule(
        std::make_shared<TrackedPointPos>(
            ModuleGenerator::generateTrackedPointPos()));

    ASSERT_EQ(39, trackable.getSize());
}

TEST(TrackableDefault, Serialize)
{
    using namespace RTTrPCpp;

    TrackableDefault trackable("Test");

    trackable.addModule(
        std::make_shared<TrackedPointPos>(
            ModuleGenerator::generateTrackedPointPos()));

    trackable.addModule(
        std::make_shared<CentroidPos>(
            ModuleGenerator::generateCentroidPos()));

    std::vector<uint8_t> buffer(trackable.getSize());

    trackable.toBytes(&buffer[0]);

    TrackableDefault trackableCopy(&buffer[0]);

    ASSERT_EQ(trackable, trackableCopy) << "Deserialization failed";
}