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


/**
   * Computes and returns phase angle, in radians, given the positions of the
   * observer and illuminator.
   *
   * Phase Angle: The angle between the vector from the surface intersection point to
   * the observer (usually the spacecraft) and the vector from the surface intersection
   * point to the illuminator (usually the sun).
   *
   * @author Kaj Williams
   *
   * @param observerBodyFixedPosition  Three dimensional position of the observer,
   *                                   in the coordinate system of the target body.
   * @param illuminatorBodyFixedPosition Three dimensional position for the illuminator,
   *                                     in the body-fixed coordinate system.
   * @param surfaceIntersection Three dimensional position for the ground (surface intersection) point,
   *                                     in the body-fixed coordinate system.
   * @return @b double Phase angle, in radians.
   */
double Sensor::phaseAngle(const CartesianPoint &groundPoint) {

}


double Sensor::phaseAngle(const ImagePoint &imagePoint) {
  CartesianPoint &groundPoint = m_sensor->imageToGround(imagePoint); 
  CartesianPoint sensorPosition = m_sensor->getSensorPosition(imagePoint); 
  CartesianPoint illuminatorPosition = illuminatorPosition(CartesianPoint imagePoint);

  CartesianVector surfaceToObserver = sensormath::subtract(groundPoint, sensorPosition); 
  CartesianVector surfaceToSun = sensormath::subtract(groundPoint, illuminatorPosition); 
  // why would we need to normalize? 

  double cos_angle = sensormath::dot(surfaceToObserver, surfaceToSun);

  if(cos_angle >= 1.0) return 0.0;
  if(cos_angle <= -1.0) return M_PI;

  return acos(cos_angle);

/*
  // Convert the vector to an arma::vec
  arma::vec observer = sensormath::cartesianToVec(sensorPosition); 

  // Convert the illuminatorBodyFixedPosition vector to an arma::vec
  arma::vec illuminator = sensormath::cartesianToVec(illuminatorBodyFixedPosition);
  
  // Convert the surfaceIntersection vector to an arma::vec
  arma::vec surface = sensormath::cartesianToVec(groundPoint);
  
  // Get vector from surface point to observer and normalise it
  arma::vec surfaceToObserver = arma::zeros<arma::vec>(3);
  arma::vec normSurfaceToObserver = arma::zeros<arma::vec>(3);
  surfaceToObserver = observer - surface;
  normSurfaceToObserver = arma::normalise(surfaceToObserver);
  
  // Get vector from surface point to sun and normalise it
  arma::vec surfaceToSun = arma::zeros<arma::vec>(3);
  arma::vec normSurfaceToSun = arma::zeros<arma::vec>(3);
  surfaceToSun = illuminator - surface;
  normSurfaceToSun = arma::normalise(surfaceToSun);

  double cos_angle = arma::dot(normSurfaceToObserver, normSurfaceToSun);

  if(cos_angle >= 1.0) return 0.0;
  if(cos_angle <= -1.0) return M_PI;

  return acos(cos_angle); */ 
}


/**
 * This method calculates the position of the illuminator.
 *
 * @author Jeannie Backer
 *
 * @param CartesianPoint imagePoint The point in the image to calculate the illuminator 
 *                                  position at.
 *        
 * @return The position of the illuminator in body fixed coordinate system.
 */
CartesianPoint illuminatorPosition(CartesianPoint imagePoint) {
  // sun pos (center body to center sun)
  // is body fixed ground coordinated (center body to ground point)
  // minus the illumination direction (center sun to ground point)
  CartesianPoint groundPoint = m_sensor->imageToGround(imagePoint);
  CartesianVector illuminatorDirection = m_sensor->getIlluminationDirection(groundPoint); 

  return sensormath::subtract(illuminatorDirection, groundPointIntersection);
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
