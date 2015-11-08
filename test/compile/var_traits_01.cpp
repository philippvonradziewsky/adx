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

#include <adx/var.hpp>
#include <adx/plus.hpp>

#include <adx/detail/binary_expression.hpp>
#include <adx/detail/var_traits.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal.hpp>

using x = adx::var<float,0>;
using y = adx::var<float,1>;
using z = adx::var<float,2>;

template<class Testee, class Reference>
using check = boost::mpl::equal<
  typename adx::detail::var_traits<Testee>::variables, Reference >;

namespace test_01 {
  using testee    = x;
  using reference = boost::mpl::list<x>;
  BOOST_MPL_ASSERT(( check<testee, reference> ));
}

namespace test_02 {
  using testee    = adx::plus<x,y>;
  using reference = boost::mpl::list<x,y>;
  BOOST_MPL_ASSERT(( check<testee, reference> ));
}

namespace test_03 {
  using adx::plus;

  using testee    = plus<plus<x,y>, x>;
  using reference = boost::mpl::list<x,y>;
  BOOST_MPL_ASSERT(( check<testee, reference> ));
}

namespace test_04 {
  using adx::plus;

  using testee    = plus<plus<x,y>, plus<x,z>>;
  using reference = boost::mpl::list<x,y,z>;
  BOOST_MPL_ASSERT(( check<testee, reference> ));
}

int main() {
}
