#include <bits/stdc++.h>

using namespace std;

// Note this can be improved by not copying the factors set each call,
// intead passing the iterator down call chain. Was not required to
// beat the challenge.

int dfs(int X, int N, std::set<int> posible_factors, int last_removed = -1)
{
  if (last_removed > 0)
  {
    posible_factors.erase(posible_factors.begin(),
                          std::next(posible_factors.find(last_removed)));
  }

  int sum = 0;
  for (int factor : posible_factors)
  {
    int remainder = X - factor;
    if (remainder < 0)
    {
      break;
    }
    else if (remainder == 0)
    {
      sum += 1;
      break;
    }
    else
    {
      sum += dfs(remainder, N, posible_factors, factor);
    }
  }

  return sum;
}
int powerSum(int X, int N)
{
  std::set<int> posible_factors;
  for (int i = 1;; i++)
  {
    int power = std::pow(i, N);
    if (power > X)
    {
      break;
    }
    else
    {
      posible_factors.insert(power);
    }
  }

  return dfs(X, N, posible_factors);
}

int main()
{
  int X;
  cin >> X;
  int N;
  cin >> N;
  int result = powerSum(X, N);
  cout << result << endl;
  return 0;
}
