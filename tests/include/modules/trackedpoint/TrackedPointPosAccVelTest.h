#pragma once
#include <modules/Modules.h>

TEST(ModuleTrackedPointPosAccVel, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    TrackedPointPosAccVel module(
        static_cast<uint8_t>(rand()),
        RTTrPCpp::Position::generateRandom(),
        RTTrPCpp::Acceleration::generateRandom(),
        RTTrPCpp::Velocity::generateRandom());

    TrackedPointPosAccVel moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "TrackedPointPosAccVel copy failed";
}

TEST(ModuleTrackedPointPosAccVel, Serialize)
{
    using namespace RTTrPCpp;

    TrackedPointPosAccVel module = ModuleGenerator::generateTrackedPointPosAccVel();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    TrackedPointPosAccVel moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "TrackedPointPosAccVel deserialization failed";
}

TEST(ModuleTrackedPointPosAccVel, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 52;

    std::vector<uint8_t> buffer;
    std::vector<TrackedPointPosAccVel> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateTrackedPointPosAccVel());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<TrackedPointPosAccVel> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(TrackedPointPosAccVel(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}