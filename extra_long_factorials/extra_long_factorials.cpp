#include <bits/stdc++.h>

using namespace std;

class Big_integer
{
public:
  Big_integer() {}
  Big_integer(int n) : m_components(1, n) {}

  Big_integer& operator*=(int multiplicand)
  {
    int leftover = 0;
    int unit     = 1;
    for (auto& component : m_components)
    {
      unit *= m_stride;
      int new_component = component * multiplicand;
      int remainder     = new_component % m_stride;
      component         = remainder;
      component += leftover;
      leftover = new_component / m_stride;
    }

    if (leftover)
    {
      m_components.push_back(leftover);
    }

    return *this;
  }
  void print()
  {
    bool first_nonzero_printed = false;
    for (auto itr = m_components.crbegin(); itr != m_components.crend(); itr++)
    {
      int mask = m_stride / 10;
      while (mask > 0)
      {
        int digit = (*itr / mask) % 10;
        if (digit != 0 || first_nonzero_printed)
        {
          std::cout << digit;
          first_nonzero_printed = true;
        }
        mask /= 10;
      }
    }
    std::putchar('\n');
  }

private:
  const int        m_stride = 1000000;
  std::vector<int> m_components;
};

void extraLongFactorials(int n)
{
  Big_integer big_int(1);
  for (int i = 0; i < n; i++)
  {
    big_int *= i + 1;
  }
  big_int.print();
}

int main()
{
  int n;
  cin >> n;
  extraLongFactorials(n);
  return 0;
}
