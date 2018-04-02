#include <bits/stdc++.h>

using namespace std;

string canModify(vector<int> a)
{
  int n = 0;
  for (int i = 1; i < (int)a.size(); i++)
  {
    if (a[i] < a[i - 1])
    {
      if (n > 0)
      {
        return "NO";
      }
      n++;

      if (i + 1 < (int)a.size())
      {
        if (a[i + 1] >= a[i - 1])
        {
          a[i] = a[i - 1];
        }
        else if (i - 2 < 0 || a[i] >= a[i - 2])
        {
          a[i - 1] = a[i];
        }
        else
        {
          return "NO";
        }
      }
    }
  }

  return "YES";
}

int main()
{
  int n;
  cin >> n;

  for (int i = 0; i < n; i++)
  {

    int k;
    std::cin >> k;

    vector<int> a(k);

    for (int a_itr = 0; a_itr < k; a_itr++)
    {
      std::cin >> a[a_itr];
    }

    string result = canModify(a);

    cout << result << "\n";
  }

  return 0;
}
