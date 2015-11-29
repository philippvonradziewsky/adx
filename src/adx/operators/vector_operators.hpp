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

#ifndef ADX_OPERATOR_VECTOR_OPERATORS_HPP_
#define ADX_OPERATOR_VECTOR_OPERATORS_HPP_

#include <adx/vector.hpp>
#include <adx/derivative.hpp>

namespace adx {

template<typename T, std::size_t Extent>
vector<T,Extent> operator* (T lhs, vector<T,Extent> rhs) {
  vector<T,Extent> result = rhs;

  for (T& t : detail::data(result))
    t = lhs * t;

  return result;
}

}

#endif /* end of include guard: ADX_OPERATOR_VECTOR_OPERATORS_HPP_ */
