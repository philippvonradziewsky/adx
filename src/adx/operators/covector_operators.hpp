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

#ifndef ADX_OPERATOR_COVECTOR_OPERATORS_HPP_
#define ADX_OPERATOR_COVECTOR_OPERATORS_HPP_

#include <adx/covector_forward.hpp>
#include <adx/eye.hpp>
#include <adx/zero.hpp>

namespace adx {

template<typename T, std::size_t Extent>
covector<T,Extent> operator* (covector<T,Extent> lhs, T rhs){
  covector<T,Extent> result = lhs;

  for (T& t : detail::data(result.storage_))
    t *= rhs;

  return result;
}

template<typename T, std::size_t Extent>
covector<T,Extent> operator* (T lhs, covector<T,Extent> rhs) {
  return rhs * lhs;
}

template<typename T, std::size_t Extent>
T operator* (covector<T,Extent> lhs, vector<T,Extent> rhs) {
  return std::inner_product(
    std::begin(detail::data(lhs)), std::end(detail::data(lhs)),
    detail::data(rhs), T(0)
  );
}

template<typename T, std::size_t Extent>
zero<T,typename make_valence<>::template covariant<Extent>::type>
operator* (
  zero<
    T,
    typename make_valence<
    >::template contravariant<
      Extent
    >:: template covariant<
      Extent
    >::type
  >,
  vector<T,Extent>) {
  return zero<T,typename make_valence<>::template covariant<Extent>::type>();
}

template<typename T, std::size_t Extent>
covector<T,Extent>
operator+ (
  zero<
    T,
    typename make_valence<
    >::template covariant<
      Extent
    >::type
  >,
  covector<T,Extent> rhs) {
  return rhs;
}

template<typename T, std::size_t Extent>
covector<T,Extent>
operator* (
  covector<T,Extent> lhs,
  eye<
    T,
    typename make_valence<
    >::template contravariant<
      Extent
    >:: template covariant<
      Extent
    >::type
  >) {
  return lhs;
}

}

#endif /* end of include guard: ADX_OPERATOR_COVECTOR_OPERATORS_HPP_ */
