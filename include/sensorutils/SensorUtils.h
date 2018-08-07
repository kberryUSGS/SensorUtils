#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>

using namespace std;

double PhaseAngle(const vector<double> & instPosition, const vector<double> & sunPosition, const vector<double> & surfaceIntersection);

double EmissionAngle(const vector<double>  &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal);

#endif
