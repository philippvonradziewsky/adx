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

#ifndef ADX_DETAIL_ARRAY_HPP_
#define ADX_DETAIL_ARRAY_HPP_

#include <adx/detail/array_forward.hpp>
#include <adx/detail/extent.hpp>

namespace adx {
namespace detail {

template<typename T, std::size_t...Extents>
class array {
public:
  using extent_type = extent<Extents...>;
  using scalar_type = T;

protected:
  T storage_[extent_type::size()];

public:
  friend T const (&data<>(array<T,Extents...> const& arr))[extent<Extents...>::size()];
};

template<typename T, std::size_t...Extents>
T const (&data(array<T,Extents...> const& arr))[extent<Extents...>::size()] {
  return arr.storage_;
}

}
}

#endif
