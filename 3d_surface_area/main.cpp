#include <bits/stdc++.h>

using namespace std;

int surfaceArea(vector<vector<int>> A)
{
  // Find total area if stacks were seperate, then remove touching faces
  int area_no_adjacent_edges = 0;
  for (auto y : A)
  {
    for (auto x : y)
    {
      if (x > 0)
      {
        // Top and bottom
        area_no_adjacent_edges += 2;
      }

      area_no_adjacent_edges += 4 * x;
    }
  }
  int duplicate_edges = 0;
  for (int i = 0; i < (int)A.size(); i++)
  {
    for (int j = 0; j < (int)A[i].size(); j++)
    {
      if (i - 1 >= 0)
      {
        duplicate_edges += 2 * std::min(A[i - 1][j], A[i][j]);
      }
      if (j - 1 >= 0)
      {
        duplicate_edges += 2 * std::min(A[i][j - 1], A[i][j]);
      }
    }
  }

  return area_no_adjacent_edges - duplicate_edges;
}

int main()
{
  int H;
  int W;
  cin >> H >> W;
  vector<vector<int>> A(H, vector<int>(W));
  for (int A_i = 0; A_i < H; A_i++)
  {
    for (int A_j = 0; A_j < W; A_j++)
    {
      cin >> A[A_i][A_j];
    }
  }
  int result = surfaceArea(A);
  cout << result << endl;
  return 0;
}
