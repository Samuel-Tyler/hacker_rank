#include <bits/stdc++.h>

using namespace std;

string encryption(string s)
{
  auto root_length = sqrt(s.length());
  int  rows        = floor(root_length);
  int  cols        = ceil(root_length);

  std::cerr << "rows" << rows << '\n';
  std::cerr << "cols" << cols << '\n';

  std::string encrypted;

  if (rows != cols)
  {
    rows++;
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      size_t new_cell_location = j * cols + i;
      if (new_cell_location < s.length())
      {
        encrypted.push_back(s[new_cell_location]);
      }
    }
    encrypted.push_back(' ');
  }
  return encrypted;
}

int main()
{
  string s;
  cin >> s;
  string result = encryption(s);
  cout << result << endl;
  return 0;
}
