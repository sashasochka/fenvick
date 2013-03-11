#include <cstdio>
#include <functional>
#include "fenvick.h"

int main() {
  const int n = 8;
  FenvickTree<double> fenvickTree(n, 1,
                                  std::multiplies<double>(),
                                  std::divides<double>());

  for (int i = 0; i < n; ++i)
    fenvickTree.set(i, i + 1);

  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j) {
      int s = fenvickTree.get(i, j);
      std::printf(
        "Function applied from data[%d] to data[%d] is equal to %d \n",
        i, j, s);
    }

  return 0;
}
