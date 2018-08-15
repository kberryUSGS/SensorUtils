#include "SensorMath.h"

#include <cfloat>
#include <cmath>

using namespace std;
using namespace arma;

namespace sensormath {

  // cartesian point -> arma::vec
  vec cartesianToVec(CartesianPoint point) {
    return vec {point.x, point.y, point.z}; 
  }


  // arma::vec -> CartesianPoint
  CartesianVector vecToCartesian(vec vec) {
    return CartesianVector(vec[0], vec[1], vec[2]); 
  }


  // cartesian point -> arma::vec
  vec imageToVec(ImagePoint point) {
    return vec {point.sample, point.line, point.band}; 
  }


  // arma::vec -> ImagePoint
  ImagePoint vecToImage(vec vec) {
    return ImagePoint(vec[0], vec[1], vec[2]); 
  }


  // Calculates the angle between two vectors
  double angle(CartesianVector ray1, CartesianVector ray2) {
    if (approx_equal(cartesianToVec(ray1), cartesianToVec(ray2),
        "absdiff", 1e-4)) {
      return 0.0; 
    }

    return acos(norm_dot(cartesianToVec(ray1), cartesianToVec(ray2))); 
  }


  /**
   * Computes the Euclidean distance between two CartesianPoints in the units they are provided 
   * in.  
   *
   * @author Ian Humphrey
   *
   * @param point1 The first Cartesian Point to calculate the distance from. 
   * @param point2 The second Cartesian Point to calculate the distance to. 
   *
   * @return double Returns the Euclidean distance
   */
  double distance(CartesianPoint& point1,
                  CartesianPoint& point2) {
    vec point1Vector = cartesianToVec(point1);
    vec point2Vector = cartesianToVec(point2);
    vec distanceVector = point1Vector - point2Vector; 
    return as_scalar(norm(distanceVector));
  }


  /**
   * Compute the dot product of two vectors.
   *
   * @param vector1 The first CartesianVector.
   * @param vector2 The second CartesianVector.
   *
   * @return double Returns the computed dot product.
   */
  double dot(CartesianVector vector1, CartesianVector vector2) {
    return arma::dot(cartesianToVec(vector1), cartesianToVec(vector2));
  }


  /**
   * Normalizes a vector to a unit vector.
   *
   * @param vector The CartesianVector to normalize.
   *
   * @return CartesianVector Returns the normalized vector (unit vector).
   */
  CartesianVector normalize(CartesianVector vector) {
    vec normalizedVector = normalise(cartesianToVec(vector));
    return vecToCartesian(normalizedVector);
  }

  /**
   * Subtracts two vectors.
   *
   * @param vector1 The CartesianVector to subtract from (minuend).
   * @param vector2 The CartesianVector being subtracted (subtrahend).
   *
   * @return CartesianVector Returns the difference between vector1 and vector2.
   */
  CartesianVector subtract(CartesianVector vector1, CartesianVector vector2) {
    vec minuend = cartesianToVec(vector1);
    vec subtrahend = cartesianToVec(vector2);
    return vecToCartesian(minuend - subtrahend);
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
}
