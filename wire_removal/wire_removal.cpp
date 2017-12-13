#include "../utils/print_container.hpp"
#include <algorithm>
#include <cassert>
#include <experimental/optional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <vector>

struct node;
std::vector<node> nodes;
std::set<int> assigned_nodes;
struct node
{
public:
  node(int n) : m_n(n), m_distance_from_root(0) {}
  long long int get_num() const { return m_n; }
  long long int get_num_children() const
  {
    if (!m_total_children)
    {
      m_total_children =
          std::accumulate(m_children.begin(), m_children.end(), 0ll,
                          [](long n_nodes, const int n) {
                            return n_nodes + 1 + nodes.at(n).get_num_children();
                          });
    }
    return *m_total_children;
  }

  node(const node &) = default;
  node &operator=(const node &) = default;

  long total_probability_bins() const
  {
    return m_distance_from_root +
           std::accumulate(m_children.begin(), m_children.end(), 0ll,
                           [](long n_nodes, const long &n) {
                             return n_nodes +
                                    nodes.at(n).total_probability_bins();
                           });
  }

  node *find_node(int n)
  {
    if (m_n == n)
    {
      return this;
    }
    else
    {
      for (auto &child : m_children)
      {
        node *matching_child = nodes.at(child).find_node(n);
        if (matching_child != nullptr)
        {
          return matching_child;
        }
      }
      return nullptr;
    }
  }

  void set_distance(long distance) { m_distance_from_root = distance; }
  void add_child(int n)
  {
    nodes[n].set_distance(m_distance_from_root + 1);
    m_children.push_back(n);
  }

  void build()
  {
    for (const int connection : m_connected)
    {
      if (assigned_nodes.find(connection) == assigned_nodes.end())
      {
        assigned_nodes.insert(connection);
        add_child(connection);
        //     std::cerr << "Adding child" << connection << std::endl;
      }
    }

    for (const auto &child : m_children)
    {
      nodes[child].build();
    }
  }

  long long int find_sum_children() const
  {
    if (!m_total_sum_children)
    {
      const auto weighted_children =
          std::accumulate(m_children.begin(), m_children.end(), 0ll,
                          [this](long n, const long child) {
                            return n +
                                   (1ll + nodes.at(child).get_num_children()) *
                                       (1ll + m_distance_from_root);
                          });
      const auto childs_weighted_children =
          std::accumulate(m_children.begin(), m_children.end(), 0ll,

                          [this](long n, const long child) {
                            return n + nodes.at(child).find_sum_children();
                          });

      m_total_sum_children = weighted_children + childs_weighted_children;
    }
    else
    {
      std::cout << "wut" << std::endl;
    }
    return *m_total_sum_children;
  }

  void print() const
  {
    std::cerr << "Node : " << m_n << " Distance from root "
              << m_distance_from_root << " total children "
              << get_num_children() << " total sum children"
              << find_sum_children() << '\n';
    for (const auto &child : m_children)
    {
      nodes.at(child).print();
    }
  }

  void add_connection(int connection) { m_connected.push_back(connection); }

  int get_id() const { return m_n; }

private:
  long long int m_n;
  long long int m_distance_from_root;
  std::vector<int> m_children;
  std::vector<int> m_connected;
  mutable std::experimental::optional<long long int> m_total_children;
  mutable std::experimental::optional<long long int> m_total_sum_children;
};

int main()
{
  int total_nodes;
  std::cin >> total_nodes;

  std::vector<std::pair<int, int>> links;
  links.reserve(total_nodes);
  for (int i = 1; i < total_nodes; i++)
  {
    int node1, node2;
    std::cin >> node1 >> node2;
    links.push_back(std::make_pair(node1, node2));
  }
  assert(links.size() + 1 == (size_t)total_nodes);

  nodes.reserve(total_nodes + 1);
  for (int i = 0; i <= total_nodes; i++)
  {
    nodes.push_back(node(i));
  }
  for (const auto &link : links)
  {
    nodes[link.first].add_connection(link.second);
    nodes[link.second].add_connection(link.first);
  }

  std::cerr << "insert done" << std::endl;
  /*  for (const auto link : links_sorted)
    {
      print(link);
    }
    */
  auto &root = nodes[1];
  assigned_nodes.insert(1);
  root.build();

  std::cerr << "build done" << std::endl;
  // root.print();

  assert(total_nodes == root.get_num_children() + 1);
  std::cerr << "total_children = " << root.get_num_children() << std::endl;
  const auto weighted_total_nodes = root.total_probability_bins() * total_nodes;
  const auto weighted_remaining_nodes =
      weighted_total_nodes - root.find_sum_children();
  std::cerr << "bins = " << root.total_probability_bins() << std::endl;
  std::cerr << "remaining nodes = " << weighted_remaining_nodes << std::endl;
  std::cout << std::setprecision(15)
            << weighted_remaining_nodes / (double)root.total_probability_bins();
}
