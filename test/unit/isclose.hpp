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

#ifndef ADX_ISCLOSE_HPP_
#define ADX_ISCLOSE_HPP_

#include <cmath>

namespace adx {

template<typename T>
bool isclose(
  T const& a, T const& b, T rtol = T(1.e-5f), T atol = T(1.e-8f)) {
  return (std::abs(a-b) <= atol+rtol*std::abs(b));
}

}

#endif /* end of include guard: ADX_ISCLOSE_HPP_ */
