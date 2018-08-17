cmake_minimum_required(VERSION 3.10)

set(COVERAGE OFF CACHE BOOL "Coverage")


# Link runSensorUtilsTests with what we want to test and the GTest and pthread library

add_executable(runSensorUtilsTests SensorCoreTesting.cpp SensorMathTesting.cpp SensorModelTesting.cpp ShapeModelTesting.cpp)

target_link_libraries(runSensorUtilsTests PUBLIC sensorutils ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)


if(COVERAGE)
    target_link_libraries(runSensorUtilsTests PRIVATE --coverage)
endif()

gtest_discover_tests(runSensorUtilsTests WORKING_DIRECTORY tests)
