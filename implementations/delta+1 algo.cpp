/*#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// Function to check if the current coloring is valid
bool isValidColoring(const vector<vector<int>>& graph, const vector<int>& color) {
    int V = graph.size();
    for (int u = 0; u < V; ++u) {
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && color[u] == color[v]) {
                return false;
            }
        }
    }
    return true;
}

// Recursive function to try all possible colorings
bool graphColoringUtil(const vector<vector<int>>& graph, int m, vector<int>& color, int v) {
    int V = graph.size();
    if (v == V) {
        return isValidColoring(graph, color);
    }

    for (int c = 1; c <= m; ++c) {
        color[v] = c;
        if (graphColoringUtil(graph, m, color, v + 1)) {
            return true;
        }
        color[v] = 0; // Backtrack
    }
    return false;
}

// Function to solve the graph coloring problem
bool graphColoring(const vector<vector<int>>& graph, int& m, vector<int>& color) {
    int V = graph.size();
    while (!graphColoringUtil(graph, m, color, 0)) {
        ++m;
    }
    return true;
}

int main() {
    // Example graph represented as a vector of pairs of edges
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {0, 3}, {1, 3},{2,5},{2,6},{3,7},{4,8},{5,9},{6,7},{7,8},{8,9},{8,3}
    };
    int V = 10; // Number of vertices

    // Create adjacency matrix
    vector<vector<int>> graph(V, vector<int>(V, 0));
    for (auto edge : edges) {
        graph[edge.first][edge.second] = 1;
        graph[edge.second][edge.first] = 1;
    }

    vector<int> color(V, 0);
    int m = 1; // Start with 1 color

    // Measure the start time
    auto start = high_resolution_clock::now();

    // Perform the graph coloring
    graphColoring(graph, m, color);

    //adding edge (1,4)
    graph[1][4]=1;
    graph[4][1]=1;

    graphColoring(graph, m, color);
    // Measure the end time
    auto end = high_resolution_clock::now();

    // Calculate the duration

    cout << "A valid coloring exists with " << m << " colors. The colors of the nodes are:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Node " << i << " -> Color " << color[i] << endl;
    }

    cout<<isValidColoring(graph,color)<<endl;
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <limits.h>
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;
using namespace std::chrono;

class Graph {
private:
    int n; // number of vertices
    std::vector<std::set<int>> adj; // adjacency list
    std::vector<int> colors; // colors of vertices

    int getAvailableColor(int v) {
        std::vector<bool> used(n + 1, false);
        for (int u : adj[v]) {
            used[colors[u]] = true;
        }
        for (int c = 1; c <= n; c++) {
            if (!used[c]) return c;
        }
        return -1; // This should never happen in Delta + 1 coloring
    }

public:
    Graph(int vertices) : n(vertices), adj(vertices), colors(vertices, 0) {}

    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
        
        // Recolor if necessary
        if (colors[u] == colors[v]) {
            colors[v] = getAvailableColor(v);
        }
    }

    void removeEdge(int u, int v) {
        adj[u].erase(v);
        adj[v].erase(u);
    }

    int getColor(int v) {
        return colors[v];
    }

    void printColoring() {
        for (int i = 0; i < n; i++) {
            std::cout << "Vertex " << i << ": Color " << colors[i] << std::endl;
        }
    }
};

int main() {
    // Read the data from the file
    auto start = high_resolution_clock::now();
    std::ifstream file("C:/Users/gauta/OneDrive/Desktop/haggle.undo.0.25.seq");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    // Assuming first line is metadata
    std::getline(file, line);
    int V;
    std::istringstream metadata(line.substr(1)); // skip the '#' character
    metadata >> V; // Read number of nodes

    Graph g(V);

    while (std::getline(file, line)) {
        if (line[0] == '#') continue; // Skip comment lines

        std::istringstream iss(line);
        int type, u, v;
        if (iss >> type >> u >> v) {
            if (type == 1) {
                g.addEdge(u, v);
            } else if (type == 0) {
                g.removeEdge(u, v);
            }
        }
    }

    file.close();

    std::cout << "Final coloring:" << std::endl;
    g.printColoring();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}

