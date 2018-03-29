#include <bits/stdc++.h>

using namespace std;

std::map<std::pair<long, int>, long> cached_vals;
long raceRecurse(long current_height, size_t currentIndex,
                 const vector<int> &heights, vector<int> &prices)
{
  if (cached_vals.find(std::make_pair(current_height, currentIndex)) !=
      cached_vals.end())
  {
    return cached_vals[std::make_pair(current_height, currentIndex)];
  }

  long startHeight = current_height;
  int startIndex = currentIndex;
  long total_cost = 0;
  while (true)
  {
    if (currentIndex >= heights.size())
    {
      break;
    }

    else if (heights[currentIndex] > current_height)
    {
      total_cost += std::abs(heights[currentIndex] - current_height) +
                    prices[currentIndex];
      current_height = heights[currentIndex];
    }
    else if (heights[currentIndex] == current_height)
    {
      if (prices[currentIndex] < 0)
      {
        total_cost += std::abs(heights[currentIndex] - current_height) +
                      prices[currentIndex];
        current_height = heights[currentIndex];
      }
    }
    else
    {
      if (prices[currentIndex] < 0)
      {
        long noSwap =
            raceRecurse(current_height, currentIndex + 1, heights, prices);
        long swapRes = std::abs(heights[currentIndex] - current_height) +
                       prices[currentIndex] +
                       raceRecurse(heights[currentIndex], currentIndex + 1,
                                   heights, prices);

        total_cost += min(noSwap, swapRes);
        break;
      }
    }
    currentIndex++;
  }

  cached_vals[std::make_pair(startHeight, startIndex)] = total_cost;
  return total_cost;
}

long raceAgainstTime(int n, int mason_height, vector<int> heights,
                     vector<int> prices)
{
  long time_taken = n;
  long total_price = raceRecurse(mason_height, 0, heights, prices);
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
