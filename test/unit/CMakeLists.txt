set(ADX_TEST_SOURCES
  "test_driver.c"
  "scalar_tests.cpp"
  "vector_tests.cpp"
  "tensor_tests.cpp")

if (BUILD_TESTING OR CodeCov_BUILD_COVERAGE)
  set(ADX_TEST_LIST_FILE "${CMAKE_CURRENT_BINARY_DIR}/unit_tests.c")
  set(ADX_TEST_FORWARD_FILE "${CMAKE_CURRENT_BINARY_DIR}/unit_tests_forward.h")

  list(APPEND ADX_TEST_SOURCES ${ADX_TEST_LIST_FILE})
endif()

if(adx_BUILD_TESTING)
  add_executable(adx-test-driver ${ADX_TEST_SOURCES})
  set_property(TARGET adx-test-driver APPEND PROPERTY
               INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/src"
                                   "${CMAKE_CURRENT_SOURCE_DIR}"
                                   "${CMAKE_CURRENT_BINARY_DIR}")
  set_target_properties(adx-test-driver PROPERTIES
    C_STANDARD   11
    CXX_STANDARD 14)

  target_link_libraries(adx-test-driver adx)
endif()

if(CodeCov_BUILD_COVERAGE)
  add_executable(adx-coverage-driver ${ADX_TEST_SOURCES})
  set_property(TARGET adx-coverage-driver APPEND PROPERTY
               INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/src"
                                   "${CMAKE_CURRENT_SOURCE_DIR}"
                                   "${CMAKE_CURRENT_BINARY_DIR}")
  add_coverage_target(adx-coverage-driver CXX)
  set_target_properties(adx-coverage-driver PROPERTIES
    C_STANDARD   11
    CXX_STANDARD 14)

  target_link_libraries(adx-coverage-driver PRIVATE adx)
endif()

if(adx_BUILD_TESTING OR CodeCov_BUILD_COVERAGE)
  string(TIMESTAMP ADX_BUILD_DATE "%Y-%m-%d" UTC)

  set(UNIT_TEST_FORWARDS "")
  set(UNIT_TEST_INITS "")

  function(add_unit_test test_name)
    set(UNIT_TEST_FORWARDS
    "${UNIT_TEST_FORWARDS}\nunit_test_result_t ${test_name}(char **result_message);\n" PARENT_SCOPE)
    set(UNIT_TEST_INITS
        "${UNIT_TEST_INITS}\n  UNIT_TEST_ADD_TEST(${test_name});" PARENT_SCOPE)
    if(BUILD_TESTING)
      add_test(NAME ${test_name} COMMAND adx-test-driver --test-case ${test_name})
    endif()
    if(CodeCov_BUILD_COVERAGE)
      add_coverage_run(${test_name} adx-coverage-driver --test-case ${test_name})
    endif()
  endfunction()

  add_unit_test(scalar_test_01)
  add_unit_test(scalar_test_02)
  add_unit_test(vector_test_01)
  add_unit_test(tensor_test_01)

  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/unit_tests.c.in"
                 "${ADX_TEST_LIST_FILE}")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/unit_tests_forward.h.in"
                 "${ADX_TEST_FORWARD_FILE}")
endif()
