#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  std::cin >> n;

  std::vector<int> nums(n);

  for (size_t i = 0; i < nums.size(); i++)
  {
    std::cin >> nums[i];
  }

  int inserting = nums[n - 1];

  int i = n - 2;
  for (; i >= 0; i--)
  {
    if (nums[i] > inserting)
    {
      nums[i + 1] = nums[i];
    }
    else
    {
      break;
    }

    for (size_t i = 0; i < nums.size(); i++)
    {
      std::cout << nums[i] << ' ';
    }
    std::cout << '\n';
  }

  nums[i + 1] = inserting;
  for (size_t i = 0; i < nums.size(); i++)
  {
    std::cout << nums[i] << ' ';
  }
  return 0;
}
