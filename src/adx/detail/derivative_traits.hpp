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

#ifndef ADX_DERIVATIVE_TRAITS_HPP_
#define ADX_DERIVATIVE_TRAITS_HPP_

#include <adx/detail/derivative_traits_forward.hpp>

#include <adx/eye.hpp>
#include <adx/zero.hpp>

namespace adx {

template<>
struct derivative_traits<float> {
  struct eye_type : public eye<
                      float,
                      typename make_valence<>::type
                    > {
    operator float() const { return 1.f; }
  };

  using valence_type = make_valence<>::type;

  template<typename T2>
  using zero_type = zero<
                      float,
                      valence<
                        typename derivative_traits<T2>::valence_type::contravariant,
                        detail::concat_extent_t<
                          typename derivative_traits<T2>::valence_type::contravariant,
                          typename derivative_traits<T2>::valence_type::contravariant
                        >
                      >
                    >;
};

}

#endif /* end of include guard: ADX_DERIVATIVE_TRAITS_HPP_ */
