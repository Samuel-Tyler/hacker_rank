#include <bits/stdc++.h>

using namespace std;

int equal(vector<int> arr)
{
  std::vector<int> diffs;
  diffs.reserve(arr.size());
  std::sort(arr.begin(), arr.end());
  for (size_t i = 0; i < arr.size(); i++)
  {
    diffs.push_back(arr[i] - arr[0]);
  }
  int min_sum = INT_MAX;
  for (int i = 0; i < 1; i++)
  {
    int sum = 0;
    for (int diff : diffs)
    {
      sum += diff / 5;
      sum += (diff % 5) / 2;
      sum += (diff % 5) % 2;
    }
    for (int& j : diffs)
    {
      j++;
    }
    min_sum = std::min(min_sum, sum);
  }
  return min_sum;
}

int main()
{
  int t;
  cin >> t;
  for (int a0 = 0; a0 < t; a0++)
  {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int arr_i = 0; arr_i < n; arr_i++)
    {
      cin >> arr[arr_i];
    }
    int result = equal(arr);
    cout << result << endl;
  }
  return 0;
}
