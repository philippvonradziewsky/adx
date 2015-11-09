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

#ifndef ADX_VAR_HPP_
#define ADX_VAR_HPP_

#include <adx/derivative_forward.hpp>

#include <adx/detail/common_type.hpp>
#include <adx/detail/nullary_expression.hpp>
#include <adx/detail/binary_expression.hpp>
#include <adx/detail/derivative_traits.hpp>

#include <cstddef>
#include <tuple>

namespace adx {

template<typename T>
struct var : public detail::nullary_expression {
  using type        = T;
  using result_type = decltype(type::value);

private:
  var(var const&) = delete;
  var& operator= (var const&) = delete;

public:
  var() = default;

public:
  template<class... Args>
  result_type operator() (Args const&... args) {
    return std::get<T const&>(std::tie(args...)).value;
  }
};

namespace detail {

template<
  class Var,
  class Other>
struct common_type_var {
  using type =
    typename std::common_type<
      typename Var::result_type,
      typename Other::result_type
    >::type;
};

template<class T, class Other>
struct common_type<var<T>, Other>
  : public common_type_var<var<T>, Other> {
};

}

template<typename T>
struct derivative<var<T>, var<T>> {
  using result_type = typename derivative_traits<
                        typename var<T>::result_type
                      >::dual_type;

  template<class... Args>
  result_type operator() (Args const&... args) {
    return result_type(1.);
  }
};

template<typename T1, typename T2>
struct derivative<var<T1>, var<T2>> {
  using result_type = typename derivative_traits<
                        typename var<T2>::result_type
                      >::dual_type;

  template<class... Args>
  result_type operator() (Args const&... args) {
    return result_type(0.);
  }
};

}

#endif /* end of include guard: ADX_VAR_HPP_ */
