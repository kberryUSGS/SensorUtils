cmake_minimum_required(VERSION 3.10)
project(sensorutils VERSION 0.1.1 DESCRIPTION "SensorUtils library")

include(cmake/gtest.cmake)
include(GNUInstallDirs)
include(GoogleTest)

set(CMAKE_CXX_STANDARD 11)

add_library(sensorutils SHARED
            src/SensorUtils.cpp)

set_target_properties(sensorutils PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER SensorUtils.h
)


target_include_directories(sensorutils
                           PUBLIC
                           include/sensorutils
                           include/
)

find_package (Threads)

target_link_libraries(sensorutils
                      gtest ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS sensorutils
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})



include(CTest)

enable_testing()

add_subdirectory(tests)
