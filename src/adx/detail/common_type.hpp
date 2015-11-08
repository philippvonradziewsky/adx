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

#ifndef ADX_COMMONTYPE_HPP_
#define ADX_COMMONTYPE_HPP_

#include <type_traits>

namespace adx {
namespace detail {

template<class... T>
struct common_type;

template< class... T>
using common_type_t = typename common_type<T...>::type;

template<class T>
struct common_type<T> {
  using type = typename std::common_type<T>::type;
};

template<class T, class U>
struct common_type<T,U> {
  using type = typename std::common_type<T,U>::type;
};

template<class T, class U, class... V>
struct common_type<T,U,V...> {
  using type = common_type_t<common_type_t<T,U>, V...>;
};

}
}

#endif /* end of include guard: ADX_COMMONTYPE_HPP_ */
