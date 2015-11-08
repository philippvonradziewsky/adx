/**
 * This file is part of adx.
 *
 * Adx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Adx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with adx.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unit_tests_forward.h>
#include <isclose.hpp>

#include <adx/plus.hpp>
#include <adx/derivative.hpp>

struct my_function {
  struct x { float value; };
  struct y { float value; };

  using function   = adx::plus<adx::var<x>,adx::var<y>>;
  using derivative = adx::derivative<function, adx::var<x>>;
};

unit_test_result_t scalar_test_01(char **result_message) {
  struct x { float value; };

  using function   = adx::var<x>;
  using derivative = adx::derivative<function, adx::var<x>>;

  function    f;
  derivative  dfdx;

  float result = f( x{42.f} );

  if ( !adx::isclose(result,42.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, result, 42.f);
    return TEST_FAILED;
  }

  result = dfdx( x{42.f} );

  if ( !adx::isclose(result,1.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, result, 1.f);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

unit_test_result_t scalar_test_02(char **result_message) {
  using x          = my_function::x;
  using y          = my_function::y;
  using function   = my_function::function;
  using derivative = my_function::derivative;

  function    f;
  derivative  dfdx;

  float result = f( x{1.f}, y{2.f} );

  if ( !adx::isclose(result,3.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, result, 3.f);
    return TEST_FAILED;
  }

  result = dfdx( x{1.f}, y{2.f} );

  if ( !adx::isclose(result,1.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, result, 1.f);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}
