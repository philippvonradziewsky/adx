#include <adx/tensor.hpp>
#include <adx/valence.hpp>

#include <iostream>

int main() {
  using valence = adx::make_valence<>::contravariant<2,2>::covariant<2,2>::type;
  using tensor  = adx::tensor<float, valence>;

  static const std::size_t order = tensor::order();

  std::cout << sizeof(tensor) << std::endl;
}
