#include <bits/stdc++.h>

std::pair<Comparison_result, int> lcp(const std::string& a, int offset_a,
                                      const std::string& b, size_t offset_b)
{
  size_t j        = 0;
  size_t length_a = a.size() - offset_a;
  size_t length_b = b.size() - offset_b;

  for (; j < std::min(length_a, length_b); j++)
  {
    if (a[j + offset_a] == b[j + offset_b])
    {
      continue;
    }
    else if (a[j + offset_a] < b[j + offset_b])
    {
      return std::make_pair(Comparison_result::less, j);
    }
    else
    {
      return std::make_pair(Comparison_result::greater, j);
    }
  }

  // Matched up to end, return based on sizes
  if (length_a == length_b)
  {
    return std::make_pair(Comparison_result::equal, j);
  }
  else if (length_a < length_b)
  {
    return std::make_pair(Comparison_result::less, j);
  }
  else
  {
    return std::make_pair(Comparison_result::greater, j);
  }
}

int main()
{
  int n;
  std::cin >> n;
  std::set<std::string> strings;
  for (int i = 0; i < n; i++)
  {
    std::string s;
    std::cin >> s;

    for (size_t j = 0; j < s.length(); j++)
    {
      strings.insert(std::string(s.begin() + j, s.end()));
    }
  }
  auto substrings = std::vector<std::string>(strings.begin(), strings.end());

  int q;
  std::cin >> q;
  std::vector<int> lcp_array(substrings.size());
  lcp_array[0] = 0;
  for (size_t i = 1; i < substrings.size(); i++)
  {
    lcp_array[i] = lcp(substrings[i], 0, substrings[i - 1], 0).second;
  }

  for (int i = 0; i < q; i++)
  {
    int k;
    std::cin >> k;
    for (size_t i = 0; i < substrings.size(); i++)
    {
      const auto& s        = substrings[i];
      auto        common   = lcp_array[i];
      auto        inserted = (int)s.length() - common;
      if (inserted < k)
      {
        k -= inserted;
      }
      else
      {
        std::cout << (std::string(s.begin(), s.begin() + common + k))
                  << std::endl;
        goto done;
      }
    }
    std::cout << "INVALID" << std::endl;
  done:;
  }
  return 0;
}
