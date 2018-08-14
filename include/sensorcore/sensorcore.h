#ifndef sensorcore_h
#define sensorcore_h

/**
 * Represents a three-dimensional point in cartesian space relative to a known origin.
 */
struct CartesianPoint {
  double x;             /**< The x-component of the point. */
  double y;             /**< The y-component of the point. */
  double z;             /**< The z-component of the point. */
  /**
   * Creates a default-intialized point containing zero as each of its components.
   */
  CartesianPoint(): x(0.0), y(0.0), z(0.0) {};
  /**
   * Creates a CartesianPoint with the passed values.
   *
   * @param x The x-component of the point.
   * @param y The y-component of the point.
   * @param z The z-component of the point.
   */
  CartesianPoint(double x, double y, double z): x(x), y(y), z(z) {};
};


/**
 * Represents a three-dimensional vector in cartesian space relative to a known origin.
 */
typedef CartesianPoint CartesianVector;


/**
 * Represents a three-dimensional point in an image.
 *
 * A sample is also known as a column or as the x-direction of an image.
 * A line is also known as a row or as the y-direction of an image.
 * A band is also known as the z-direction of an image.
 */
struct ImagePoint {
  double sample;    /**< The sample (i.e. column, x) component of an image. */
  double line;      /**< The line (i.e. row, y) component of an image. */
  double band;      /** < The band (i.e. z) component of an image. */
  /**
   * Creates a default-intialized point containing zero as each of its components.
   *
   * @param sample The sample for the ImagePoint.
   * @param line The line for the ImagePoint.
   * @param band The band for the ImagePoint.
   */
  ImagePoint(): sample(0.0), line(0.0), band(0.0) {};
  /**
   * Creates an ImagePoint with the passed values.
   */
  ImagePoint(double sample, double line, double band): sample(sample), line(line), band(band) {};
};

#endif