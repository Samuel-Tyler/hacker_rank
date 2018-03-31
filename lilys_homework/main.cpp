#include <bits/stdc++.h>
#include <cassert>

using namespace std;

int count_swaps(vector<int>& arr, const vector<int>& sorted,
                std::map<int, std::set<int>>&        sorted_positions)
{
  int swaps = 0;

  while (sorted != arr)
  {
    for (size_t i = 0; i < arr.size(); i++)
    {
      if (arr[i] != sorted[i])
      {
        int desired_pos = [&] {

          for (int j : sorted_positions[arr[i]])
          {
            if (arr[j] == sorted[i])
            {
              return j;
            }
          }
          for (int j : sorted_positions[arr[i]])
          {
            if (arr[j] != arr[i])
            {
              return j;
            }
          }

          assert(!"Could not find!");
        }();

        assert(arr[i] != arr[desired_pos]);
        std::swap(arr[i], arr[desired_pos]);

        swaps++;
      }
    }
  }
  return swaps;
}

int lilysHomework(vector<int> arr)
{
  auto sorted = arr;
  std::sort(sorted.begin(), sorted.end());

  std::map<int, std::set<int>> sorted_positions;

  for (size_t i = 0; i < sorted.size(); i++)
  {
    sorted_positions[sorted[i]].insert(i);
  }

  auto reversed = vector<int>(arr.crbegin(), arr.crend());
  return std::min(count_swaps(arr, sorted, sorted_positions),
                  count_swaps(reversed, sorted, sorted_positions));
}
int main()
{
  int n;
  cin >> n;
  vector<int> arr(n);
  for (int arr_i = 0; arr_i < n; arr_i++)
  {
    cin >> arr[arr_i];
  }
  int result = lilysHomework(arr);
  cout << result << endl;
  return 0;
}
