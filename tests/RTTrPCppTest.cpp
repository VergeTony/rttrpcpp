#include <cstdio>
#include <gtest/gtest.h>

#include <modules/centroid/CentroidPosTest.h>
#include <modules/centroid/CentroidPosAccVelTest.h>
#include <modules/trackedpoint/TrackedPointPosTest.h>
#include <modules/trackedpoint/TrackedPointPosAccVelTest.h>
#include <modules/orientation/OrientationEulerTest.h>
#include <modules/orientation/OrientationQuaternionTest.h>
#include <modules/zone/ZoneCollisionTest.h>
#include <trackables/TrackableDefaultTest.h>
#include <RTTrPHeaderTest.h>
#include <RTTrPMTest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}