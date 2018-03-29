#include <bits/stdc++.h>

using namespace std;

template <typename T>
struct Disjoint_set
{    
    Disjoint_set(const std::vector<T>& nodes)
    {
        for (const auto& node : nodes)
        {
            // All elements start as single nodes
            m_parents[node] = node;
        }
    }
    
    T find_root(const T& node)
    {
        const auto parent = m_parents[node];
        if (node == parent)
        {
            return node;
        }
        else
        {
            return find_root(parent);
        }
    }
    
    void make_union(const T& node_one, const T& node_two)
    {
        m_parents[find_root(node_one)] = find_root(node_two);
    }
    private:
    std::unordered_map<T, T> m_parents;
};

struct Connection
{
    int start;
    int end;
    int weight;
};

int main()
{
    int g_nodes;
    int g_edges;

    cin >> g_nodes >> g_edges;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Connection> connections(g_edges);
    std::vector<int> nodes(g_nodes);
    
    std::iota (std::begin(nodes), std::end(nodes), 1);

    for (int i = 0; i < g_edges; i++) {
        cin >> connections[i].start >> connections[i].end >> connections[i].weight;
    }

    Disjoint_set<int> disjoint_Set(nodes);
    
    std::sort(connections.begin(), connections.end(), [](const Connection& lhs, const Connection& rhs)
                { return lhs.weight < rhs.weight; });
    
    int sum = 0;
    for (const auto& connection : connections)
    {
        std::cerr << connection.start << " " << connection.end << " " << connection.weight << '\n';
        if (disjoint_Set.find_root(connection.start) != disjoint_Set.find_root(connection.end))
        {
            std::cerr << "Roots differ" << disjoint_Set.find_root(connection.start)
                      << " "            << disjoint_Set.find_root(connection.end) << '\n';
            disjoint_Set.make_union(connection.start, connection.end);
            sum += connection.weight;
            std::cerr << "Connecting - " << connection.start << " " << connection.end << " " << connection.weight << '\n';
        }
    }

    std::cout << sum;
    return 0;
}
