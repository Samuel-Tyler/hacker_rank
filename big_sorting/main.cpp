#include <iostream>
#include <set>
#include <string>

struct big_num_less
{
  bool operator()(const std::string &lhs, const std::string &rhs) const
  {
    if (lhs.length() < rhs.length())
    {
      return true;
    }
    else if (lhs.length() == rhs.length())
    {
      return lhs < rhs;
    }
    else
    {
      return false;
    }
  }
};

int main()
{
  long n;
  std::cin >> n;
  std::multiset<std::string, big_num_less> vals_sorted;
  for (int i = 0; i < n; i++)
  {
    std::string long_num;
    std::cin >> std::ws >> long_num;
    vals_sorted.insert(long_num);
  }

  for (const auto str : vals_sorted)
  {
    std::cout << str << '\n';
  }
}
