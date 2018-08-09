#include "SensorUtils.h"

#include <cfloat>


#include <iostream>
#include <vector>

#include <armadillo>

using namespace std;

using namespace arma;


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
 * @brief rect2lat:  Converts rectanglur coordinates to [R,RightAscension,Declination]
 *
 * Rectanglular Cartesian Coordinates are related to Spherical Coordinates by:
 *
 * (1) X/R = cos(Declination)cos(RightAscension)
 * (2) Y/R = cos(Declination)sin(RightAscension)
 * (3) Z/R = sin(Declination)
 *
 * Where R = [X^2 + Y^2 + Z^2]^(1/2)
 *
 * Dividing (2) by (1) and solving for RightAscension gives us:
 *
 * RightAscension = atan(Y/X)
 *
 * Declination can be solved directly:
 *
 * Declination = asin(Z/R)
 *
 *
 * @author Tyler Wilson
 * @param rectangularCoords
 * @return  Given a set of Cartesian Coordinates, returns [R,RightAscension,Declination] in Radians
 * (for the angles).
 */
vector<double> rect2lat(const vector<double> rectangularCoords){

  vector<double> radiusLatLong{0.0,0.0,0.0};
  vec coords(rectangularCoords);
  double maxCoord = abs(coords).max();

  //Ensures we don't have a zero vector (which is impossible if the norm > 0 )
  if (maxCoord > 0.0) {
    radiusLatLong[0] = norm(coords,2);
    //Declination = asin(Z/R)
    radiusLatLong[1] = asin(coords[2]/radiusLatLong[0]);
    //RightAscension = atan(Y/X)
    radiusLatLong[2] = atan2(coords[1],coords[0]);

  }

  return radiusLatLong;

 }


/**
 * @brief lat2rect
 * @author Tyler Wilson
 * @param sphericalCoords [R,RA,Declination], RA and Declination need to be given in radians.
 * @return Cartesian coordinates
 *
 */

vector<double> lat2rect(vector<double> sphericalCoords) {

  double R = sphericalCoords[0];
  double RA = sphericalCoords[1];
  double dec = sphericalCoords[2];


  vector<double> cartesian{0.0,0.0,0.0};
  cartesian[0] = R*cos(dec)*cos(RA);
  cartesian[1] = R*cos(dec)*sin(RA);
  cartesian[2] = R*sin(dec);

  return cartesian;

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


}
