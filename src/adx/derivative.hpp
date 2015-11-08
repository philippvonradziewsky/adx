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

#ifndef ADX_DERIVATIVE_HPP_
#define ADX_DERIVATIVE_HPP_

#include <adx/var.hpp>
#include <adx/detail/is_instantiation_of.hpp>

#include <adx/derivative_forward.hpp>

namespace adx {

template<class F, class Var>
struct derivative {
  static_assert(detail::is_instantiation_of<var, Var>::value,
    "2nd argument must be instantiation of adx::var");
};

}

#endif /* end of include guard: ADX_DERIVATIVE_HPP_ */
