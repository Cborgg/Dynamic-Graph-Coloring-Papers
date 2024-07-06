#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

class DynamicGraph {
private:
    int n; // number of vertices
    std::set<std::pair<int, int>> degree_set; // (degree, vertex) pairs
    std::unordered_map<int, std::unordered_map<int, bool>> adj; // adjacency list
    std::vector<int> vertex_degree; // Quick lookup for vertex degrees

    void update_vertex(int v, int delta) {
        int old_degree = vertex_degree[v];
        int new_degree = old_degree + delta;
        
        if (old_degree > 0) degree_set.erase({old_degree, v});
        if (new_degree > 0) degree_set.insert({new_degree, v});
        vertex_degree[v] = new_degree;
    }

public:
    DynamicGraph(int num_vertices) : n(num_vertices), vertex_degree(num_vertices, 0) {}

    void add_edge(int u, int v) {
        if (u == v || adj[u][v]) return; // self-loop or edge already exists

        adj[u][v] = adj[v][u] = true;
        update_vertex(u, 1);
        update_vertex(v, 1);
    }

    void remove_edge(int u, int v) {
        if (!adj[u][v]) return; // edge doesn't exist

        adj[u].erase(v);
        adj[v].erase(u);
        update_vertex(u, -1);
        update_vertex(v, -1);
    }

    int get_max_degree() {
        return degree_set.empty() ? 0 : degree_set.rbegin()->first;
    }

    void print_graph() {
        for (int i = 0; i < n; i++) {
            std::cout << "Vertex " << i << " (degree " << vertex_degree[i] << "): ";
            for (const auto& neighbor : adj[i]) {
                std::cout << neighbor.first << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Maximum degree: " << get_max_degree() << std::endl;
    }
};

int main() {
    DynamicGraph graph(5);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);

    std::cout << "Initial graph:" << std::endl;
    graph.print_graph();

    graph.remove_edge(1, 2);
    std::cout << "\nAfter removing edge (1, 2):" << std::endl;
    graph.print_graph();

    graph.add_edge(0, 3);
    graph.add_edge(0, 4);
    std::cout << "\nAfter adding edges (0, 3) and (0, 4):" << std::endl;
    graph.print_graph();

    return 0;
}
