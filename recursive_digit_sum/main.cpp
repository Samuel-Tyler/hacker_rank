#include <bits/stdc++.h>

using namespace std;

std::map<std::string, int> cache;

int digitSum(string n, int k)
{
  if (k > 1)
  {
    return digitSum(to_string(k * digitSum(n, 1)), 1);
  }

  if (n.length() == 1)
  {
    return n[0] - '0';
  }

  auto pos = cache.find(n);
  if (pos != cache.end())
  {
    return pos->second;
  }

  int sum = 0;
  for (char c : n)
  {
    sum += c - '0';
  }

  int result = digitSum(to_string(sum), 1);
  cache[n]   = result;
  return result;
}

int main()
{
  string n;
  int    k;
  cin >> n >> k;
  int result = digitSum(n, k);
  cout << result << endl;
  return 0;
}
