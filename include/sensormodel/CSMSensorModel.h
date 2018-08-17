#ifndef CSMSensorModel_h
#define CSMSensorModel_h

#include <vector>

#include "sensorcore.h"
#include "SensorModel.h"

class CSMSensorModel : public SensorModel {
  public:
    CSMSensorModel(); 
    CartesianPoint imageToGround(ImagePoint &);
    ImagePoint groundToImage(CartesianPoint &);
    CartesianVector groundToLook(CartesianPoint & );
    double imageTime(ImagePoint & );

    CartesianPoint getSensorPosition(ImagePoint &);
    CartesianVector getIlluminationDirection (CartesianPoint &);
};

#endif