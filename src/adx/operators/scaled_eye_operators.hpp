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

#ifndef ADX_OPERATORS_SCALED_EYE_OPERATORS_HPP_
#define ADX_OPERATORS_SCALED_EYE_OPERATORS_HPP_

#include <adx/scaled_eye_forward.hpp>
#include <adx/eye.hpp>

namespace adx {

template<typename T>
T operator+ (T lhs, scaled_eye<T,make_valence<>::type> rhs) {
  return lhs + detail::data(rhs);
}

template<
  typename T,
  class Valence1,
  class Valence2,
  typename = std::enable_if_t<
               std::is_same<
                 typename Valence1::covariant,
                 typename Valence2::contravariant
               >::value
             >
>
scaled_eye<
  T,
  valence<
    typename Valence1::contravariant,
    typename Valence2::covariant
  >
> operator* (scaled_eye<T, Valence1> lhs, eye<T,Valence2>) {
  return scaled_eye<
    T,
    valence<
      typename Valence1::contravariant,
      typename Valence2::covariant
    >
  >(detail::data(lhs));
}
}

#endif /* end of include guard: ADX_OPERATORS_SCALED_EYE_OPERATORS_HPP_ */
