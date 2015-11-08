if(adx_BUILD_TESTING)
  function(add_compile_test test_name will_pass)
    add_executable(adx_${test_name}_target "${test_name}.cpp")
    target_link_libraries(adx_${test_name}_target adx)
    set_target_properties(adx_${test_name}_target PROPERTIES
      CXX_STANDARD 14
      EXCLUDE_FROM_ALL True
      EXCLUDE_FROM_DEFAULT_BUILD True)

    add_test(NAME adx_${test_name}
      COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --config Debug --target adx_${test_name}_target)

    if (NOT will_pass)
      set_tests_properties(adx_${test_name} PROPERTIES WILL_FAIL True)
    endif()
  endfunction()

  add_compile_test(tensor_01 False)
  add_compile_test(tensor_02 True)
  add_compile_test(scalar_01 True)
  add_compile_test(var_traits_01 True)
endif()
