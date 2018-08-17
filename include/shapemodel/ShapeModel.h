#ifndef ShapeModel_h
#define ShapeModel_h

#include <vector>

#include "sensorcore.h"

class ShapeModel {
  public:
    virtual ~ShapeModel() {};
    virtual std::vector<CartesianPoint> intersect(CartesianVector direction,
                                                  CartesianPoint origin) = 0;
    virtual CartesianVector surfaceNormal(CartesianPoint surfacePoint) = 0;
};

#endif