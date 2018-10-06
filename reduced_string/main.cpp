#include <bits/stdc++.h>

using namespace std;

void remove_empty(std::string& s)
{
  s.erase(remove_if(s.begin(), s.end(), [](char c) { return c == ' '; }),
          s.end());
}

string super_reduced_string(string& s)
{
  auto previous_len = s.length();
  do
  {
    previous_len = s.length();
    for (int i = 1; i < (int)s.length(); i++)
    {
      if (s[i - 1] == s[i])
      {
        s[i - 1] = ' ';
        s[i]     = ' ';
      }
    }
    remove_empty(s);

  } while (s.length() < previous_len);

  if (s.length() == 0)
  {
    return "Empty String";
  }
  return s;
}

int main()
{
  string s;
  cin >> s;
  string result = super_reduced_string(s);
  cout << result << endl;
  return 0;
}
