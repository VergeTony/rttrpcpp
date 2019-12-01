#pragma once
#include <modules/Modules.h>

TEST(ModuleZoneCollision, Copy)
{
    using namespace RTTrPCpp;

    srand(time(nullptr));

    std::string collisions;
    int count = static_cast<int>(rand() % 4) + 1;

    for (int i = 0; i < count; i++)
    {
        collisions += "$" + std::to_string(static_cast<int>(rand()));
    }

    ZoneCollision module(collisions);

    ZoneCollision moduleCopy;
    moduleCopy = module;

    ASSERT_EQ(module, moduleCopy) << "ZoneCollision copy failed";
}

TEST(ModuleZoneCollision, Serialize)
{
    using namespace RTTrPCpp;

    ZoneCollision module = ModuleGenerator::generateZoneCollision();

    std::vector<uint8_t> buffer;
    buffer.resize(module.getSize());
    ASSERT_EQ(module.toBytes(&buffer[0]), module.getSize());

    ZoneCollision moduleCopy(&buffer[0]);

    ASSERT_EQ(module, moduleCopy) << "ZoneCollision deserialization failed";
}

TEST(ModuleZoneCollision, SerializeMultiple)
{
    using namespace RTTrPCpp;

    constexpr int count = 100;
    constexpr size_t packetSize = 29;

    std::vector<uint8_t> buffer;
    std::vector<ZoneCollision> modules;

    for (int i = 0; i < count; i++)
    {
        modules.push_back(ModuleGenerator::generateZoneCollision());
    }

    size_t size = 0;
    for (auto &module : modules)
    {
        auto start = buffer.size();
        buffer.resize(buffer.size() + module.getSize());
        int ret = module.toBytes(&buffer[start]);
        ASSERT_EQ(ret, module.getSize());
        size += ret;
    }

    ASSERT_EQ(size, buffer.size());

    std::vector<ZoneCollision> moduleCopies;

    size_t start = 0;
    for (int i = 0; i < count; i++)
    {
        moduleCopies.push_back(ZoneCollision(&buffer[start]));
        start += moduleCopies.back().getSize();
    }

    for (int i = 0; i < count; i++)
    {
        ASSERT_EQ(modules[i], moduleCopies[i]);
    }
}