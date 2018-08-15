#include "Sensor.h"

#include <cmath>
#include <string>
#include <vector>

#include "sensorcore.h"
#include "SensorMath.h"

Sensor::Sensor(const std::string &metaData, const std::string &sensorName) {
}


/**
 * Computes declination (in radians) on the celestial sphere for a given look direction.
 *
 * @param vector The look direction to project onto the celestial sphere.
 *
 * @return Returns the declination in radians.
 */
double Sensor::declination(const CartesianVector &vector) {
  std::vector<double> cartesianVector{vector.x, vector.y, vector.z};
  std::vector<double> radiusRaDec = sensormath::rect2lat(cartesianVector);
  return radiusRaDec[1];
}


double Sensor::emissionAngle(const CartesianPoint &groundPoint) {
  return 0.0;
}


double Sensor::emissionAngle(const ImagePoint &imagePoint) {
  return 0.0;
}


double Sensor::phaseAngle(const CartesianPoint &groundPoint) {
  return 0.0;
}


double Sensor::phaseAngle(const ImagePoint &imagePoint) {
  return 0.0;
}


/**
 * Computes right ascension (in radians) on the celestial sphere for a given look direction.
 *
 * @param vector The look direction to project onto the celestial sphere.
 *
 * @return Returns the right ascension in radians.
 */
double Sensor::rightAscension(const CartesianVector &vector) {
  std::vector<double> cartesianVector{vector.x, vector.y, vector.z};
  std::vector<double> radiusRaDec = sensormath::rect2lat(cartesianVector);
  if (radiusRaDec[2] < 0.0) {
    radiusRaDec[2] += 2 * M_PI;
  }
  return radiusRaDec[2];
}
