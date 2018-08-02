#include "SensorUtils.h"

#include <gtest/gtest.h>

TEST(SensorUtils, PhaseAngle) {
   vector<double> instrumentPosition{0, 0, 0};
   vector<double> sunPosition{0, 0, 0};
   EXPECT_EQ(0, PhaseAngle(instrumentPosition, sunPosition));
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
