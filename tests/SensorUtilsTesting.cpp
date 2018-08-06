#include "SensorUtils.h"

#include <gtest/gtest.h>

TEST(SensorUtils, EmissionAngle) {
   vector<double> observerBodyFixedPosition1{-2399.5377741187439824,-2374.0338295628557717,1277.6750059817834426};
   vector<double> groundPtIntersection1{-2123.3622582859998147,-2380.37178122360001,1194.6783966636000969};
   vector<double> surfaceNormal1{-0.62338400000000004919,-0.69883799999999995922,0.35073799999999999422};
   EXPECT_NEAR(0.81971651917135968102, EmissionAngle(observerBodyFixedPosition1, groundPtIntersection1,surfaceNormal1),1e-5);

   vector<double> observerBodyFixedPosition2{0.0,0.0,0.0};
   vector<double> groundPtIntersection2{0.0,0.0,0.0};
   vector<double> surfaceNormal2{0.0,0.0,0.0};
   EXPECT_NEAR(1.5707963267948966, EmissionAngle(observerBodyFixedPosition2, groundPtIntersection2,surfaceNormal2),1e-5);
}


TEST(SensorUtils, PhaseAngle) {
   vector<double> instrumentPosition{0, 0, 0};
   vector<double> sunPosition{0, 0, 0};
   EXPECT_EQ(0, PhaseAngle(instrumentPosition, sunPosition));
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
