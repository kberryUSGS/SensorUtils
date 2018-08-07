#include "SensorUtils.h"

#include "math.h"

#include <vector>

#include <armadillo>

using namespace std;


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

  arma::vec surfacePoint(groundPtIntersection);
  arma::vec surfacePointNormal(surfaceNormal);
  arma::vec bodyFixedPosition(observerBodyFixedPosition);

  arma::vec lookVec = bodyFixedPosition - surfacePoint;

  arma::vec normLookVec = arma::normalise(lookVec);

  double cos_theta = arma::dot(normLookVec,surfacePointNormal);


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


  return std::acos(cos_theta);



}
