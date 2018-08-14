#include "SensorUtils.h"

#include <cmath>
#include <gtest/gtest.h>

/**
 * Test resolution() function
 */
TEST(resolution, allPositive) {
  double distance = 10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = 0.1; // mm
  double summing = 1.0; // no summing (no binning)
  EXPECT_DOUBLE_EQ(2.0, resolution(distance, focalLength, pixelPitch, summing)); 
}

TEST(resolution, summingGreaterThanOne) {
  double distance = 10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = 0.1; // mm
  double summing = 2.0; // summing of 2 pixels together (losing resolution)
  EXPECT_DOUBLE_EQ(4.0, resolution(distance, focalLength, pixelPitch, summing));
}

TEST(resolution, negativeDistance) {
  // Negative distance
  double distance = -10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = 0.1; // mm
  double summing = 1.0; // no summing (no binning)
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, focalLength, pixelPitch, summing));
}

TEST(resolution, negativeFocalLength) {
  // Negative focal length
  double distance = 10.0; // km
  double focalLength = -500; // mm
  double pixelPitch = 0.1; // mm
  double summing = 1.0; // no summing (no binning)
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, focalLength, pixelPitch, summing));
}

TEST(resolution, negativePixelPitch) {
  // Negative pixel pitch
  double distance = 10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = -0.1; // mm
  double summing = 1.0; // no summing (no binning)
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, focalLength, pixelPitch, summing));
}

TEST(resolution, negativeSumming) {
  // Negative summing
  double distance = 10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = 0.1; // mm
  double summing = -1.0; // no summing (no binning)
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, focalLength, pixelPitch, summing));
}

TEST(resolution, zeroDivisors) {
  double distance = 10.0; // km
  double focalLength = 500; // mm
  double pixelPitch = 0.0; // mm
  double summing = 1.0; // no summing (no binning)
  // Zero pixel pitch
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, focalLength, pixelPitch, summing));
  // Zero focal length
  EXPECT_DOUBLE_EQ(0.0, resolution(distance, 0.0, 1.0, summing));
}

TEST(EmissionAngle,zerosForAllInputs) {

  vector<double> observerBodyFixedPosition{0.0,0.0,0.0};
  vector<double> groundPtIntersection{0.0,0.0,0.0};
  vector<double> surfaceNormal{0.0,0.0,0.0};
  EXPECT_NEAR(M_PI/2.0, EmissionAngle(observerBodyFixedPosition, groundPtIntersection,surfaceNormal),1e-5);

 }

TEST(EmissionAngle,lookVectorSameAsNormal) {

  vector<double> observerBodyFixedPosition3{2.0,0.0,0.0};
  vector<double> groundPtIntersection3{1.0,0.0,0.0};
  vector<double> surfaceNormal3{1.0,0.0,0.0};
  EXPECT_NEAR(0.0,EmissionAngle(observerBodyFixedPosition3, groundPtIntersection3,surfaceNormal3),1e-5);


 }

TEST(EmissionAngle,lookVector180FromNormal) {

  vector<double> observerBodyFixedPosition4{1.0,1.0,1.0};
  vector<double> groundPtIntersection4{0.0,0.0,0.0};
  vector<double> surfaceNormal4{-2.0,-2.0,2.0};
  EXPECT_NEAR(M_PI,EmissionAngle(observerBodyFixedPosition4, groundPtIntersection4,surfaceNormal4),1e-5);
 }

TEST(SensorUtils, PhaseAngle) {

   vector<double> instrumentPosition1{-1, 0, 0};
   vector<double> sunPosition1{1, 0, 0};
   vector<double> surfaceIntersection1{0, 0, 0};
   EXPECT_EQ(M_PI, PhaseAngle(instrumentPosition1, sunPosition1, surfaceIntersection1));


   vector<double> instrumentPosition2{0, 1, 0};
   vector<double> sunPosition2{0, 1, 0};
   vector<double> surfaceIntersection2{0, 0, 0};
   EXPECT_EQ(0, PhaseAngle(instrumentPosition2, sunPosition2, surfaceIntersection2));

   vector<double> instrumentPosition3{1, 1, 0};
   vector<double> sunPosition3{-1, 1, 0};
   vector<double> surfaceIntersection3{0, 0, 0};
   EXPECT_EQ(M_PI/2.0, PhaseAngle(instrumentPosition3, sunPosition3, surfaceIntersection3));


}

/**
 * Testing general case for illuminatorPosition method.
 */
TEST(illuminatorPosition, SensorUtils) {

   vector<double> surfaceIntersection{0, 1, 0};
   vector<double> illuminatorDirection{-1, 0, 1};
   vector<double> sunPosition{1, 1, -1};
   vector<double> illumPos = arma::conv_to< std::vector<double> >::from(illuminatorPosition(surfaceIntersection, 
                                                                                            illuminatorDirection));
   EXPECT_EQ(sunPosition, illumPos);

}


TEST(computeRADec,AlphaCentauri) {
  const double rad2deg = 180.0/M_PI;
  //coordinates are given in heliocentric-xyz parsecs
  //The truth data was taken from SIMBAD:
  //http://simbad.u-strasbg.fr/simbad/
  vector<double> coords{-0.495304,-0.414169,-1.15686};
  vector<double> radec = computeRADec(coords);

  EXPECT_NEAR(219.90205833,rad2deg*radec[0],1e-4);
  EXPECT_NEAR(-60.83399269,rad2deg*radec[1],1e-4);
}


TEST(offNadirAngle,zeroVector) {
  const double rad2deg = 180.0/M_PI;


  vector<double> observerBodyFixedPosition{0.0,0.0,0.0};
  vector<double> groundPtIntersection{0.0,0.0,0.0};
  vector<double> surfaceNormal{0.0,0.0,0.0};
  double theta = offNadirAngle(observerBodyFixedPosition,groundPtIntersection,surfaceNormal);

  EXPECT_NEAR(0.0,rad2deg*theta,1e-4);
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
