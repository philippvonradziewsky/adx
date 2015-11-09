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

#include <adx/covector.hpp>
#include <adx/derivative.hpp>
#include <adx/multiply.hpp>
#include <adx/vector.hpp>

#include <type_traits>

using vec2   = adx::vector<float,2>;
using covec2 = adx::covector<float,2>;

struct my_function {
  struct p { vec2   value; };
  struct q { covec2 value; };

  using function   = adx::multiply<adx::var<q>,adx::var<p>>;
  using derivative = adx::derivative<function,adx::var<p>>;
};

int main() {
  using function   = my_function::function;
  using derivative = my_function::derivative;

  static_assert(std::is_same<function::result_type, float>::value,
    "Test failed");

  static_assert(std::is_same<derivative::result_type, covec2>::value,
    "Test failed");
}
