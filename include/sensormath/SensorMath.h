#ifndef SensorMath_h
#define SensorMath_h

#include <armadillo>
#include <vector>

#include "sensorcore.h"

using namespace std; 
using namespace arma;

namespace sensormath {

  vec cartesianToVec(CartesianPoint point);
  vec imageToVec(ImagePoint point);

  CartesianVector vecToCartesian(vec vec); 
  ImagePoint vecToImage(vec vec);   

  double distance(CartesianPoint& point1, CartesianPoint& point2); 

  double angle(CartesianVector ray1, CartesianVector ray2); 

  // TODO: convert rect2lat and lat2rect to use CartesianPoints and CartesianVectors
  vector<double> rect2lat(const vector<double> rectangularCoords);
  vector<double> lat2rect(vector<double> sphericalCoords);
}
#endif
