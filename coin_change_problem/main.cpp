#include <bits/stdc++.h>
#include <print.hpp>

int get_int()
{
  int i;
  std::cin >> i;
  return i;
}

std::vector<int> get_vec_ints(int n)
{
  std::vector<int> vec(n);
  for (int& i : vec)
  {
    i = get_int();
  }

  return vec;
}

int main()
{

  auto cost  = get_int();
  auto n     = get_int();
  auto coins = get_vec_ints(n);

  std::vector<long> combinations(cost + 1, 0);
  combinations[0] = 1;

  for (int coin : coins)
  {
    for (int i = 1; i <= cost; i++)
    {
      auto combination_pos = i - coin;
      if (combination_pos >= 0)
      {
        combinations[i] += combinations[combination_pos];
      }
    }
  }

  std::cout << combinations[cost];
}
