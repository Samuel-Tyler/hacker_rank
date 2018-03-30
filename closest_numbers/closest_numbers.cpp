#include <bits/stdc++.h>

using namespace std;

vector<int> closestNumbers(vector<int> arr)
{
  std::sort(arr.begin(), arr.end());

  int mindiff = std::numeric_limits<int>::max();

  vector<int> pairs;
  for (size_t i = 0; i < arr.size() - 1; i++)
  {
    const auto diff = abs(arr[i + 1] - arr[i]);
    if (diff < mindiff)
    {
      pairs.clear();
      mindiff = diff;
    }

    if (diff == mindiff)
    {
      pairs.push_back(arr[i]);
      pairs.push_back(arr[i + 1]);
    }
  }

  return pairs;
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
  vector<int> result = closestNumbers(arr);
  for (size_t i = 0; i < result.size(); i++)
  {
    cout << result[i] << (i != result.size() - 1 ? " " : "");
  }
  cout << endl;

  return 0;
}
