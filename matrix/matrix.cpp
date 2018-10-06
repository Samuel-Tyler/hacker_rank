#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Disjoint_set
{
  Disjoint_set(const std::set<T>& nodes, const std::set<T>& catapults)
  {
    for (const auto& node : nodes)
    {
      // All elements start as single nodes
      m_parents[node] = node;
      m_depth[node]   = 1;
    }

    for (const auto& catapult : catapults)
    {
      m_has_catapult[catapult] = true;
    }
  }

  T find_root(const T& node)
  {
    const auto parent = m_parents[node];
    if (node == parent)
    {
      return node;
    }

    return find_root(parent);
  }

  void make_union(const T& node_one, const T& node_two)
  {
    T    new_parent            = find_root(node_one);
    T    new_child             = find_root(node_two);
    bool one_has_catapult      = m_has_catapult[new_parent];
    bool two_has_catapult      = m_has_catapult[new_child];
    m_has_catapult[new_parent] = one_has_catapult || two_has_catapult;
    m_depth[new_parent]        = m_depth[new_parent] + m_depth[new_child];
    m_parents[new_child]       = new_parent;
  }

  bool has_catapult(const T& node) { return m_has_catapult[find_root(node)]; }

private:
  std::unordered_map<T, int>  m_depth;
  std::unordered_map<T, T>    m_parents;
  std::unordered_map<T, bool> m_has_catapult;
};

struct Connection
{
  int start;
  int end;
  int weight;
};

int main()
{
  int n_nodes;
  int n_catapults;

  cin >> n_nodes >> n_catapults;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<Connection> connections(n_nodes - 1);
  std::set<int>      nodes;
  for (int i = 0; i < n_nodes; i++)
  {
    nodes.insert(i);
  }

  for (int i = 0; i < n_nodes - 1; i++)
  {
    cin >> connections[i].start >> connections[i].end >> connections[i].weight;
  }

  std::set<int> catapults;
  for (int i = 0; i < n_catapults; i++)
  {
    int x;
    cin >> x;
    catapults.insert(x);
  }

  Disjoint_set<int> disjoint_Set(nodes, catapults);

  std::sort(connections.begin(), connections.end(),
            [](const Connection& lhs, const Connection& rhs) {
              return lhs.weight > rhs.weight;
            });

  for (const auto& connection : connections)
  {
    if (!disjoint_Set.has_catapult(connection.start) ||
        !disjoint_Set.has_catapult(connection.end))
    {
      disjoint_Set.make_union(connection.start, connection.end);
    }
  }

  std::set<int> minimised_nodes;
  std::set<int> minimised_catapults;
  for (const auto& node : nodes)
  {
    minimised_nodes.insert(disjoint_Set.find_root(node));
  }

  for (const auto& catapult : catapults)
  {
    minimised_catapults.insert(disjoint_Set.find_root(catapult));
  }

  for (auto& connection : connections)
  {
    connection.start = disjoint_Set.find_root(connection.start);
    connection.end   = disjoint_Set.find_root(connection.end);
  }

  std::sort(connections.begin(), connections.end(),
            [](const Connection& lhs, const Connection& rhs) {
              return lhs.weight < rhs.weight;
            });

  Disjoint_set<int> minimised_disjoint_set(minimised_nodes,
                                           minimised_catapults);
  int               sum = 0;
  for (const auto& connection : connections)
  {
    if (minimised_disjoint_set.find_root(connection.start) !=
        minimised_disjoint_set.find_root(connection.end))
    {
      minimised_disjoint_set.make_union(connection.start, connection.end);
      sum += connection.weight;
    }
  }

  std::cout << sum;
  return 0;
}
