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

  for (int j = 1; j < n; j++)
  {
    int inserting = nums[j];

    int i = j - 1;
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
    }

    nums[i + 1] = inserting;
    for (size_t i = 0; i < nums.size(); i++)
    {
      std::cout << nums[i] << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}
