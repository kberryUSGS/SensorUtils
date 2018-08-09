#ifndef SensorUtils_h
#define SensorUtils_h
#include <vector>

using namespace std;

double PhaseAngle(const vector<double> & instPosition, const vector<double> & sunPosition, const vector<double> & surfaceIntersection);

double EmissionAngle(const vector<double>  &observerBodyFixedPosition,
                     const vector<double> &groundPtIntersection,
                     const vector<double> &surfaceNormal);

vector<double> rect2lat(const vector<double> rectangularCoords);
vector<double> lat2rect(vector<double> sphericalCoords);
vector <double> computeRADec(const vector<double> rectangularCoords);




#endif
