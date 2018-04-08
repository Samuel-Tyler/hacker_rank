//#include "print.hpp"
#include <bits/stdc++.h>

int matrixLand(const std::vector<std::vector<int>>& A)
{
  int              width = (int)A[0].size();
  std::vector<int> previous_values(width, 0);
  std::vector<int> current_values(width, INT_MIN);

  int         x = 0;
  std::vector<int> max_previous(width);
  for (const auto& row : A)
  {
    x++;

    for (int& i : current_values)
    {
      i = INT_MIN;
    }

    for (int& i : max_previous)
    {
      i = INT_MIN;
    }

    int sum = 0;
    for (int i = 0; i < width; i++)
    {
      sum += row[i];
    }

    for (int i = 0; i < width;)
    {
      //   auto inner_previous = available_previous;
      auto inner_sum = sum;
      int  last_max  = INT_MIN;

      if (max_previous[i] != previous_values[i])
      {
        max_previous[i] = previous_values[i];
        for (int j = i + 1; j < width; j++)
        {
          max_previous[j] = std::max(max_previous[j - 1], previous_values[j]);
        }
      }

      for (int j = width - 1; j >= i; j--)
      {
        int new_max = std::max(max_previous[j] + inner_sum, last_max);

        current_values[j] = std::max(current_values[j], new_max);

        inner_sum -= row[j];
        last_max = new_max;
      }
      const auto increment = [&] {
        sum -= row[i];
        i++;
      };
      increment();

      while (i < width && row[i] >= 0 && row[i - 1] >= 0)
      {
        current_values[i] = current_values[i - 1];
        increment();
      }
      std::cout << i << " / " << width << " " << x << " / " << A.size()
                << std::endl;
    }
    previous_values = current_values;
    // print(row);
    //   print(previous_values);
    //  std::cout << endl;
  }
  return *max_element(previous_values.begin(), previous_values.end());
}

int main()
{
  int n;
  int m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> A(n, std::vector<int>(m));
  for (int A_i = 0; A_i < n; A_i++)
  {
    for (int A_j = 0; A_j < m; A_j++)
    {
      std::cin >> A[A_i][A_j];
    }
  }
  int result = matrixLand(A);
  std::cout << result << std::endl;
  return 0;
}
