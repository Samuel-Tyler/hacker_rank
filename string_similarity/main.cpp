#include <bits/stdc++.h>

struct myTuple
{
  int originalIndex; // stores original index of suffix
  int firstHalf;     // store rank for first half of suffix
  int secondHalf;    // store rank for second half of suffix
};

bool cmp(myTuple a, myTuple b)
{
  if (a.firstHalf == b.firstHalf)
    return a.secondHalf < b.secondHalf;
  else
    return a.firstHalf < b.firstHalf;
}

enum class Comparison_result
{
  less,
  equal,
  greater
};

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

class Suffix_array
{
public:
  Suffix_array(const std::string& s) : m_string(s), m_array(s.length())
  {
    int              N = s.size();
    std::vector<int> suffix_ranks(N);

    for (int i = 0; i < N; ++i)
    {
      suffix_ranks[i] = s[i] - 'a';
    }

    // Iterate log(n) times i.e. till when all the suffixes are sorted
    // 'cnt' store length of suffix which is going to be compared

    // On each iteration we initialize tuple for each suffix array
    // with values computed from previous iteration

    for (int cnt = 1; cnt < N; cnt *= 2)
    {
      auto previous_suffix_ranks = suffix_ranks;
      for (int i = 0; i < N; ++i)
      {
        m_array[i].firstHalf = previous_suffix_ranks[i];
        m_array[i].secondHalf =
            i + cnt < N ? previous_suffix_ranks[i + cnt] : -1;
        m_array[i].originalIndex = i;
      }

      // On the basis of tuples obtained sort the tuple array

      std::sort(m_array.begin(), m_array.begin() + N, cmp);

      suffix_ranks[m_array[0].originalIndex] = 0;

      for (int current_rank = 0, i = 1; i < N; ++i)
      {
        if (m_array[i - 1].firstHalf != m_array[i].firstHalf ||
            m_array[i - 1].secondHalf != m_array[i].secondHalf)
        {
          ++current_rank;
        }

        suffix_ranks[m_array[i].originalIndex] = current_rank;
      }
    }
  }

  void print()
  {
    for (size_t i = 0; i < m_array.size(); ++i)
    {
      std::cout << m_array[i].originalIndex << " : "
                << std::string(m_string.begin() + m_array[i].originalIndex,
                               m_string.end())
                << std::endl;
    }
  }

  int contains_recursive(const std::string& str, int current, int left, int mid,
                         int right)
  {
    if (right < left)
    {
      return -1;
    }
    current = 0;
    auto comp_res =
        lcp(str, current, m_string, m_array[mid].originalIndex + current);
    auto k = comp_res.second + current;
    if (comp_res.second == (int)str.length() ||
        comp_res.first == Comparison_result::equal)
    {
      return mid;
    }
    else if (comp_res.first == Comparison_result::less)
    {
      int new_end   = mid - 1;
      int new_begin = left;
      int new_mid   = (new_begin + new_end) / 2;

      if (new_end < new_mid || new_begin > new_mid)
      {
        return -1;
      }

      assert(m_lcp_lr.find(std::make_pair(mid, new_mid)) != m_lcp_lr.end());
      int common_chars = m_lcp_lr[std::make_pair(mid, new_mid)];
      if (k == common_chars)
      {
        return contains_recursive(str, k, left, new_mid, new_end);
      }
      else if (k > common_chars)
      {
        return contains_recursive(str, k, new_mid + 1,
                                  (new_mid + 1 + new_end) / 2, new_end);
      }
      else if (k < common_chars)
      {
        return contains_recursive(str, k, new_begin,
                                  (new_begin + new_mid - 1) / 2, new_mid - 1);
      }
    }
    else if (comp_res.first == Comparison_result::greater)
    {
      int new_begin = mid + 1;
      int new_end   = right;
      int new_mid   = (new_begin + new_end) / 2;
      if (new_end < new_mid || new_begin > new_mid)
      {
        return -1;
      }

      assert(m_lcp_lr.find(std::make_pair(mid, new_mid)) != m_lcp_lr.end());
      int common_chars = m_lcp_lr[std::make_pair(mid, new_mid)];
      if (k == common_chars)
      {
        return contains_recursive(str, k, new_begin, new_mid, new_end);
      }
      else if (k < common_chars)
      {
        return contains_recursive(str, k, new_mid + 1,
                                  (new_mid + 1 + new_end) / 2, new_end);
      }
      else if (k > common_chars)
      {
        return contains_recursive(str, k, new_begin,
                                  (new_begin + new_mid - 1) / 2, new_mid - 1);
      }
    }

    return -1;
  }

