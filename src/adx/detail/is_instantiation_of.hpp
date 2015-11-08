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

#pragma once

#include <type_traits>

namespace adx {
namespace detail {

// from: http://stackoverflow.com/questions/11251376
template< template<typename...> class Template, typename T >
struct is_instantiation_of : std::false_type {};

template< template<typename...> class Template, typename... Args >
struct is_instantiation_of< Template, Template<Args...> > : std::true_type {};

}
}
