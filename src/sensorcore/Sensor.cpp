#include "Sensor.h"

#include <cmath>
#include <string>
#include <vector>

#include "sensorcore.h"
#include "SensorMath.h"
#include "ShapeModel.h"
#include "ShapeModelFactory.h"
#include "SensorModelFactory.h"

Sensor::Sensor(const std::string &metaData, const std::string &sensorName) {
  m_shapeModel = ShapeModelFactory::create("test");
  m_sensorModel = SensorModelFactory::create("test"); 
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
   * @param groundPoint The point on the body to calculate the phase angle at 
   *  
   * @return @b double Phase angle, in radians.
   */
double Sensor::phaseAngle(const CartesianPoint &groundPoint) {
  CartesianPoint input = groundPoint; 
  ImagePoint imagePoint = m_sensorModel->groundToImage(input); 
  CartesianPoint sensorPosition = m_sensorModel->getSensorPosition(imagePoint); 
  CartesianPoint sunPosition = illuminatorPosition(imagePoint);

  CartesianVector surfaceToObserver = sensormath::subtract(groundPoint, sensorPosition); 
  CartesianVector surfaceToSun = sensormath::subtract(groundPoint, sunPosition); 
  // why would we need to normalize? 

  double cos_angle = sensormath::dot(surfaceToObserver, surfaceToSun);

  if(cos_angle >= 1.0) return 0.0;
  if(cos_angle <= -1.0) return M_PI;

  return acos(cos_angle);
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
   * @param imagePoint The point on the image to calculate the phaseAngle at. 
   *  
   * @return @b double Phase angle, in radians.
   */
double Sensor::phaseAngle(const ImagePoint &imagePoint) {
  ImagePoint input = imagePoint; 
  CartesianPoint groundPoint = m_sensorModel->imageToGround(input); 
  CartesianPoint sensorPosition = m_sensorModel->getSensorPosition(input); 
  CartesianPoint sunPosition = illuminatorPosition(input);

  CartesianVector surfaceToObserver = sensormath::subtract(groundPoint, sensorPosition); 
  CartesianVector surfaceToSun = sensormath::subtract(groundPoint, sunPosition); 
  // why would we need to normalize? 

  double cos_angle = sensormath::dot(surfaceToObserver, surfaceToSun);

  if(cos_angle >= 1.0) return 0.0;
  if(cos_angle <= -1.0) return M_PI;

  return acos(cos_angle);
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
CartesianPoint Sensor::illuminatorPosition(ImagePoint imagePoint) {
  // sun pos (center body to center sun)
  // is body fixed ground coordinated (center body to ground point)
  // minus the illumination direction (center sun to ground point)
  CartesianPoint groundPoint = m_sensorModel->imageToGround(imagePoint);
  CartesianVector illuminatorDirection = m_sensorModel->getIlluminationDirection(groundPoint); 

  return sensormath::subtract(illuminatorDirection, groundPoint);
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