  int find(const std::string& str)
  {
    get_lcp_lr();
    auto end_char = m_string.length() - 1;
    return contains_recursive(str, 0, 0, end_char / 2, end_char);
  }

  bool contains(const std::string& str) { return find(str) != -1; }

  const std::map<std::pair<int, int>, int>& get_lcp_lr()
  {
    if (m_lcp_lr.empty())
    {
      calculate_lcp_lr();
    }
    return m_lcp_lr;
  }

  const std::vector<int>& get_lcp()
  {
    if (m_lcp_array.empty())
    {
      calculate_lcp_array();
    }
    return m_lcp_array;
  }

  std::vector<int> get_ordered_indexes()
  {
    std::vector<int> res(m_array.size());
    for (size_t i = 0; i < m_array.size(); i++)
    {
      res[i] = m_array[i].originalIndex;
    }
    return res;
  }

  std::vector<std::string> get_ordered_suffixes()
  {

    std::vector<std::string> res(m_array.size());
    for (size_t i = 0; i < m_array.size(); i++)
    {
      res[i] = std::string(m_string.begin() + m_array[i].originalIndex,
                           m_string.end());
    }
    return res;
  }

private:
  std::string          m_string;
  std::vector<myTuple> m_array;
  std::vector<int>     m_lcp_array;
  std::map<std::pair<int, int>, int> m_lcp_lr;

  // using kasai method
  void calculate_lcp_array()
  {
    const auto indexes = get_ordered_indexes();
    int        n       = (int)m_array.size();
    int        k       = 0;
    m_lcp_array        = std::vector<int>(n, 0);
    std::vector<int> rank(n, 0);

    for (int i = 0; i < n; i++)
    {
      rank[indexes[i]] = i;
    }

    for (int i = 0; i < n; i++, k ? k-- : 0)
    {
      if (rank[i] == n - 1)
      {
        k = 0;
        continue;
      }
      int j = indexes[rank[i] + 1];
      while (i + k < n && j + k < n && m_string[i + k] == m_string[j + k])
      {
        k++;
      }

      m_lcp_array[rank[i] + 1] = k;
    }
  }

  void calculate_lcp_lr_dfs(std::map<std::pair<int, int>, int>& lcp_lr,
                            int left, int mid, int right)
  {
    if (right <= left)
    {
      return;
    }

    for (int i = left; i <= right; i++)
    {
      lcp_lr[std::make_pair(mid, i)] = lcp(m_string, m_array[i].originalIndex,
                                           m_string, m_array[mid].originalIndex)
                                           .second;
    }

    calculate_lcp_lr_dfs(lcp_lr, left, (left + mid - 1) / 2, mid - 1);
    calculate_lcp_lr_dfs(lcp_lr, mid + 1, (right + mid + 1) / 2, right);
  }

  void calculate_lcp_lr()
  {
    auto end = m_string.length() - 1;
    calculate_lcp_lr_dfs(m_lcp_lr, 0, end / 2, end);
  }
};

int main()
{
  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++)
  {
    std::string s;
    std::cin >> s;
    Suffix_array suffix_array(s);
    const auto&  lcp_table = suffix_array.get_lcp();
    const auto   indexes   = suffix_array.get_ordered_indexes();

    long score = 0;

    long previous_common        = 0;
    long matching_substring_pos = s.length() - 1;
    for (size_t i = 0; i < s.length(); i++)
    {
      if (lcp_table[i] < previous_common)
      {
        matching_substring_pos = i - 1;
        assert(indexes[matching_substring_pos] == 0);
        break;
      }
      else
      {
        previous_common +=
            lcp(s, previous_common, s, indexes[i] + previous_common).second;
        score += previous_common;
      }
    }

    auto previous_match = (int)s.length();
    auto index          = suffix_array.get_ordered_indexes();
    for (size_t i = matching_substring_pos + 1; i < s.length(); i++)
    {
      if (lcp_table[i] == 0)
      {
        break;
      }
      else
      {
        previous_match = std::min(previous_match, lcp_table[i]);
        score += previous_match;
      }
    }

    std::cout << score << std::endl;
  }
  return 0;
}
