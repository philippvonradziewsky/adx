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

#ifndef ADX_PLUS_HPP_
#define ADX_PLUS_HPP_

#include <adx/detail/common_type.hpp>
#include <adx/detail/binary_expression.hpp>

#include <adx/derivative_forward.hpp>

namespace adx {

template<class Lhs, class Rhs>
struct plus : public detail::binary_expression {

  using result_type = detail::common_type_t<
                        typename Lhs::result_type,
                        typename Rhs::result_type
                      >;

  template<class... Args>
  result_type operator() (Args const&... args) {
    Lhs lhs;
    Rhs rhs;
    return lhs(args...) + rhs(args...);
  }
};

namespace detail {

template<
  class Plus,
  class Expression2>
struct common_type_plus {
  using type =
    typename std::common_type<
      typename Plus::result_type,
      typename Expression2::result_type
    >::type;
};

template<class Lhs, class Rhs, class U>
struct common_type<plus<Lhs,Rhs>,U>
  : public common_type_plus<plus<Lhs,Rhs>,U> {
};

}

template<typename Lhs, typename Rhs, typename Var>
struct derivative<plus<Lhs,Rhs>, Var> {
  using result_type = decltype(
                        std::declval<
                          typename derivative<Lhs,Var>::result_type
                        >() +
                        std::declval<
                          typename derivative<Rhs,Var>::result_type
                        >()
                      );

  template<class... Args>
  result_type operator() (Args const&... args) {
    return derivative<Lhs,Var>()(args...) + derivative<Rhs,Var>()(args...);
  }
};

}

#endif /* end of include guard: ADX_PLUS_HPP_ */
