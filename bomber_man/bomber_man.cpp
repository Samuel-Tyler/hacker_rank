#include <bits/stdc++.h>

using namespace std;

bool is_in_grid(size_t y, size_t x, const vector<vector<int>>& grid)
{
  return y < grid.size() && x < grid[y].size();
}

void run_iteration(int& n, std::vector<std::vector<int>>& timing_grid)
{
  for (size_t i = 0; i < timing_grid.size(); i++)
  {
    for (size_t j = 0; j < timing_grid[i].size(); j++)
    {
      if (timing_grid[i][j] == 1)
      {
        timing_grid[i][j] = -1;
      }
      else if (timing_grid[i][j] > 1)
      {
        timing_grid[i][j]--;
      }
      else
      {
        timing_grid[i][j] = 3;
      }
    }
  }

  for (size_t i = 0; i < timing_grid.size(); i++)
  {
    for (size_t j = 0; j < timing_grid[i].size(); j++)
    {
      if (timing_grid[i][j] == -1)
      {
        timing_grid[i][j] = 0;

        if (is_in_grid(i - 1, j, timing_grid) && timing_grid[i - 1][j] != -1)
        {
          timing_grid[i - 1][j] = 0;
        }
        if (is_in_grid(i + 1, j, timing_grid) && timing_grid[i + 1][j] != -1)
        {
          timing_grid[i + 1][j] = 0;
        }
        if (is_in_grid(i, j - 1, timing_grid) && timing_grid[i][j - 1] != -1)
        {
          timing_grid[i][j - 1] = 0;
        }
        if (is_in_grid(i, j + 1, timing_grid) && timing_grid[i][j + 1] != -1)
        {
          timing_grid[i][j + 1] = 0;
        }
      }
    }
  }

  n--;
}
void bomberMan(int n, vector<string> grid)
{
  // Initialise the grid
  std::vector<vector<int>> timing_grid;
  timing_grid.reserve(grid.size());
  for (size_t i = 0; i < grid.size(); i++)
  {
    timing_grid.push_back({});
    for (size_t j = 0; j < grid[i].size(); j++)
    {
      if (grid[i][j] == 'O')
      {
        timing_grid[i].push_back(2);
      }
      else
      {
        timing_grid[i].push_back(0);
      }
    }
  }

  // Bomberman waiting
  n--;

  if (n / 4 > 0)
  {
    n %= 4;
    n += 4;
  }

  while (n > 0)
  {
    run_iteration(n, timing_grid);
  }
  for (size_t i = 0; i < timing_grid.size(); i++)
  {
    for (size_t j = 0; j < timing_grid[i].size(); j++)
    {
      if (timing_grid[i][j] > 0)
      {
        putchar('O');
      }
      else
      {
        putchar('.');
      }
    }
    putchar('\n');
  }
}

int main()
{
  int r;
  int c;
  int n;
  cin >> r >> c >> n;
  vector<string> grid(r);
  for (int grid_i = 0; grid_i < r; grid_i++)
  {
    cin >> grid[grid_i];
  }
  bomberMan(n, grid);

  return 0;
}
