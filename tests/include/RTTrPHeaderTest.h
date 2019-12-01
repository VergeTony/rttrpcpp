#pragma once
#include <rttrpcpp/RTTrPM.h>
#include <trackables/Trackables.h>

TEST(RTTrPHeader, Deserialize)
{
    using namespace RTTrPCpp;

    std::vector<std::shared_ptr<RTTrPCpp::TrackableDefault>> trackables = {
        TrackableGenerator::generateTrackable(1),
        TrackableGenerator::generateTrackable(10),
        TrackableGenerator::generateTrackable(100)
    };

    RTTrPM rttrpm(static_cast<uint32_t>(0));

    for (auto &trackable : trackables)
    {
        rttrpm.addTrackable(trackable);
    }

    std::vector<uint8_t> buffer(rttrpm.getSize());

    rttrpm.toBytes(&buffer[0]);

    RTTrPHeader rttrheader(&buffer[0]);

    ASSERT_EQ(rttrpm, rttrheader) << "Deserialize RTTrPHeader Failed";
}

TEST(RTTrPHeader, DeserializeFromHeader)
{
    using namespace RTTrPCpp;

    std::vector<std::shared_ptr<RTTrPCpp::TrackableDefault>> trackables = {
        TrackableGenerator::generateTrackable(1),
        TrackableGenerator::generateTrackable(10),
        TrackableGenerator::generateTrackable(100)
    };

    RTTrPM rttrpm(static_cast<uint32_t>(0));

    for (auto &trackable : trackables)
    {
        rttrpm.addTrackable(trackable);
    }

    std::vector<uint8_t> buffer(rttrpm.getSize());
    rttrpm.toBytes(&buffer[0]);

    RTTrPType type = RTTrPHeader::getTypeFromBytes(&buffer[0]);

    ASSERT_EQ(type, rttrpm.getRTTrPType()) << "Unable to read RTTrPHeader";

    RTTrPM receivedPacket(&buffer[0]);

    ASSERT_EQ(rttrpm, receivedPacket) << "Deserialize RTTrPM Failed";
}