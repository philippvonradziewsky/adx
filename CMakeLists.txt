cmake_minimum_required(VERSION 3.1)

project(adx LANGUAGES C CXX VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

option(adx_BUILD_TESTING "Build tests" On)

add_library(adx INTERFACE)
target_include_directories(adx SYSTEM
  INTERFACE "${CMAKE_SOURCE_DIR}/src")

if (adx_BUILD_TESTING)
  include(CTest)
  include(CodeCoverage)
  enable_testing()
  add_subdirectory(test)
endif()
