#include <gtest/gtest.h>

#include "sensorcore.h"
#include "Sensor.h"

TEST(declination, placeHodor) {
  Sensor sensor("test", "test");
  EXPECT_DOUBLE_EQ(0.0, sensor.declination(CartesianVector()));
}

TEST(emissionAngle, placeHodor) {
  Sensor sensor("test", "test");
  EXPECT_DOUBLE_EQ(0.0, sensor.emissionAngle(CartesianPoint()));
  EXPECT_DOUBLE_EQ(0.0, sensor.emissionAngle(ImagePoint()));
}

TEST(phaseAngle, placeHodor) {
  Sensor sensor("test", "test");
  EXPECT_DOUBLE_EQ(0.0, sensor.phaseAngle(CartesianPoint()));
  EXPECT_DOUBLE_EQ(0.0, sensor.phaseAngle(ImagePoint()));
}

TEST(rightAscension, placeHodor) {
  Sensor sensor("test", "test");
  EXPECT_DOUBLE_EQ(0.0, sensor.rightAscension(CartesianVector()));
}
