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

#ifndef ADX_OPERATOR_ZERO_OPERATORS_HPP_
#define ADX_OPERATOR_ZERO_OPERATORS_HPP_

#include <adx/covector_forward.hpp>
#include <adx/scaled_eye.hpp>
#include <adx/valence.hpp>
#include <adx/vector_forward.hpp>
#include <adx/zero.hpp>

namespace adx {

template<typename T, class Valence>
T operator+ (T lhs, zero<T,Valence>) {
  return lhs;
}

template<typename T, class Valence>
scaled_eye<T,Valence> operator+ (
  zero<T,Valence>, scaled_eye<T,Valence> rhs) {
  return rhs;
}

template<typename T, std::size_t Extent>
covector<T,Extent> operator+ (
  zero<T,typename make_valence<>::covariant<Extent>::type>,
  covector<T,Extent> rhs) {
  return rhs;
}

template<
  typename T,
  std::size_t... ContravariantExtents,
  std::size_t... CovariantExtents>
zero<
  T,
  valence<
    detail::extent<ContravariantExtents...>,
    detail::pop_extent_t<
      detail::extent<CovariantExtents...>
    >
  >
>
operator* (
  zero<
    T,
    valence<
      detail::extent<ContravariantExtents...>,
      detail::extent<CovariantExtents...>
    >
  >,
  vector<
    T,
    detail::extent<CovariantExtents...>::at(
      detail::extent<CovariantExtents...>::dimension - 1
    )
  >) {
  return zero<
    T,
    valence<
      detail::extent<ContravariantExtents...>,
      detail::pop_extent_t<
        detail::extent<CovariantExtents...>
      >
    >
  >();
}

}

#endif /* end of include guard: ADX_OPERATOR_ZERO_OPERATORS_HPP_ */
