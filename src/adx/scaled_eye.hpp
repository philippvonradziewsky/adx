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

#ifndef ADX_SCALED_EYE_HPP_
#define ADX_SCALED_EYE_HPP_

#include <adx/scaled_eye_forward.hpp>

#include <adx/eye.hpp>
#include <adx/valence.hpp>

#include <adx/detail/derivative_traits_forward.hpp>
#include <adx/detail/always_false.hpp>

#include <cstddef>

namespace adx {

template<typename T, class Valence>
class scaled_eye {
  static_assert(detail::always_false<Valence>::value,
    "2nd template argument must be valence type");
};

template<
  typename T,
  std::size_t... ContravarientExtents,
  std::size_t... CovariantExtents>
class scaled_eye<
  T,
  valence<
    detail::extent<ContravarientExtents...>,
    detail::extent<CovariantExtents...>
  >
> {
public:
  using valence_type = valence<
                         detail::extent<ContravarientExtents...>,
                         detail::extent<CovariantExtents...>
                       >;

public:
  scaled_eye(T val) : storage_(val) {
  }

private:
  T storage_;

public:
  friend T const& detail::data<>(scaled_eye<T,valence_type> const& val);
};

template<typename T, class Valence>
struct derivative_traits<scaled_eye<T,Valence>> {

  using valence_type = Valence;

  using eye_type  = eye<T,valence_type>;

  template<typename T2>
  using zero_type = zero<
                      T,
                      valence<
                        typename valence_type::contravariant,
                        detail::concat_extent_t<
                          typename valence_type::covariant,
                          typename derivative_traits<
                            T2
                          >::valence_type::contravariant
                        >
                      >
                    >;

};

namespace detail {

template<typename T, class Valence>
T const& data(scaled_eye<T,Valence> const& val) {
  return val.storage_;
}

}

}

#include <adx/operators/scaled_eye_operators.hpp>

#endif /* end of include guard: ADX_SCALED_EYE_HPP_ */
