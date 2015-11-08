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

#ifndef ADX_VARTRAITS_HPP_
#define ADX_VARTRAITS_HPP_

#include <adx/constant.hpp>
#include <adx/var.hpp>
#include <adx/detail/binary_expression.hpp>
#include <adx/detail/to_std_tuple.hpp>

#include <boost/mpl/end.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/type_traits.hpp>

#include <type_traits>

namespace adx {
namespace detail {

template<
  class Expression,
  bool = std::is_base_of<binary_expression, Expression>::value>
struct var_traits;

template<typename T, T Value>
struct var_traits<constant<T,Value>, false> {

  using variables = boost::mpl::list<>;
};

template<typename T, std::size_t Idx>
struct var_traits<var<T,Idx>, false> {

  using variables = boost::mpl::list<var<T,Idx>>;

};

struct var_comparator_tag : boost::mpl::int_<10> {};

template<class T>
struct var_comparator {
  using tag        = var_comparator_tag;
  using type       = var_comparator;
  using value_type = T;
};

template<class T>
struct var_traits<T, true> {

  using variables =
    typename boost::mpl::unique<
      typename boost::mpl::sort<
        typename boost::mpl::insert_range<
          typename var_traits<
            typename T::lhs_type>::variables,
          typename boost::mpl::end<
            typename var_traits<
              typename T::lhs_type>::variables
          >::type,
          typename var_traits<
            typename T::rhs_type>::variables
        >::type,
        boost::mpl::less<
          var_comparator<boost::mpl::_1>,
          var_comparator<boost::mpl::_2>
        >
      >::type,
      boost::is_same<
        boost::mpl::_1, boost::mpl::_2
      >
    >::type;

};

}
}

namespace boost { namespace mpl {
template<>
struct less_impl<
  adx::detail::var_comparator_tag, adx::detail::var_comparator_tag>
{
  template< typename Lhs, typename Rhs > struct apply :
    bool_<(Lhs::value_type::idx < Rhs::value_type::idx)>
  {};
};
}}

#endif /* end of include guard: ADX_VARTRAITS_HPP_ */
