#include <memory>
#include <string>

#include "sensorcore.h"
#include "SensorMath.h"
#include "ShapeModel.h"
#include "ShapeModelFactory.h"

#include <gtest/gtest.h>

TEST(BiAxialEllipsoid, intersect) {
  std::unique_ptr<ShapeModel> shape = ShapeModelFactory::create("test");
  CartesianVector lookDirection{1.0, 2.0, 3.0};
  CartesianPoint origin{3.0, 3.0, 3.0};
  CartesianPoint intersection = shape->intersect(lookDirection, origin)[0];
  EXPECT_DOUBLE_EQ(0.0, intersection.x);
  EXPECT_DOUBLE_EQ(0.0, intersection.y);
  EXPECT_DOUBLE_EQ(0.0, intersection.z);
}

TEST(BiAxialEllipsoid, sphereSurfaceNormal) {
  std::unique_ptr<ShapeModel> shape = ShapeModelFactory::create("sphere");
  CartesianVector normal = shape->surfaceNormal(CartesianPoint{-2.0, -2.0, 2.0});
  EXPECT_DOUBLE_EQ(-1.0/sqrt(3), normal.x);
  EXPECT_DOUBLE_EQ(-1.0/sqrt(3), normal.y);
  EXPECT_DOUBLE_EQ(1/sqrt(3), normal.z);
}