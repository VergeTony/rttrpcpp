#pragma once
#include <modules/Modules.h>

TEST(ModuleCentroidPosAccVel, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    CentroidPosAccVel module(
        RTTrPCpp::Position::generateRandom(),
        RTTrPCpp::Acceleration::generateRandom(),
        RTTrPCpp::Velocity::generateRandom());

    CentroidPosAccVel moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "CentroidPosAccVel copy failed";
}

TEST(ModuleCentroidPosAccVel, Serialize)
{
    using namespace RTTrPCpp;

    CentroidPosAccVel module = ModuleGenerator::generateCentroidPosAccVel();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    CentroidPosAccVel moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "CentroidPosAccVel deserialization failed";
}

TEST(ModuleCentroidPosAccVel, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 51;

    std::vector<uint8_t> buffer;
    std::vector<CentroidPosAccVel> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateCentroidPosAccVel());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<CentroidPosAccVel> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(CentroidPosAccVel(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}