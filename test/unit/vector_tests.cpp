/*
 * This file is part of adx.
 *
 * adx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * adx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with adx.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unit_tests_forward.h>

#include <adx/covector.hpp>
#include <adx/derivative.hpp>
#include <adx/multiply.hpp>
#include <adx/var.hpp>
#include <adx/vector.hpp>

#include <isclose.hpp>

using vec2   = adx::vector<float,2>;
using covec2 = adx::covector<float,2>;

struct my_function {
  struct p { vec2   value; };
  struct q { covec2 value; };

  using function   = adx::multiply<adx::var<q>,adx::var<p>>;
  using derivative = adx::derivative<function, adx::var<p>>;
};

unit_test_result_t vector_test_01(char **result_message) {
  using p = my_function::p;
  using q = my_function::q;

  using function   = my_function::function;
  using derivative = my_function::derivative;

  function   f;
  derivative dfdp;

  float  result = f( p{{1.f,2.f}}, q{{3.f,4.f}} );

  if ( !adx::isclose(result,11.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, result, 42.f);
    return TEST_FAILED;
  }

  covec2 dresult = dfdp( p{{1.f,2.f}}, q{{3.f,4.f}} );

  if ( !adx::isclose(adx::detail::data(dresult)[0],3.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, adx::detail::data(dresult)[0], 3.f);
    return TEST_FAILED;
  }

  if ( !adx::isclose(adx::detail::data(dresult)[1],4.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, adx::detail::data(dresult)[1], 4.f);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}

unit_test_result_t vector_test_02(char **result_message) {
  using namespace adx;
  struct v { vec2 value; };
  struct a { float value; };

  using function   = multiply<var<a>,var<v>>;
  using derivative = derivative<function,var<v>>;

  function   f;
  derivative dfdx;

  vec2 result = f( a{3.f}, v{{1.f,5.f}} );

  if ( !isclose(detail::data(result)[0],3.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, detail::data(result)[0], 3.f);
    return TEST_FAILED;
  }

  if ( !isclose(detail::data(result)[1],15.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, %.2f != %.2f", __FILE__,
      __LINE__, detail::data(result)[1], 15.f);
    return TEST_FAILED;
  }

  auto dresult = dfdx( a{3.f}, v{{1.f,5.f}} );

  if ( !isclose(detail::data(dresult),3.f) ) {
    UNIT_TEST_CREATE_RESULT_MESSAGE(
      result_message, "An error occurred in %s:%d, test not implemented",
      __FILE__, __LINE__);
    return TEST_FAILED;
  }

  return TEST_PASSED;
}
