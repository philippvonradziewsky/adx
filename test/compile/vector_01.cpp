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

#include <adx/vector.hpp>
#include <adx/multiply.hpp>
#include <adx/derivative.hpp>
#include <adx/tensor.hpp>

#include <type_traits>

using vec2   = adx::vector<float,2>;

int main() {
  using namespace adx;
  struct v { vec2 value; };
  struct a { float value; };

  using function   = multiply<var<a>,var<v>>;
  using derivative = derivative<function,var<v>>;

  function   f;
  derivative dfdx;

  static_assert(std::is_same<
    derivative::result_type::valence_type,
    make_valence<>::contravariant<2>::covariant<2>::type
  >::value, "Test failed");
}
