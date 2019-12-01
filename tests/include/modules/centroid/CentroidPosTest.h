#pragma once
#include <modules/Modules.h>

TEST(ModuleCentroidPos, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    CentroidPos module(
        static_cast<uint16_t>(rand()),
        RTTrPCpp::Position::generateRandom());

    CentroidPos moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "CentroidPos copy failed";
}

TEST(ModuleCentroidPos, Serialize)
{
    using namespace RTTrPCpp;

    CentroidPos module = ModuleGenerator::generateCentroidPos();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    CentroidPos moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "CentroidPos deserialization failed";
}

TEST(ModuleCentroidPos, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 29;

    std::vector<uint8_t> buffer;
    std::vector<CentroidPos> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateCentroidPos());
    }

    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        ASSERT_EQ(module.toBytes(&buffer[start]), module.getSize());
    }

    ASSERT_EQ(count * packetSize, buffer.size());

    std::vector<CentroidPos> moduleCopies;

    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(CentroidPos(&buffer[packetSize * i]));
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}