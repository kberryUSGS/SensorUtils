#include "sensorcore.h"
#include "SensorMath.h"

#include <cmath>
#include <armadillo>
#include <gtest/gtest.h>

using namespace sensormath; 

TEST(cartesianToVec, point) {
  CartesianPoint point(1.0, 2.0, 3.0);
  arma::vec armaPoint = cartesianToVec(point);
  EXPECT_DOUBLE_EQ(1.0, armaPoint[0]);
  EXPECT_DOUBLE_EQ(2.0, armaPoint[1]);
  EXPECT_DOUBLE_EQ(3.0, armaPoint[2]);
}


TEST(cartesianToVec, vec) {
  CartesianVector point(1.0, 2.0, 3.0);
  arma::vec armaPoint = cartesianToVec(point);
  EXPECT_DOUBLE_EQ(1.0, armaPoint[0]);
  EXPECT_DOUBLE_EQ(2.0, armaPoint[1]);
  EXPECT_DOUBLE_EQ(3.0, armaPoint[2]);
}


TEST(imageToVec, image) {
  ImagePoint point(1.0, 2.0, 3.0);
  arma::vec armaPoint = imageToVec(point);
  EXPECT_DOUBLE_EQ(1.0, armaPoint[0]);
  EXPECT_DOUBLE_EQ(2.0, armaPoint[1]);
  EXPECT_DOUBLE_EQ(3.0, armaPoint[2]);
}


TEST(vecToImage, image) {
  arma::vec armaPoint{1.0, 2.0, 3.0}; 
  ImagePoint image = vecToImage(armaPoint); 
  EXPECT_DOUBLE_EQ(1.0, image.sample);
  EXPECT_DOUBLE_EQ(2.0, image.line);
  EXPECT_DOUBLE_EQ(3.0, image.band);
}


TEST(vecToCartesian, vec) {
  arma::vec armaPoint{1.0, 2.0, 3.0}; 
  CartesianVector cartesianVec = vecToCartesian(armaPoint);
  EXPECT_DOUBLE_EQ(1.0, cartesianVec.x);
  EXPECT_DOUBLE_EQ(2.0, cartesianVec.y);
  EXPECT_DOUBLE_EQ(3.0, cartesianVec.z);
}


/**
 * Test distance() function.
 */
TEST(distance, simpleDistance) {
  // Easy hand-calculation: sqrt(1^2 + 2^2 + 2^2) ==> sqrt(9) ==> 3
  CartesianPoint fartherPoint(10, 10, 10);
  CartesianPoint closerPoint(9, 8, 8);
  EXPECT_DOUBLE_EQ(3.0, sensormath::distance(fartherPoint, closerPoint));
  EXPECT_DOUBLE_EQ(3.0, sensormath::distance(closerPoint, fartherPoint));
}


TEST(distance, zero) {
  // Zero distance
  CartesianVector zero(0.0, 0.0, 0.0);
  EXPECT_DOUBLE_EQ(0.0, sensormath::distance(zero, zero));   
}


TEST(angle, zero) {
  CartesianVector zero(0.0, 0.0, 0.0);
  EXPECT_NEAR(0.0, sensormath::angle(zero, zero),1e-4);   
}


TEST(angle, orthogonal) {
  CartesianVector ray1(1.0, 2.0, 0.0);
  CartesianVector ray2(2.0, -1.0, 10.0);
  EXPECT_NEAR(M_PI/2, sensormath::angle(ray1, ray2),1e-4);   
}


// TODO: update rect2lat and lat2rect tests after modified for sensorcore.h definitions
// (not part of EPIC 0.1) 

//These are unit test values which came from
//the cspice implementation of this function
TEST(rect2lat,cspiceunittest) {
  const double rad2deg = 180.0/M_PI;
  vector<double> coords{1.0,1.0,1.0};
  vector<double> radiusLatLong;

  radiusLatLong = sensormath::rect2lat(coords);
  EXPECT_NEAR(1.7320,radiusLatLong[0],1e-4);
  EXPECT_NEAR(35.2643,rad2deg*radiusLatLong[1],1e-4);
  EXPECT_NEAR(45.0,rad2deg*radiusLatLong[2],1e-4);
}


TEST(rect2lat,zerovector) {
  const double rad2deg = 180.0/M_PI;
  vector<double> coords{0.0,0.0,0.0};
  vector<double> radiusLatLong;

  radiusLatLong = sensormath::rect2lat(coords);
  EXPECT_NEAR(0.0,radiusLatLong[0],1e-4);
  EXPECT_NEAR(0.0,rad2deg*radiusLatLong[1],1e-4);
  EXPECT_NEAR(0.0,rad2deg*radiusLatLong[2],1e-4);
}

TEST(rect2lat,zeroXCoord) {
  const double rad2deg = 180.0/M_PI;
  vector<double> coords{0.0,1.0,0.0};
  vector<double> radiusLatLong;

  radiusLatLong = sensormath::rect2lat(coords);
  EXPECT_NEAR(1.0,radiusLatLong[0],1e-4);
  EXPECT_NEAR(0.0,rad2deg*radiusLatLong[1],1e-4);
  EXPECT_NEAR(90.0,rad2deg*radiusLatLong[2],1e-4);
}


TEST(lat2rect,zeroXCoord) {
  const double rad2deg = 180.0/M_PI;
  vector<double> spherical{0.0,0.0,0.0};
  vector<double> cartesian = sensormath::lat2rect(spherical);

  EXPECT_NEAR(0.0,cartesian[0],1e-4);
  EXPECT_NEAR(0.0,cartesian[1],1e-4);
  EXPECT_NEAR(0.0,cartesian[1],1e-4);
}


TEST(lat2rect,AlphaCentauri) {
  const double deg2rad = M_PI/180.0;
  //coordinates are returned in heliocentric-xyz parsecs
  //The truth data was taken from SIMBAD:
  //http://simbad.u-strasbg.fr/simbad/
  vector<double> spherical{1.32483,deg2rad*219.90205833,-60.83399269*deg2rad};
  vector<double> cartesian = sensormath::lat2rect(spherical);

  EXPECT_NEAR(-0.495304,cartesian[0],1e-4);
  EXPECT_NEAR(-0.414169,cartesian[1],1e-4);
  EXPECT_NEAR(-1.15686,cartesian[2],1e-4);
}

