#pragma once

#include "print_coloured.hpp"

#include <iostream>
#include <map>
#include <string>
#include <type_traits>

template <typename Scalar, int = 1, typename = std::enable_if_t<std::is_scalar<Scalar>::value>>
void print(const Scalar& i)
{
  print_coloured(i, Console_colour::FG_LIGHT_CYAN);
}

void print(const std::string& s)
{
  print_coloured(s, Console_colour::FG_LIGHT_RED);
}

template <typename T1, typename T2>
void print(const std::pair<T1, T2>& pair)
{
  std::cout << "{ ";
  print(pair.first);
  std::cout << " : ";
  print(pair.second);
  std::cout << " }";
}

template <typename T1, typename T2, typename T3>
void print(const std::map<T1, T2, T3>& container)
{
  std::cout << "{ ";
  for (const auto& obj : container)
  {
    print(obj);
    std::cout << ", ";
  }
  std::cout << "}\n";
}

template <typename T1, typename T2, typename T3>
void print(const std::multimap<T1, T2, T3>& container)
{
  int i = 0;
  for (const auto& obj : container)
  {
    std::cout << i++ << " : " << obj.first << " : " << obj.second << std::endl;
  }
}

template <typename T>
auto is_iterable_impl(int) -> decltype(
    std::begin(std::declval<T&>()) !=
        std::end(std::declval<T&>()), // begin/end and operator !=
    void(),                           // Handle evil operator ,
    ++std::declval<decltype(begin(std::declval<T&>())) &>(), // operator ++
    void(*std::begin(std::declval<T&>())),                   // operator*
    std::true_type{});

template <typename T>
std::false_type is_iterable_impl(...);

template <typename T, typename T2 = std::enable_if_t<decltype(is_iterable_impl<T>(0))::value>>
void print(const T& container)
{
  std::cout << "{ ";
  for (const auto& obj : container)
  {
    print(obj);
    std::cout << ' ';
  }
  std::cout << "}\n";
}
