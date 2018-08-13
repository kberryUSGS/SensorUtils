#include "SensorUtils.h"

#include <cfloat>
#include <cmath>

#include <iostream>
#include <vector>

#include <armadillo>

using namespace std;

using namespace arma;


/**
 * Computes the resolution of a sensor based on distance from the point-of-interest, focal
 * length, pixel pitch (size of pixel), and summing mode (scale factor).
 *
 * Resolution is computed as meters per pixel. If any of the input parameters are negative,
 * this function returns 0.0. If focalLength or pixelPitch is 0.0, this function returns 0.0.
 *
 * @author Ian Humphrey
 *
 * @param distance Distance between the sensor and the point-of-interest (km)
 * @param focalLength Focal length of the sensor (mm)
 * @param pixelPitch Size of a pixel on the sensor (mm)
 * @param summing Summing mode of the sensor
 *
 * @return double Returns the resolution of the distance between the sensor and the
 *                point-of-interest in meters/pixel. Returns 0.0 if any parameter is
 *                negative.
 */
double resolution(double distance, double focalLength, double pixelPitch, double summing) {
  // Make sure none of inputs are negative, and focalLength and pixelPitch can not be zero,
  // so we don't divide by zero.
  if (distance < 0.0 || focalLength <= 0.0 || pixelPitch <= 0.0 || summing < 0.0) {
    return 0.0;
  }

  return (distance / (focalLength / pixelPitch)) * summing * 1000.0;
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

double PhaseAngle(const std::vector<double> &observerBodyFixedPosition,
                                const std::vector<double> &illuminatorBodyFixedPosition,
                                const std::vector<double> &surfaceIntersection) {

    //convert the vector to an arma::vec
    arma::vec observer = arma::zeros<arma::vec>(3);
    observer = arma::conv_to<arma::vec>::from(observerBodyFixedPosition);

    //convert the illuminatorBodyFixedPosition vector to an arma::vec
    arma::vec illuminator = arma::zeros<arma::vec>(3);
    illuminator = arma::conv_to<arma::vec>::from(illuminatorBodyFixedPosition);

    //convert the surfaceIntersection vector to an arma::vec
    arma::vec surface = arma::zeros<arma::vec>(3);
    surface = arma::conv_to<arma::vec>::from(surfaceIntersection);

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

    double cos_angle=arma::dot(normSurfaceToObserver,normSurfaceToSun);

    if(cos_angle >= 1.0) return 0.0;
    if(cos_angle <= -1.0) return M_PI;

    return acos(cos_angle);
}


/**
 * @brief computeRADec
 * @author Tyler Wilson
 * @param  rectangularCoords:  The coordinates of the spacecraft in Cartesian coords
 * (body-fixed, J2000,...)
 * @return [RightAscension, Declination] in Radians
 */
vector <double> computeRADec(const vector<double> rectangularCoords) {
  vector<double> radiusLatLong = rect2lat(rectangularCoords);

  vector<double> RADec {radiusLatLong[2],radiusLatLong[1]};
  if (RADec[0] <0.0) {
    RADec[0] += 2*M_PI;
  }
  return RADec;
}


/**
 * @brief EmissionAngle
 * @author Tyler Wilson
 * @param observerBodyFixedPosition
 * @param groundPtIntersection
 * @param surfaceNormal
 * @return The angle of emission (in radians)
 */
double EmissionAngle(const vector<double>  &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal) {

  vec surfacePoint(groundPtIntersection);
  vec surfacePointNormal(surfaceNormal);
  vec bodyFixedPosition(observerBodyFixedPosition);

  vec lookVec = bodyFixedPosition - surfacePoint;

  vec normLookVec = normalise(lookVec);

  double cos_theta = dot(normLookVec,surfacePointNormal);


  //If cos(\theta) >= 1.0, there was some small rounding error
  //but the angle between the two vectors will be close to 0.0
  //Likewise, if cos(\theta) <=-1.0, a rounding error occurred
  //and the angle will be close to \pi radians.  To see
  //why, consult a plot of the acos function
  if (cos_theta >= 1.0) {
    return 0.0;
  }

  //IF cos(\theta) < -1.0,
  if (cos_theta <= -1.0) {
    return M_PI;
  }
  return acos(cos_theta);
}


/**
 * @brief offNadirAngle:  The angle (in radians) between the look vector of the spacecraft
 * and the look vector of the spacecraft at nadir (when the spacecraft is directly
 * over the intersection point of the look vector with the target).
 * @author Tyler Wilson
 * @param observerBodyFixedPosition
 * @param groundPtIntersection
 * @param surfaceNormal
 * @return The offnadir angle in radians
 */
double offNadirAngle(const vector<double> &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal) {
  vec surfacePoint(groundPtIntersection);
  vec bodyFixedPosition(observerBodyFixedPosition);
  double emissionAngle = EmissionAngle(observerBodyFixedPosition,groundPtIntersection,surfaceNormal);
  vec normalSurface = normalise(surfacePoint,2);
  vec normalBodyFixed = normalise(bodyFixedPosition,2);
  double theta = acos(dot(normalSurface,normalBodyFixed));
  double piMinusEmission = M_PI - emissionAngle;
  return M_PI - (theta+piMinusEmission);
}


/**
 * This method calculates the position of the illuminator with respect
 * to the observed body fixed position. It requires a ground intersection point
 * and the illuminator direction vector.
 *
 * @author Jeannie Backer
 *
 * @param groundPointIntersection A point on the surface of the observed body,
 *                                in body fixed coordinate system.
 * @param illuminatorDirection An illuminator direction vector,
 *                             in illuminator center coordinate system.
 *
 * @return The position of the illuminator in body fixed coordinate system.
 */
arma::vec illuminatorPosition(const arma::vec &groundPointIntersection,
                              const arma::vec &illuminatorDirection) {
  // sun pos (center body to center sun)
  // is body fixed ground coordinated (center body to ground point)
  // minus the illumination direction (center sun to ground point)
  return groundPointIntersection - illuminatorDirection;
}
