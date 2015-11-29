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

#ifndef ADX_MULTIPLY_HPP_
#define ADX_MULTIPLY_HPP_

#include <adx/detail/binary_expression.hpp>
#include <adx/detail/common_type.hpp>
#include <adx/detail/derivative_traits.hpp>
#include <adx/detail/is_instantiation_of.hpp>

#include <adx/derivative_forward.hpp>
#include <adx/scaled_eye.hpp>
#include <adx/var.hpp>

#include <utility>

namespace adx {

template<class Lhs, class Rhs>
struct multiply : public detail::binary_expression {

  using result_type = decltype(
                        std::declval<typename Lhs::result_type>() *
                        std::declval<typename Rhs::result_type>()
                      );

  template<class... Args>
  result_type operator() (Args const&... args) {
    Lhs lhs;
    Rhs rhs;
    return lhs(args...) * rhs(args...);
  }
};

template<typename Lhs, typename Rhs, typename Var>
struct derivative<multiply<Lhs,Rhs>, Var> {

  using result_type = decltype(
                        std::declval<
                          std::conditional_t<
                            std::is_arithmetic<
                              typename derivative<Lhs,Var>::result_type
                            >::value,
                            scaled_eye<
                              typename derivative<Lhs,Var>::result_type,
                              valence<
                                typename derivative<
                                  Rhs,Var
                                >::result_type::valence_type::contravariant,
                                typename derivative<
                                  Rhs,Var
                                >::result_type::valence_type::contravariant
                              >
                            >,
                            std::conditional_t<
                              detail::is_instantiation_of<
                                var,Lhs
                              >::value &&
                              std::is_arithmetic<
                                typename Lhs::result_type
                              >::value &&
                              !std::is_same<
                                Lhs, Var
                              >::value,
                              typename derivative_traits<
                                scaled_eye<
                                  typename Lhs::result_type,
                                  valence<
                                    typename derivative<
                                      Rhs,Var
                                    >::result_type::valence_type::contravariant,
                                    typename derivative<
                                      Rhs,Var
                                    >::result_type::valence_type::contravariant
                                  >
                                >
                              >::template zero_type<typename Var::result_type>,
                              typename derivative<Lhs,Var>::result_type
                            >
                          >
                        >() * std::declval<
                          typename Rhs::result_type
                        >() + std::declval<
                          std::conditional_t<
                            std::is_arithmetic<
                              typename Lhs::result_type
                            >::value,
                            scaled_eye<
                              typename Lhs::result_type,
                              valence<
                                typename derivative<
                                  Rhs,Var
                                >::result_type::valence_type::contravariant,
                                typename derivative<
                                  Rhs,Var
                                >::result_type::valence_type::contravariant
                              >
                            >,
                            typename Lhs::result_type
                          >
                        >() * std::declval<
                          typename derivative<Rhs,Var>::result_type
                        >()
                      );

  template<class... Args>
  result_type operator() (Args const&... args) {
    return derivative<Lhs,Var>()(args...) * Rhs()(args...) +
    typename std::conditional<
      std::is_arithmetic<
        typename Lhs::result_type
      >::value,
      scaled_eye<
        typename Lhs::result_type,
        valence<
          typename derivative<
            Rhs,Var
          >::result_type::valence_type::contravariant,
          typename derivative<
            Rhs,Var
          >::result_type::valence_type::contravariant
        >
      >,
      typename Lhs::result_type
    >::type(Lhs()(args...)) * derivative<Rhs,Var>()(args...);
  }
};

}

#endif /* end of include guard: ADX_MULTIPLY_HPP_ */
