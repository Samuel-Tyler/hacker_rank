#include <bits/stdc++.h>

using namespace std;

string organizingContainers(vector<vector<int>> container)
{

  std::map<int, int>    counts;
  std::vector<int> sizes;
  for (size_t i = 0; i < container.size(); i++)
  {
    int total_elements = 0;
    for (size_t j = 0; j < container[i].size(); j++)
    {
      counts[j] += container[i][j];
      total_elements += container[i][j];
    }
      sizes.push_back(total_elements);
  }

  std::vector<int> counts_vec;

  for (auto count : counts)
  {
    counts_vec.push_back(count.second);
  }

  std::sort(sizes.begin(), sizes.end());
  std::sort(counts_vec.begin(), counts_vec.end());
  
  if (sizes == counts_vec)
  {
    return "Possible";
  }
  else
  {
    return "Impossible";
  }
}

int main()
{
  int q;
  cin >> q;
  for (int a0 = 0; a0 < q; a0++)
  {
    int n;
    cin >> n;
    vector<vector<int>> container(n, vector<int>(n));
    for (int container_i = 0; container_i < n; container_i++)
    {
      for (int container_j = 0; container_j < n; container_j++)
      {
        cin >> container[container_i][container_j];
      }
    }
    string result = organizingContainers(container);
    cout << result << endl;
  }
  return 0;
}
