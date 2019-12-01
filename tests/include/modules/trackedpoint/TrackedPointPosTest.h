#pragma once
#include <modules/Modules.h>

TEST(ModuleTrackedPointPos, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    TrackedPointPos module(
        static_cast<uint16_t>(rand()),
        RTTrPCpp::Position::generateRandom(),
        static_cast<uint8_t>(rand()));

    TrackedPointPos moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "TrackedPointPos copy failed";
}

TEST(ModuleTrackedPointPos, Serialize)
{
    using namespace RTTrPCpp;

    TrackedPointPos module = ModuleGenerator::generateTrackedPointPos();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    TrackedPointPos moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "TrackedPointPos deserialization failed";
}

TEST(ModuleTrackedPointPos, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 30;

    std::vector<uint8_t> buffer;
    std::vector<TrackedPointPos> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateTrackedPointPos());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<TrackedPointPos> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(TrackedPointPos(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}