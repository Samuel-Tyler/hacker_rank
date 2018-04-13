#include <bits/stdc++.h>

using namespace std;

void almostSorted(vector<int> arr)
{
  int last_val         = INT_MIN;
  int first_not_sorted = -1;

  for (size_t i = 0; i < arr.size() - 1; i++)
  {
    if (arr[i] > arr[i + 1])
    {
      first_not_sorted = i;
      break;
    }
  }

  if (first_not_sorted == -1)
  {
    std::cout << "yes\n";
    return;
  }

  last_val            = arr[first_not_sorted];
  int last_not_sorted = first_not_sorted + 1;
  for (size_t i = first_not_sorted + 1; i < arr.size(); i++)
  {
    if (arr[i] < last_val)
    {
      last_not_sorted = i;
    }
    last_val = arr[i];
  }

  std::swap(arr[first_not_sorted], arr[last_not_sorted]);

  if (std::is_sorted(arr.begin(), arr.end()))
  {
    std::cout << "yes\n";
    std::cout << "swap " << first_not_sorted + 1 << " " << last_not_sorted + 1
              << '\n';
    return;
  }
  // Revert swap
  std::swap(arr[first_not_sorted], arr[last_not_sorted]);

  std::reverse(arr.begin() + first_not_sorted, arr.begin() + last_not_sorted + 1);
  if (std::is_sorted(arr.begin(), arr.end()))
  {
    std::cout << "yes\n";
    std::cout << "reverse " << first_not_sorted + 1 << " "
              << last_not_sorted + 1 << '\n';
    return;
  }

  std::cout << "no";
  return;
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
  almostSorted(arr);
  return 0;
}
