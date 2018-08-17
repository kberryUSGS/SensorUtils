#ifndef Sensor_h
#define Sensor_h

#include <memory>
#include <string>

#include "sensorcore.h"

#include "SensorModel.h"
#include "ShapeModel.h"

class Sensor {

  public:
    Sensor(const std::string &metaData, const std::string &sensorName);

    double declination(const CartesianVector &);
    double emissionAngle(const CartesianPoint &groundPoint);
    double emissionAngle(const ImagePoint &imagePoint);
    double phaseAngle(const CartesianPoint &groundPoint);
    double phaseAngle(const ImagePoint &imagePoint);
    double rightAscension(const CartesianVector &);
    
    CartesianPoint illuminatorPosition(ImagePoint imagePoint); 

  private:
    std::unique_ptr<SensorModel> m_sensorModel;
    std::unique_ptr<ShapeModel> m_shapeModel;
};

#endif
