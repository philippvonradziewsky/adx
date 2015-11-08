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

#ifndef ADX_TOSTDTUPLE_HPP_
#define ADX_TOSTDTUPLE_HPP_

#include <boost/mpl/fold.hpp>

#include <tuple>

namespace adx {
namespace detail {

template < class T, class R >
struct to_std_tuple_impl;

template < class... TTypes, class X >
struct to_std_tuple_impl< std::tuple< TTypes... >, X >
{
  using type = std::tuple< TTypes..., X >;
};

template<class Sequence>
struct to_std_tuple {

  // from: http://stackoverflow.com/questions/14965116
  using type =
    boost::mpl::fold<
      Sequence, std::tuple<>,
      to_std_tuple_impl<
        boost::mpl::_1,
        boost::mpl::_2
      >
    >::type;

};

}
}

#endif /* end of include guard: ADX_TOSTDTUPLE_HPP_ */
