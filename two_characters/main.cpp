#include <bits/stdc++.h>

using namespace std;

bool is_valid(const std::string& s)
{
  if (s.length() > 2)
  {
    char a = s[0];
    char b = s[1];
    for (int i = 0; i < (int)s.length(); i++)
    {
      if (i % 2 == 0)
      {
        if (s[i] != a)
        {
          return false;
        }
      }
      if (i % 2 == 1)
      {
        if (s[i] != b)
        {
          return false;
        }
      }
    }
  }
  return true;
}

std::string remove_all_but(char a, char b, std::string s)
{
  s.erase(std::remove_if(s.begin(), s.end(),
                         [&](char c) { return !(c == a || c == b); }),
          s.end());
  return s;
}

int twoCharaters(string s)
{

  std::set<char> chars;

  for (char c : s)
  {
    chars.insert(c);
  }

  int max_length = 0;

  for (auto first_char = chars.begin(); std::next(first_char) != chars.end();
       first_char++)
  {
    for (auto second_char = std::next(first_char); second_char != chars.end();
         second_char++)
    {
      auto str = remove_all_but(*first_char, *second_char, s);
      if (is_valid(str))
      {
        max_length = std::max(max_length, (int)str.length());
      }
    }
  }
  return max_length;
}

int main()
{
  int l;
  cin >> l;
  string s;
  cin >> s;
  int result = twoCharaters(s);
  cout << result << endl;
  return 0;
}
