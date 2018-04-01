#include <bits/stdc++.h>

using namespace std;

map<std::string::const_iterator, bool> cache;

std::vector<int> check(const vector<string>&              pass,
                       const std::string::const_iterator& attempt_begin,
                       const std::string::const_iterator& attempt_end,
                       size_t                             attempt_len)
{
  auto cached = cache.find(attempt_begin);
  if (cached != cache.end())
  {
    return {};
  }
  cache[attempt_begin] = true;

  for (int i = 0; i < (int)pass.size(); i++)
  {
    const string& password = pass[i];
    if (attempt_len >= password.size() &&
        equal(password.begin(), password.end(), attempt_begin))
    {
      if (attempt_len == password.length())
      {
        return {i};
      }

      auto components = check(pass, attempt_begin + password.length(),
                              attempt_end, attempt_len - password.length());
      if (components.size() != 0)
      {
        components.push_back(i);
        return components;
      }
    }
  }

  return {};
}

map<char, bool>     char_seen;
map<string, string> attempt_history;
string passwordCracker(const vector<string>& pass, const string& attempt)
{
  string ret_string = {};
  cache.clear();

  auto cached = attempt_history.find(attempt);
  if (cached != attempt_history.end())
  {
    return cached->second;
  }

  if (std::all_of(attempt.begin(), attempt.end(),
                  [](char c) { return char_seen[c]; }))
  {
    auto res = check(pass, attempt.begin(), attempt.end(), attempt.length());
    for (auto itr = res.rbegin(); itr != res.rend(); itr++)
    {
      ret_string += pass[*itr];
      ret_string += ' ';
    }
  }

  attempt_history[attempt] = ret_string;
  return ret_string;
}

int main()
{
  int t;
  cin >> t;
  for (int a0 = 0; a0 < t; a0++)
  {
    int n;
    cin >> n;
    vector<string> pass(n);
    for (int pass_i = 0; pass_i < n; pass_i++)
    {
      cin >> pass[pass_i];
      for (char c : pass[pass_i])
      {
        char_seen[c] = true;
      }
    }
    string attempt;
    cin >> attempt;
    auto res = passwordCracker(pass, attempt);
    if (res.size() > 0)
    {
      std::cout << res << std::endl;
    }
    else
    {
      std::cout << "WRONG PASSWORD" << endl;
    }
  }
  return 0;
}
