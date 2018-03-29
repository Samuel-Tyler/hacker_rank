#include <bits/stdc++.h>

using namespace std;

long raceAgainstTime(int n, int mason_height, vector<int> heights,
                     vector<int> prices)
{
  std::vector<int> selected;

  long current_height = mason_height;
  long time_taken = n;
  long total_price = 0;
  for (int i = 0; i < n - 1; i++)
  {
    if (heights[i] > current_height)
    {
      time_taken += heights[i] - current_height;
      total_price += prices[i];
      current_height = heights[i];
      selected.push_back(i);
    }
    else if ((std::abs(heights[i] - current_height)*2 + prices[i]) < 0)
    {
      time_taken += std::abs(heights[i] - current_height);
      total_price += prices[i];
      current_height = heights[i];
      selected.push_back(i);
    }
  }
  int j = 0;
  std::vector<int> new_selected;
  for (int i = 0; i < n - 1; i++)
  {
    // skip if already selected
    if (selected[j] == i)
    {
      j++;
      new_selected.push_back(i);
    }
    if (j - 1 >= 0 && j < (int)selected.size())
    {
      if (prices[i] < 0)
      {
        if (heights[i] < heights[selected[j - 1]] && heights[i] < heights[selected[j]])
        {
          total_price += prices[i];
          new_selected.push_back(i);
        }
      }
    }
  }
 
  j = 0;
  for (int i = 0; i < n - 1; i++)
  {
    // skip if already selected
    if (new_selected[j] == i)
    {
      std::cout << "idx: " << i << "height: " << heights[i] << "price: " << prices[i] << std::endl;
      j++;
    }
  }

  return total_price + time_taken;
}

int main()
{
  int n;
  cin >> n;
  int mason_height;
  cin >> mason_height;
  vector<int> heights(n - 1);
  for (int heights_i = 0; heights_i < n - 1; heights_i++)
  {
    cin >> heights[heights_i];
  }
  vector<int> prices(n - 1);
  for (int prices_i = 0; prices_i < n - 1; prices_i++)
  {
    cin >> prices[prices_i];
  }
  long result = raceAgainstTime(n, mason_height, heights, prices);
  cout << result << endl;
  return 0;
}
