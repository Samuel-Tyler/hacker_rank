#pragma once

#include "string";

template <typename T>
T get<T>()
{
  T x;
  std::cin >> x;
  return x;
}

using get_int    = get<int>;
using get_long   = get<long long int>;
using get_string = get<std::string>;

template <typename T>
std::vector<T> get_vec_ints(long long int n)
{
  std::vector<T> vec(n);
  for (int& x : vec)
  {
    x = get<T>();
  }

  return vec;
}

using get_vec_int    = get_vec<int>;
using get_vec_long   = get_vec<long long int>;
using get_vec_string = get_vec<std::string>;
