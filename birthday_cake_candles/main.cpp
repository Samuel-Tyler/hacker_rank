#include <algorithm>
#include <iostream>
#include <numeric>

int main()
{
  int n_candles;
  std::cin >> n_candles;

  long max = 0;
  long n_max_height = 0;
  for (int i = 0; i < n_candles; i++)
  {
    int height;
    std::cin >> height;
    if (height > max)
    {
      max = height;
      n_max_height = 1;
    }
    else if (height == max)
    {
      n_max_height++;
    }
  }
  std::cout << n_max_height;
}
