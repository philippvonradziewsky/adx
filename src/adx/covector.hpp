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

#ifndef ADX_COVECTOR_HPP_
#define ADX_COVECTOR_HPP_

#include <adx/tensor.hpp>
#include <adx/valence.hpp>
#include <adx/derivative_forward.hpp>
#include <adx/zero.hpp>

#include <adx/vector.hpp>

#include <iterator>
#include <numeric>

namespace adx {

template<typename T, std::size_t Extent>
class covector
  : public tensor<T, typename make_valence<>::covariant<Extent>::type> {

public:
  covector(std::initializer_list<T> init) {
    std::uninitialized_copy(
      std::begin(init), std::end(init), std::begin(this->storage_)
    );
  }
};

template<typename T, std::size_t Extent>
struct derivative_traits<covector<T,Extent>> {

  using eye_type  = eye<
                      T,
                      typename make_valence<
                      >::template contravariant<
                        Extent
                      >::template covariant<
                        Extent
                      >::type
                    >;

  using zero_type = zero<
                      T,
                      typename make_valence<
                      >::template contravariant<
                        Extent
                      >::template covariant<
                        Extent
                      >::type
                    >;

};

}

#include <adx/operators/covector_operators.hpp>

#endif /* end of include guard: ADX_COVECTOR_HPP_ */
