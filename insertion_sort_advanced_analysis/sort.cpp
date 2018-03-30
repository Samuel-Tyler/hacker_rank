#include <bits/stdc++.h>

using namespace std;

std::vector<int> tmp(100000);

long merge(vector<int>& arr, int left, int mid_point, int right)
{
  int i = left;
  int j = mid_point;
  long inv_count = 0;
  int k = left;

  while ((i <= mid_point - 1) && (j <= right))
  {
    if (arr[i] <= arr[j])
    {
      tmp[k++] = arr[i++];
    }
    else
    {
      tmp[k++] = arr[j++];
      inv_count += (mid_point - i);
    }
  }

  while (i <= mid_point - 1)
  {
    tmp[k++] = arr[i++];
  }
  while (j <= right)
  {
    tmp[k++] = arr[j++];
  }

  for (int i = left; i <= right; i++)
  {
      arr[i] = tmp[i];
  }
  
  return inv_count;
}

long merge_count(vector<int>& arr, int left, int right)
{
  long inv_count = 0;
  if (right > left)
  {
    int mid_point = (left + right) / 2;

    inv_count += merge_count(arr, left, mid_point);
    inv_count += merge_count(arr, mid_point + 1, right);

    inv_count += merge(arr, left, mid_point + 1, right);
  }
  return inv_count;
}

long insertionSort(vector<int> arr)
{
  return merge_count(arr, 0, arr.size() - 1);
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
    long result = insertionSort(arr);
    cout << result << endl;
  }
  return 0;
}
