#include "SensorUtils.h"

#include <armadillo>
#include <iostream>
#include <iomanip>
#include <vector>

double PhaseAngle(vector<double>& instrumentPosition,vector<double>& sunPosition) {
    return 0.0;
}



/**
 * @brief EmissionAngle
 * @author Tyler Wilson
 * @param observerBodyFixedPosition
 * @param groundPtIntersection
 * @param surfaceNormal
 * @return The angle of emission (in radians)
 */

double EmissionAngle(const std::vector<double>  &observerBodyFixedPosition,
                     const std::vector<double> &groundPtIntersection,
                     const std::vector<double> &surfaceNormal) {

  arma::dvec surfacePoint(groundPtIntersection);
  arma::dvec surfacePointNormal(surfaceNormal);
  arma::dvec bodyFixedPosition(observerBodyFixedPosition);

  arma::dvec lookVec = bodyFixedPosition - surfacePoint;

  arma::dvec normLookVec = arma::normalise(lookVec);

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
