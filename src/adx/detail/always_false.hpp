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

#ifndef ADX_ALWAYSFALSE_HPP_
#define ADX_ALWAYSFALSE_HPP_

namespace adx {
namespace detail {

template<class T>
struct always_false {
  static constexpr bool value = false;
};

}
}

#endif /* end of include guard: ADX_ALWAYSFALSE_HPP_ */