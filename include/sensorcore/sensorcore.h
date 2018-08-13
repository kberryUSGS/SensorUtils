#ifndef sensorcore_h
#define sensorcore_h

struct CartesianPoint {
  double x;
  double y;
  double z;
  CartesianPoint(): x(0.0), y(0.0), z(0.0) {};
  CartesianPoint(double x, double y, double z): x(x), y(y), z(z) {};
};

struct CartesianVector {
  double x;
  double y;
  double z;
  CartesianVector(): x(0.0), y(0.0), z(0.0) {};
  CartesianVector(double x, double y, double z): x(x), y(y), z(z) {};
};

struct ImagePoint {
  double sample;
  double line;
  double band;
  ImagePoint(): sample(0.0), line(0.0), band(0.0) {};
  ImagePoint(double sample, double line, double band): sample(sample), line(line), band(band) {};
};

#endif