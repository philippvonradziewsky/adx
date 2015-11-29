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

#ifndef ADX_OPERATOR_EYE_OPERATORS_HPP_
#define ADX_OPERATOR_EYE_OPERATORS_HPP_

#include <adx/valence.hpp>
#include <adx/eye.hpp>
#include <adx/zero.hpp>

namespace adx {

template<typename T, class Valence>
eye<T,Valence> operator+ (eye<T,Valence>, zero<T,Valence>) {
  return {};
}

template<typename T>
T operator* (eye<T,make_valence<>::type>, T rhs) {
  return rhs;
}

}

#endif /* end of include guard: ADX_OPERATOR_EYE_OPERATORS_HPP_ */
