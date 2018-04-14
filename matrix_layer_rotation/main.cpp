#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

class matrix
{
public:
  matrix()
  {
    std::cin >> m_height >> m_width >> m_rotation;
    m_vals.reserve(m_width * m_height);
    for (int i = 0; i < m_width * m_height; i++)
    {
      int x;
      std::cin >> x;
      m_vals.push_back(x);
    }
  }

  int get(int x, int y) const { return m_vals[x + y * m_width]; }

  int get_converted(int x, int y) const
  {
    const auto min_distance =
        std::min({x - 0, y - 0, m_width - 1 - x, m_height - 1 - y});
    const int equiv_rotations =
        m_rotation % (2 * (m_width + m_height - 4 * min_distance - 2));

    for (int i = 0; i < equiv_rotations; i++)
    {
      if (x - 0 == min_distance && y - 1 >= min_distance)
      {
        y--;
      }
      else if (y - 0 == min_distance &&
               ((m_width - 1 - (x + 1)) >= min_distance))
      {
        x++;
      }
      else if ((m_width - 1 - x == min_distance) &&
               ((m_height - 1 - (y + 1)) >= min_distance))
      {
        y++;
      }
      else if (m_height - 1 - y == min_distance && x - 1 >= min_distance)
      {
        x--;
      }

      // std::cout << "x = " << x << " y = " << y << std::endl;
      const auto min_distance_after =
          std::min({x - 0, y - 0, m_width - 1 - x, m_height - 1 - y});
      assert(min_distance == min_distance_after);
    }
    return get(x, y);
  }

  void print()
  {
    for (int i = 0; i < m_height; i++)
    {
      for (int j = 0; j < m_width; j++)
      {
        std::cout << get_converted(j, i) << " ";
      }
      std::cout << '\n';
    }
  }

private:
  int              m_height;
  int              m_width;
  int              m_rotation;
  std::vector<int> m_vals;
};

int main()
{
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  matrix m;
  m.print();
  return 0;
}
