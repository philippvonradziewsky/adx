#include <unit_tests_forward.h>

#include <adx/vector.hpp>
#include <adx/covector.hpp>

using vec3   = adx::vector<float, 3>;
using covec3 = adx::covector<float, 3>;

unit_test_result_t tensor_test_01(char **result_message) {
  vec3 vector;

  UNIT_TEST_CREATE_RESULT_MESSAGE(
    result_message, "An error occurred in %s:%d", __FILE__, __LINE__);
  return TEST_FAILED;
}
