#ifndef BiAxialEllipsoid_h
#define BiAxialEllipsoid_h
#include "ShapeModel.h"

#include <vector>

#include "sensorcore.h"

class BiAxialEllipsoid : public ShapeModel {
  public:
    BiAxialEllipsoid(double majorAxis, double minorAxis);
    std::vector<CartesianPoint> intersect(CartesianVector direction, CartesianPoint origin);
    CartesianVector surfaceNormal(CartesianPoint groundPoint);
  private:
    double m_majorAxis; /**< Major axis of the ellipsoid */
    double m_minorAxis; /**< Minor axis of the ellipsoid */
};

#endif