#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class cumulative_timer
{
public:
  cumulative_timer(const std::string &name) : m_ns(0), m_name(name) {}
  ~cumulative_timer()
  {
    std::cerr << m_name << " - Total active time " << m_ns.count() << "ns"
              << std::endl;
  }
  void begin() { m_start = std::chrono::high_resolution_clock::now(); }
  void end()
  {
    const auto end = std::chrono::high_resolution_clock::now();
    m_ns += end - m_start;
  }

private:
  std::chrono::high_resolution_clock::time_point m_start;
  std::chrono::nanoseconds m_ns;
  std::string m_name;
};

int main()
{
  std::ios::sync_with_stdio(false);

  std::string hamming_string;
  int string_len;
  std::cin >> string_len;

  hamming_string.reserve(string_len);
  std::cin >> hamming_string;

  int n_commands;
  std::cin >> n_commands;

  cumulative_timer c("C");
  cumulative_timer s("S");
  cumulative_timer r("R");
  cumulative_timer w("w");
  cumulative_timer h("H");

  for (int i = 0; i < n_commands; i++)
  {
    char command;
    std::cin >> command;
    switch (command)
    {
    case 'C':
    {
      c.begin();
      long l, r;
      char ch;
      std::cin >> l >> r >> ch;
      for (int j = l - 1; j < r; j++)
      {
        hamming_string[j] = ch;
      }
      c.end();
      break;
    }

    case 'S':
    {
      s.begin();
      long l1, r1, l2, r2;
      std::cin >> l1 >> r1 >> l2 >> r2;

      const auto s1 = hamming_string.substr(l1 - 1, r1 - (l1 - 1));
      const auto s2 = hamming_string.substr(r1, l2 - 1 - r1);
      const auto s3 = hamming_string.substr(l2 - 1, r2 - (l2 - 1));

      std::string s_final;
      s_final.append(s3.begin(), s3.end());
      s_final.append(s2.begin(), s2.end());
      s_final.append(s1.begin(), s1.end());

      std::swap_ranges(s_final.begin(), s_final.end(),
                       hamming_string.begin() + l1 - 1);
      s.end();
      break;
    }

    case 'R':
    {
      r.begin();
      {
        long l, r;
        std::cin >> l >> r;
        std::reverse(hamming_string.begin() + l - 1,
                     hamming_string.begin() + r);
      }
      r.end();
      break;
    }

    case 'W':
    {
      w.begin();
      long l, r;
      std::cin >> l >> r;
      std::cout << hamming_string.substr(l - 1, r - (l - 1)) << '\n';
      w.end();
      break;
    }

    case 'H':
    {
      h.begin();
      int l1, l2, len;
      std::cin >> l1 >> l2 >> len;
      int diff = 0;

      for (int j = 0; j < len; j++)
      {
        diff += hamming_string[l1 - 1 + j] != hamming_string[l2 - 1 + j];
      }

      std::cout << diff << '\n';
      h.end();
      break;
    }
    }
    //       std::cout << hamming_string << std::endl;
  }
  return 0;
}
