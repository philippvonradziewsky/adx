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

#ifndef ADX_FUNCTION_HPP_
#define ADX_FUNCTION_HPP_

#include <adx/detail/to_std_tuple.hpp>
#include <adx/detail/var_traits.hpp>

#include <utility>

namespace adx {

template<class Expression>
class function {

public:
  using result_type = typename Expression::result_type;

  using arg_type =
    detail::to_std_tuple<
      detail::var_traits<Expression>::variables
    >::type;

  template<class Variable>
  struct set_variable {

    template<class T>
    set_variable(T && value) {
      Variable::value = std::forward<T>(value);
    }

    operator Variable() { return Variable(); }
  };

  template<class... Args>
  result_type operator(Args... && args) {
    set_variables(args..., arg_type);
  }

private:
  template<class... Args, class... Variables>
  void set_variables(Args... && args, std::tuple<Variables...>) {
    std::tuple<Variables...>(
      set_variable<Variables>(std::forward<Args>(args))......);
  }
};

}

#endif /* end of include guard: ADX_FUNCTION_HPP_ */
