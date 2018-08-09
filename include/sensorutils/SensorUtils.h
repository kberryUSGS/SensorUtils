#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>
#include <armadillo>

using namespace std;
using namespace arma;

double PhaseAngle(const vector<double> & instPosition, const vector<double> & sunPosition, const vector<double> & surfaceIntersection);

double EmissionAngle(const vector<double>  &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal);

vec illuminatorPosition(const vec &groundPointIntersection,
                        const vec &illuminatorDirection);

vector<double> rect2lat(const vector<double> rectangularCoords);

vector <double> computeRADec(const vector<double> rectangularCoords);

#endif
