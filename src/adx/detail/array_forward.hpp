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

#ifndef ADX_DETAIL_ARRAY_FORWARD_HPP_
#define ADX_DETAIL_ARRAY_FORWARD_HPP_

#include <adx/detail/extent.hpp>

#include <cstddef>

namespace adx {
namespace detail {

template<typename T, std::size_t...Extents>
class array;

template<typename T, std::size_t...Extents>
T const (&data(array<T,Extents...> const& arr))[extent<Extents...>::size()];

template<typename T, std::size_t...Extents>
T (&data(array<T,Extents...> & arr))[extent<Extents...>::size()];

}
}

#endif /* end of include guard: ADX_DETAIL_ARRAY_FORWARD_HPP_ */
