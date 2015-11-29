/**
 * This file is part of adx.
 *
 * Adx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Foobar is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADX_EXTENT_HPP_
#define ADX_EXTENT_HPP_

#include <adx/detail/always_false.hpp>

#include <array>
#include <type_traits>

namespace adx {
namespace detail {

template<std::size_t... Extents>
struct extent {

  static constexpr
  std::size_t                                 dimension = sizeof...(Extents);

  static constexpr
  std::array<std::size_t, sizeof...(Extents)> values    = {Extents...};

  static constexpr
  std::size_t at( std::size_t index ) { return values[index]; }

  static constexpr
  std::size_t size(std::size_t index = 0, std::size_t result = 1) {
    return (index == dimension) ?
      result : size(index+1,result*at(index));
  }
};

template<class ExtentLhs, class ExtentRhs>
struct concat_extent;

template<class ExtentLhs, class ExtentRhs>
using concat_extent_t = typename concat_extent<ExtentLhs,ExtentRhs>::type;

template<std::size_t... Lhs, std::size_t... Rhs>
struct concat_extent<extent<Lhs...>, extent<Rhs...>> {
  using type = extent<Lhs..., Rhs...>;
};

template<class Extent>
struct pop_extent {
  static_assert(!std::is_same<Extent, extent<>>::value,
                "cannot remove extent, already empty");
  static_assert(detail::always_false<Extent>::value,
                "not an extent type");
};

template<class Extent>
using pop_extent_t = typename pop_extent<Extent>::type;

template<std::size_t LastExtent>
struct pop_extent<extent<LastExtent>> {
  using type = extent<>;
};

template<std::size_t FirstExtent,std::size_t... TrailingExtents>
struct pop_extent<
  extent<
    FirstExtent,
    TrailingExtents...
  >
> {
  using type = concat_extent_t<
                 extent<FirstExtent>,
                 pop_extent_t<
                   extent<TrailingExtents...>
                 >
               >;
};

}
}

#endif /* end of include guard: ADX_EXTENT_HPP_ */
