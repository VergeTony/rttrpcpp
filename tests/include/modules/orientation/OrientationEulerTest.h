#pragma once
#include <modules/Modules.h>

TEST(ModuleOrientationEuler, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    OrientationEuler module(
        static_cast<uint16_t>(rand()),
        static_cast<uint16_t>(rand()),
        Euler::generateRandom());

    OrientationEuler moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "OrientationEuler copy failed";
}

TEST(ModuleOrientationEuler, Serialize)
{
    using namespace RTTrPCpp;

    OrientationEuler module = ModuleGenerator::generateOrientationEuler();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    OrientationEuler moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "OrientationEuler deserialization failed";
}

TEST(ModuleOrientationEuler, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 31;

    std::vector<uint8_t> buffer;
    std::vector<OrientationEuler> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateOrientationEuler());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<OrientationEuler> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(OrientationEuler(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}