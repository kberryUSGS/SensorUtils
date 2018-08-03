cmake_minimum_required(VERSION 3.10)

set(COVERAGE OFF CACHE BOOL "Coverage")

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests TestyMcTestFace.cpp)

target_link_libraries(runTests PUBLIC sensorutils ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)

if (COVERAGE)
        target_compile_options(runTests PRIVATE --coverage)
	target_link_libraries(runTests PRIVATE --coverage)
endif()

gtest_discover_tests(runTests WORKING_DIRECTORY tests)
