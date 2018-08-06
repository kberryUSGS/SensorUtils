#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>

using namespace std;

double PhaseAngle(vector<double> & instPosition, vector<double> & sunPosition);
double EmissionAngle(const std::vector<double>  &observerBodyFixedPosition,
                     const std::vector<double> &groundPtIntersection,
                     const std::vector<double> &surfaceNormal);

#endif
