#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void bfs(std::unordered_map<int, std::unordered_set<int>>& partners, int start,
         int n_nodes)
{
  std::deque<int>              frontier;
  std::unordered_set<int>      visited;
  std::unordered_map<int, int> parents;
  std::vector<int>             distances(n_nodes + 1, -1);
  frontier.push_back(start);
  distances[start] = 0;

  while (!frontier.empty())
  {
    int current = frontier[0];
    frontier.pop_front();
    for (int partner : partners[current])
    {
      if (visited.count(partner) == 0)
      {
        parents[partner]   = current;
        distances[partner] = distances[current] + 6;

        frontier.push_back(partner);
        visited.insert(partner);
      }
    }
  }

  for (size_t i = 1; i < distances.size(); i++)
  {
    if (i != (size_t)start)
    {
      std::cout << distances[i] << ' ';
    }
  }
  std::cout << std::endl;
}

int main()
{
  int n_queries;
  std::cin >> n_queries;
  for (int q = 0; q < n_queries; q++)
  {
    int                                              n_nodes;
    int                                              n_edges;
    std::unordered_map<int, std::unordered_set<int>> partners;

    std::cin >> n_nodes >> n_edges;
    for (int i = 0; i < n_edges; i++)
    {
      int node_a, node_b;
      std::cin >> node_a >> node_b;
      partners[node_a].insert(node_b);
      partners[node_b].insert(node_a);
    }
    int start;
    std::cin >> start;
    bfs(partners, start, n_nodes);
  }
}
