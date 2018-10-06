#include <bits/stdc++.h>

using namespace std;

int num_pairs(int items_in_set)
{
  return (items_in_set * (items_in_set - 1)) / 2;
}

int sherlockAndAnagrams(string s)
{
  std::unordered_map<std::string, std::vector<std::string>> chunks;
  int count = 0;
  for (size_t i = 0; i < s.length(); i++)
  {
    for (size_t j = 1; j <= s.length() - i; j++)
    {
      auto chunk        = s.substr(i, j);
      auto sorted_chunk = chunk;
      std::sort(sorted_chunk.begin(), sorted_chunk.end());

      chunks[sorted_chunk].push_back(chunk);
    }
  }

  for (auto& chunk : chunks)
  {
    count += num_pairs(chunk.second.size());
  }
  return count;
}

int main()
{
  int q;
  cin >> q;
  for (int a0 = 0; a0 < q; a0++)
  {
    string s;
    cin >> s;
    int result = sherlockAndAnagrams(s);
    cout << result << endl;
  }
  return 0;
}
