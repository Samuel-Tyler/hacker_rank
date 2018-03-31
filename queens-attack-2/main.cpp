#include <bits/stdc++.h>

using namespace std;

int queensAttack(int n, int, int r_q, int c_q, vector<vector<int>> obstacles)
{
  struct pair
  {
    pair(int _y, int _x, int _r_q, int _c_q)
        : y(_y), x(_x), distance(std::max(abs(_x - _c_q), abs(y - _r_q)))
    {
    }
    int y;
    int x;
    int distance;
  };

  pair nearest_up    = {n, c_q, r_q, c_q};
  pair nearest_down  = {1, c_q, r_q, c_q};
  pair nearest_left  = {r_q, 1, r_q, c_q};
  pair nearest_right = {r_q, n, r_q, c_q};

  int left_up_offset    = min(n - r_q, c_q - 1);
  int left_down_offset  = min(r_q - 1, c_q - 1);
  int right_up_offset   = min(n - r_q, n - c_q);
  int right_down_offset = min(r_q - 1, n - c_q);

  pair nearest_left_up = {r_q + left_up_offset, c_q - left_up_offset, r_q, c_q};
  pair nearest_left_down = {r_q - left_down_offset, c_q - left_down_offset, r_q,
                            c_q};
  pair nearest_right_up = {r_q + right_up_offset, c_q + right_up_offset, r_q,
                           c_q};
  pair nearest_right_down = {r_q - right_down_offset, c_q + right_down_offset,
                             r_q, c_q};

  for (auto obstacle : obstacles)
  {
    int y = obstacle[0];
    int x = obstacle[1];
    if (x == c_q)
    {
      if (y - r_q > 0 && std::abs(y - r_q) < nearest_up.distance)
      {
        nearest_up = {y - 1, c_q, r_q, c_q};
      }
      if (y - r_q < 0 && std::abs(y - r_q) < nearest_down.distance)
      {
        nearest_down = {y + 1, c_q, r_q, c_q};
      }
    }
    if (y == r_q)
    {
      if (x - c_q > 0 && std::abs(x - c_q) < nearest_right.distance)
      {
        nearest_right = {r_q, x - 1, r_q, c_q};
      }
      if (x - c_q < 0 && std::abs(x - c_q) < nearest_left.distance)
      {
        nearest_left = {r_q, x + 1, r_q, c_q};
      }
    }

    int x_diff = x - c_q;
    int y_diff = y - r_q;

    if (x_diff == y_diff)
    {
      if (x_diff > 0)
      {
        if (abs(x_diff) < nearest_right_up.distance)
        {

          nearest_right_up = {y - 1, x - 1, r_q, c_q};
        }
      }
      else
      {
        if (abs(x_diff) < nearest_left_down.distance)
        {
          nearest_left_down = {y + 1, x + 1, r_q, c_q};
        }
      }
    }
    if (x_diff == -y_diff)
    {
      if (x_diff > 0)
      {
        if (abs(x_diff) < nearest_right_down.distance)
        {

          nearest_right_down = {y + 1, x - 1, r_q, c_q};
        }
      }
      else
      {
        if (abs(x_diff) < nearest_left_up.distance)
        {
          nearest_left_up = {y - 1, x + 1, r_q, c_q};
        }
      }
    }
  }

  int res = nearest_up.distance + nearest_down.distance +
            nearest_left.distance + nearest_right.distance +
            nearest_left_up.distance + nearest_left_down.distance +
            nearest_right_up.distance + nearest_right_down.distance;

  return res;
}

int main()
{
  int n;
  int k;
  cin >> n >> k;
  int r_q;
  int c_q;
  cin >> r_q >> c_q;
  vector<vector<int>> obstacles(k, vector<int>(2));
  for (int obstacles_i = 0; obstacles_i < k; obstacles_i++)
  {
    for (int obstacles_j = 0; obstacles_j < 2; obstacles_j++)
    {
      cin >> obstacles[obstacles_i][obstacles_j];
    }
  }
  std::cout << queensAttack(n, k, r_q, c_q, obstacles);
  return 0;
}
