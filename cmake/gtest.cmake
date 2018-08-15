if (NOT TARGET gtest)
  set(GOOGLETEST_ROOT gtest/googletest CACHE STRING "Google Test source root")

  include_directories(SYSTEM
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/../googlemock
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/../googlemock/include
      )

  set(GOOGLETEST_SOURCES
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/../googlemock/src/gmock-all.cc
      ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/../googlemock/src/gmock_main.cc
      )

  foreach(_source ${GOOGLETEST_SOURCES})
      set_source_files_properties(${_source} PROPERTIES GENERATED 1)
  endforeach()

  add_library(gtest SHARED ${GOOGLETEST_SOURCES})
endif()
