//============================================================================
// Name        : segtree.h
// Author      : Oleksandr
// Copyright   : Licensed with GPLv3
// Description : Segment tree class in C++11
//============================================================================

#ifndef SEGTREE_H_ // NOLINT
#define SEGTREE_H_

#include <cassert>
#include <functional>
#include <vector>

template <typename T>
class FenvickTree {
 private:
  std::vector<T> tree;
  std::function<T(T, T)> f;
  std::function<T(T, T)> f_inv;

  T query(int r) {
    int next = (r & (r+1)) - 1;
    if (next < 0)
      return tree[r];
    else
      return f(tree[r], query(next));
  }
  
 public:
  FenvickTree(const std::vector<T>& data,
      std::function<T(T, T)> f     = std::plus <T>(),
      std::function<T(T, T)> f_inv = std::minus<T>()) {
    this -> f     = f;
    this -> f_inv = f_inv;

    tree.resize(data.size(), 1);
    for (int i = 0; i < static_cast<int>(data.size()); ++i)
      set(i, data[i]);
  }

  FenvickTree(int n, T val = T(),
      std::function<T(T, T)> f     = std::plus <T>(),
      std::function<T(T, T)> f_inv = std::minus<T>()) :
        FenvickTree(std::vector<T>(n, val), f, f_inv) {
  }


  T get(int l, int r) {
    if (l == 0)
      return query(r);
    else
      return f_inv(query(r), query(l - 1));
  }

  T get(int index) {
    return get(index, index);
  }

  void set(int index, T value) {
    for (int i = index; i < static_cast<int>(tree.size()); i |= (i+1))
      tree[i] = f(value, f_inv(tree[i], get(i)));
  }
};


#endif /* SEGTREE_H_ */ // NOLINT
