#include <bits/stdc++.h>
using namespace std;

vector<int> absolutePermutation(int n, int k)
{
  if (k == 0)
  {
    std::vector<int> original(n);
    std::iota(original.begin(), original.end(), 1);
    return original;
  }
  else if ((n % (2 * k)) == 0)
  {
    std::vector<int> original(n);
    for (int i = 0; i < n; i += 2 * k)
    {
      for (int j = 0; j < k; j++)
      {
        original[i + j] = 1 + i + j + k;
      }
      for (int j = 0; j < k; j++)
      {
        original[i + k + j] = 1 + i + j;
      }
    }
    return original;
  }

  return {-1};
}

int main()
{
  int t;
  cin >> t;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int t_itr = 0; t_itr < t; t_itr++)
  {
    int n, k;
    std::cin >> std::ws >> n;
    std::cin >> std::ws >> k;

    vector<int> result = absolutePermutation(n, k);

    for (size_t result_itr = 0; result_itr < result.size(); result_itr++)
    {
      cout << result[result_itr];

      if (result_itr != result.size() - 1)
      {
        cout << " ";
      }
    }

    cout << "\n";
  }

  return 0;
}
