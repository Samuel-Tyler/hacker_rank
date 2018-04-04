#include <bits/stdc++.h>

using namespace std;

bool check(int offset_y, int offset_x, vector<string>& G, vector<string>& P)
{
  for (size_t i = 0; i < P.size(); i++)
  {
    for (size_t j = 0; j < P[0].size(); j++)
    {
      if (G[offset_y + i][offset_x + j] != P[i][j])
      {
        return false;
      }
    }
  }
  return true;
}

string gridSearch(vector<string> G, vector<string> P)
{
  for (size_t i = 0; i <= G.size() - P.size(); i++)
  {
    for (size_t j = 0; j <= G[0].size() - P[0].size(); j++)
    {
        if (check(i, j, G, P))
        {
            return "YES";
        }
    }
  }
  return "NO";
}

int main()
{
  int t;
  cin >> t;
  for (int a0 = 0; a0 < t; a0++)
  {
    int R;
    int C;
    cin >> R >> C;
    vector<string> G(R);
    for (int G_i = 0; G_i < R; G_i++)
    {
      cin >> G[G_i];
    }
    int r;
    int c;
    cin >> r >> c;
    vector<string> P(r);
    for (int P_i = 0; P_i < r; P_i++)
    {
      cin >> P[P_i];
    }
    string result = gridSearch(G, P);
    cout << result << endl;
  }
  return 0;
}
