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

#ifndef ADX_VECTOR_HPP_
#define ADX_VECTOR_HPP_

#include <adx/covector_forward.hpp>
#include <adx/derivative_forward.hpp>
#include <adx/eye.hpp>
#include <adx/tensor.hpp>
#include <adx/var_forward.hpp>
#include <adx/zero.hpp>

#include <adx/detail/derivative_traits.hpp>

#include <initializer_list>
#include <memory>

namespace adx {

template<typename T, std::size_t Extent>
class vector
  : public tensor<T, typename make_valence<>::contravariant<Extent>::type> {

public:
  vector(std::initializer_list<T> init) {
    std::uninitialized_copy(
      std::begin(init), std::end(init), std::begin(this->storage_)
    );
  }

};

template<typename T, std::size_t Extent>
struct derivative_traits<vector<T,Extent>> {

  using eye_type  = eye<
                      T,
                      typename make_valence<
                      >::template contravariant<
                        Extent
                      >::template covariant<
                        Extent
                      >::type
                    >;

  using valence_type = typename vector<T,Extent>::valence_type;

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

#include <adx/operators/vector_operators.hpp>

#endif /* end of include guard: ADX_VECTOR_HPP_ */
