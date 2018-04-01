#include <bits/stdc++.h>

using namespace std;

vector<long> dfs(int n, const vector<int>& sorted_options, int start_offset)
{
  std::cerr << n << std::endl;
  if (n == 1)
  {
    return {1};
  }

  std::vector<std::vector<long>> posible;
  for (int i = start_offset; i < (int)sorted_options.size(); i++)
  {
    if (n % sorted_options[i] == 0)
    {
      auto vals = dfs(n / sorted_options[i], sorted_options, i);
      if (vals.size() > 0)
      {
        vals.push_back(n);
        posible.push_back(vals);
      }
    }
  }
  if (posible.size() > 0)
  {
    return *min_element(posible.begin(), posible.end(),
                       [](const std::vector<long>& lhs, const std::vector<long>& rhs) { return lhs.size() < rhs.size(); });
    
  }
  return {};
}

vector<long> kFactorization(int n, vector<int> A)
{
  std::sort(A.begin(), A.end(), std::greater<int>());
  auto res = dfs(n, A, 0);
  if (res.size() == 0)
  {
    // Could not find solution
    return {-1};
  }
  return res;
}

int main()
{
  int n;
  int k;
  cin >> n >> k;
  vector<int> A(k);
  for (int A_i = 0; A_i < k; A_i++)
  {
    cin >> A[A_i];
  }
  vector<long> result = kFactorization(n, A);
  for (size_t i = 0; i < result.size(); i++)
  {
    cout << result[i] << (i != result.size() - 1 ? " " : "");
  }
  cout << endl;

  return 0;
}
