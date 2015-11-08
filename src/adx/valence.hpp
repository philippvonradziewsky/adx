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

#ifndef ADX_VALENCE_HPP_
#define ADX_VALENCE_HPP_

#include <adx/detail/extent.hpp>
// #include <adx/detail/is_instantiation_of.hpp>

#include <utility>

namespace adx {

template<class ContravariantExtent, class CovariantExtent>
struct valence {

  // static_assert(
  //   detail::is_instantiation_of<detail::extent, ContravariantExtent>::value,
  //   "must be extent type");
  // static_assert(
  //   detail::is_instantiation_of<detail::extent, CovariantExtent>::value,
  //   "must be extent type");

  using contravariant = ContravariantExtent;
  using covariant     = CovariantExtent;

  static constexpr
  std::pair<std::size_t,std::size_t> value =
    {contravariant::dimension, covariant::dimension};
};

template<class Valence = valence<detail::extent<>, detail::extent<>>>
struct make_valence {
  using type = Valence;

  template<std::size_t... Extents>
  using covariant = make_valence<
    valence<typename type::contravariant, detail::extent<Extents...>>>;

  template<std::size_t... Extents>
  using contravariant = make_valence<
    valence<detail::extent<Extents...>, typename type::covariant>>;
};

}

#endif /* end of include guard: ADX_VALENCE_HPP_ */
