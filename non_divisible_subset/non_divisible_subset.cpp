#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the nonDivisibleSubset function below.
 */
int nonDivisibleSubset(int k, vector<int> S)
{
  std::map<int, int> count_of_mods;

  for (int element : S)
  {
      int this_mod = element % k;
      count_of_mods[this_mod]++;
      if (this_mod * 2 == k || this_mod == 0)
      {
          // Can only have one of a number with half the mod of k
          count_of_mods[this_mod] = 1;
      }
  }

  struct mod_counts
  {
    int mod;
    int count;
  };

  std::vector<mod_counts> counts_vec;
  for (auto count_of_mod : count_of_mods)
  {
    counts_vec.push_back({count_of_mod.first, count_of_mod.second});
  }

  std::sort(counts_vec.begin(), counts_vec.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.count > rhs.count; });

  std::set<int> accepted_mods;
  int result = 0;
  for (const auto& mod_count : counts_vec)
  {
      if (accepted_mods.find(k - mod_count.mod) == accepted_mods.end())
      {
          result += mod_count.count;
          std::cerr << "Accepted: " << mod_count.mod << " count " << mod_count.count << '\n';
          accepted_mods.insert(mod_count.mod);
      }
  }

  return result;
}

int main()
{
  ofstream fout(getenv("OUTPUT_PATH"));

  string nk_temp;
  getline(cin, nk_temp);

  vector<string> nk = split_string(nk_temp);

  int n = stoi(nk[0]);

  int k = stoi(nk[1]);

  string S_temp_temp;
  getline(cin, S_temp_temp);

  vector<string> S_temp = split_string(S_temp_temp);

  vector<int> S(n);

  for (int S_itr = 0; S_itr < n; S_itr++)
  {
    int S_item = stoi(S_temp[S_itr]);

    S[S_itr] = S_item;
  }

  int result = nonDivisibleSubset(k, S);

  fout << result << "\n";

  fout.close();

  return 0;
}

vector<string> split_string(string input_string)
{
  string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char& x, const char& y) { return x == y and x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ')
  {
    input_string.pop_back();
  }

  vector<string> splits;
  char           delimiter = ' ';

  size_t i   = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != string::npos)
  {
    splits.push_back(input_string.substr(i, pos - i));

    i   = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, min(pos, input_string.length()) - i + 1));

  return splits;
}
