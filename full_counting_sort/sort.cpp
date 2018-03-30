#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<vector<string>> strings(100);
  for (int a0 = 0; a0 < n; a0++)
  {
    int    x;
    string s;
    cin >> x >> s;
    if (a0 >= n / 2)
    {
      strings[x].push_back(s);
    }
    else
    {
      strings[x].push_back(std::string("-"));
    }
  }

  for (auto vec : strings)
  {
    for (std::string str : vec)
    {
      std::cout << str << ' ';
    }
  }
  return 0;
}
