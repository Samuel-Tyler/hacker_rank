#pragma once

#include <iostream>
#include <map>

template <typename T1, typename T2>
void print(const std::pair<T1, T2>& pair)
{
  std::cout << "{ " <<  pair.first << " : " << pair.second << " }";
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
void print(const T& container)
{
  std::cout << "{ ";
  for (const auto& obj : container)
  {
    std::cout << obj << ' ';
  }
  std::cout << "}\n";
} 
