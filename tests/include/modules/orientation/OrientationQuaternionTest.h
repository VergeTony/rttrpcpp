#pragma once
#include <modules/Modules.h>

TEST(ModuleOrientationQuaternion, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    OrientationQuaternion module(
        static_cast<uint16_t>(rand()),
        Quaternion::generateRandom());

    OrientationQuaternion moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "OrientationQuaternion copy failed";
}

TEST(ModuleOrientationQuaternion, Serialize)
{
    using namespace RTTrPCpp;

    OrientationQuaternion module = ModuleGenerator::generateOrientationQuaternion();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    OrientationQuaternion moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "OrientationQuaternion deserialization failed";
}

TEST(ModuleOrientationQuaternion, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 37;

    std::vector<uint8_t> buffer;
    std::vector<OrientationQuaternion> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateOrientationQuaternion());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<OrientationQuaternion> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(OrientationQuaternion(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}