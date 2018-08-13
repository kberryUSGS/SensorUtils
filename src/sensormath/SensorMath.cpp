#include <cfloat>
#include <cmath>

#include <iostream>
#include <vector>

#include <armadillo>

using namespace std;

using namespace arma;

/**
 * Computes the Euclidean distance in kilometers between two body-fixed positions.
 *
 * This function computes the Euclidean distance between a body-fixed observer vector and
 * a body-fixed surface intersection (ground point) vector.
 *
 * @author Ian Humphrey
 *
 * @param observerBodyFixedPosition Body-fixed XYZ coordinate of the observer (km)
 * @param surfaceIntersection Body-fixed XYZ coordinate of the intersection on the surface from
 *                            the look direction of the observer (km)
 *
 * @return double Returns the Euclidean distance (in kilometers)
 */
double distance(const vector<double>& observerBodyFixedPosition,
                const vector<double>& surfaceIntersection) {
  vec observerPosition(observerBodyFixedPosition);
  vec intersection(surfaceIntersection);
  vec distanceVector = observerPosition - intersection;
  return as_scalar(norm(distanceVector));
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
 * Where R = [X^2 + Y^2 + Z^2]^(1/2), where R is the radius of the sphere.
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
 * @param sphericalCoords [R,longitude,latitude], long/lat are given in radians.
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

