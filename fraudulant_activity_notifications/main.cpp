#include <bits/stdc++.h>

using namespace std;

int double_median(const std::vector<int>& sorted_vals)
{
  int size = sorted_vals.size();
  int mid  = size / 2;
  if (size % 2 == 0)
  {
    return sorted_vals[mid] + sorted_vals[mid - 1];
  }
  else
  {
    return sorted_vals[mid] * 2;
  }
}

int activityNotifications(vector<int>& expenditure, int d)
{
  std::vector<int> counts(200, 0);
  std::vector<int> active(d);

  for (int i = 0; i < d; i++)
  {
    counts[expenditure[i]]++;
  }

  int over = 0;
  size_t size = expenditure.size();
  for (size_t i = 0; i < size - d; i++)
  {
    int spent = expenditure[i + d];
    int k     = 0;
    for (int i = 0; i < 200; i++)
    {
      for (int j = 0; j < counts[i]; j++)
      {
        active[k++] = i;
      }
      // Only need to sort up to midpoint, cancel now
      if (k > d / 2)
      {
        break;
      }
    }

    // std::cerr << " median " << median(active);
    // std::cerr << " this " << spent << std::endl;
    if (spent >= double_median(active))
    {
      over++;
    }
    counts[expenditure[i]]--;
    counts[spent]++;
  }
  return over;
}

int main()
{
  int n;
  int d;
  cin >> n >> d;
  vector<int> expenditure(n);
  for (int expenditure_i = 0; expenditure_i < n; expenditure_i++)
  {
    cin >> expenditure[expenditure_i];
  }
  int result = activityNotifications(expenditure, d);
  cout << result << endl;
  return 0;
}
