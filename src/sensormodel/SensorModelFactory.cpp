#include "SensorModelFactory.h"

#include <memory>
#include <string>

#include "SensorModel.h"
#include "CSMSensorModel.h"

/**
 * Creates a SensorModel based on the given shape model name.
 *
 * @param sensorModelName Name of the sensor model to create.
 *
 * @return std::unique_ptr<SensorModel> Returns a managed pointer of the created SensorModel.
 */
std::unique_ptr<SensorModel> SensorModelFactory::create(const std::string &sensorModelName) {
  return std::unique_ptr<SensorModel>(new CSMSensorModel); 
}