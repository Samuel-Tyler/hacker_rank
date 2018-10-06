#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Disjoint_set
{
  Disjoint_set(const std::vector<T>& nodes)
      : m_values(nodes), m_mst(nodes.size(), 0), m_min(nodes),
        m_max(nodes)
  {
    for (size_t i = 0; i < nodes.size(); i++)
    {
      // All elements start as single nodes
      m_parents[i] = i;
    }
  }

  int find_root(const int node) const
  {
    const auto parent_iter = m_parents.find(node);
    assert(parent_iter != m_parents.end());
    const auto parent = parent_iter->second;
    if (node == parent)
    {
      return node;
    }
    else
    {
      return find_root(parent);
    }
  }

  void make_union(const int node_one, const int node_two, int weight = 0)
  {
    auto root_one = find_root(node_one);
    auto root_two = find_root(node_two);
    if (root_one != root_two)
    {
      m_parents[root_one] = root_two;
      m_mst[root_two] += m_mst[root_one];
      m_mst[root_two] += weight;
      m_min[root_two] = std::min(m_min[root_one], m_min[root_two]);
      m_max[root_two] = std::max(m_max[root_one], m_max[root_two]);
    }
  }

  long group_mst(int node) const { return m_mst[find_root(node)]; }
  const T& group_min(int node) const { return m_min[find_root(node)]; }
  const T& group_max(int node) const { return m_max[find_root(node)]; }

private:
  std::unordered_map<int, int> m_parents;
  std::vector<T>               m_values;
  std::vector<long>            m_mst;
  std::vector<T>               m_min;
  std::vector<T>               m_max;
};

struct Connection
{
  int start;
  int end;
  int weight;
};

template <typename T>
Disjoint_set<T> build_msts(const std::vector<T>&    nodes,
                           std::vector<Connection>& connections)
{
  Disjoint_set<T> djs(nodes);
  std::sort(connections.begin(), connections.end(),
            [](const Connection& lhs, const Connection& rhs) {
              return lhs.weight < rhs.weight;
            });
  for (const auto& connection : connections)
  {
    djs.make_union(connection.start, connection.end, connection.weight);
  }
  return djs;
}

int main()
{
  int q;
  std::cin >> q;

  for (int i = 0; i < q; i++)
  {
    long n, m, c_lib, c_road;
    std::cin >> n >> m >> c_lib >> c_road;
    std::vector<long>        nodes(n, c_lib);
    std::vector<Connection> connections(m);
    for (int j = 0; j < m; j++)
    {
      std::cin >> connections[j].start;
      std::cin >> connections[j].end;
      connections[j].start--;
      connections[j].end--;
      connections[j].weight = c_road;
    }

    if (c_lib < c_road)
    {
      std::cout << c_lib * n << std::endl;
    }
    else
    {
      const auto    djs = build_msts(nodes, connections);
      std::set<int> visited;
      long          score = 0;
      for (int j = 0; j < n; j++)
      {
        const auto root = djs.find_root(j);
        if (visited.find(root) == visited.end())
        {
          score += djs.group_mst(root);
          score += djs.group_min(root);
          visited.insert(root);
        }
      }
      std::cout << score << std::endl;
    }
  }
  return 0;
}
