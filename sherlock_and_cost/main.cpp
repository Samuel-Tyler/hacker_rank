#include "print.hpp"
#include <bits/stdc++.h>

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

int solve(std::vector<int>& nums)
{
  int last_low_total  = 0;
  int last_high_total = 0;
  int low_previous    = nums[0];
  int high_previous   = 1;
  for (size_t i = 1; i < nums.size(); i++)
  {
    auto new_low  = 1;
    auto new_high = nums[i];
    auto new_low_total =
        std::max(std::abs(high_previous - new_low) + last_high_total,
                 std::abs(low_previous - new_low) + last_low_total);
    auto new_high_total =
        std::max(std::abs(new_high - low_previous) + last_low_total,
                 std::abs(new_high - high_previous) + last_high_total);

    low_previous    = 1;
    high_previous   = nums[i];
    last_high_total = new_high_total;
    last_low_total  = new_low_total;
  }
  return std::max(last_low_total, last_high_total);
}

int main()
{
  auto n = get_int();

  for (int i = 0; i < n; i++)
  {
    auto x   = get_int();
    auto vec = get_vec_ints(x);
    std::cout << solve(vec) << '\n';
  }
}
