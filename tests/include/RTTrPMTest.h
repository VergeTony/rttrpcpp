#pragma once
#include <rttrpcpp/RTTrPM.h>
#include <trackables/Trackables.h>

TEST(RTTrPM, Serialize)
{
    using namespace RTTrPCpp;

    auto trackable = TrackableGenerator::generateTrackable(2);

    RTTrPM rttrpm(static_cast<uint32_t>(0));
    rttrpm.addTrackable(trackable);

    std::vector<uint8_t> buffer(rttrpm.getSize());

    rttrpm.toBytes(&buffer[0]);

    RTTrPM rttrpmCopy(&buffer[0]);

    ASSERT_EQ(rttrpm, rttrpmCopy) << "Serialize RTTrPM Failed";
}

// TEST(RTTrP, Serialize)
// {
//     using namespace RTTrPCpp;

//     auto trackable0 = TrackableGenerator::generateTrackable(10);
//     auto trackable1 = TrackableGenerator::generateTrackable(10);

//     RTTrP rttrp(0);
//     rttrp.addTrackable(trackable0);
//     rttrp.addTrackable(trackable1);

//     std::vector<uint8_t> buffer(rttrp.getSize());

//     rttrp.toBytes(&buffer[0]);

//     RTTrP rttrpCopy(1);
//     rttrpCopy.fromBytes(&buffer[0]);
// }