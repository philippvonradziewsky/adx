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

#ifndef ADX_ZERO_HPP_
#define ADX_ZERO_HPP_

#include <adx/detail/always_false.hpp>

#include <cstddef>

namespace adx {

template<typename T, class Valence>
struct zero {
  static_assert(detail::always_false<Valence>::value,
    "2nd template argument must be valence type");
};

template<
  typename T,
  std::size_t... ContravarientExtents,
  std::size_t... CovariantExtents>
class zero<
  T,
  valence<
    detail::extent<ContravarientExtents...>,
    detail::extent<CovariantExtents...>
  >
> {
};



}

#endif /* end of include guard: ADX_ZERO_HPP_ */
