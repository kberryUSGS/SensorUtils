#include "BiAxialEllipsoid.h"

#include <vector>

#include "sensorcore.h"
#include "SensorMath.h"

/**
 * Construct a bi-axial ellipsoid with passed majorAxis and minorAxis.
 *
 * @param majorAxis The major axis of the ellipsoid
 * @param minorAxis The minor axis of the ellipsoid
 */
BiAxialEllipsoid::BiAxialEllipsoid(double majorAxis, double minorAxis): 
    m_majorAxis(majorAxis), m_minorAxis(minorAxis) {
}


/**
 * IS NOT CURRENTLY IMPLEMENTED -- RETURNS STD::VECTOR (LEN 1) WITH CARTESIANPOINT{0,0,0}
 */
std::vector<CartesianPoint> BiAxialEllipsoid::intersect(CartesianVector direction,
                                                        CartesianPoint origin) {
  return std::vector<CartesianPoint>{CartesianPoint{0,0,0}};
}


/**
 * IS NOT FULLY SUPPORTED -- RETURNS SURFACE NORMAL OF SPHERE
 */
CartesianVector BiAxialEllipsoid::surfaceNormal(CartesianPoint groundPoint) {
  return sensormath::normalize(groundPoint);
}