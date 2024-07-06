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
public:
    Graph(int vertices);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    void recolorGraph();
    void displayColors();
    void displayGraph();

private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<int> colors;

    void recolorVertex(int u);
    int smallestUnassignedColor(int u);
};

Graph::Graph(int vertices) : V(vertices), adj(vertices), colors(vertices, -1) {}

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
    if (colors[u] == colors[v]) {
        int toRecolor = (adj[u].size() < adj[v].size()) ? u : v;
        recolorVertex(toRecolor);
    }
}

void Graph::removeEdge(int u, int v) {
    adj[u].erase(std::remove(adj[u].begin(), adj[u].end(), v), adj[u].end());
    adj[v].erase(std::remove(adj[v].begin(), adj[v].end(), u), adj[v].end());
    recolorVertex(u);
    recolorVertex(v);
}

void Graph::recolorGraph() {
    for (int u = 0; u < V; ++u) {
        recolorVertex(u);
    }
}

void Graph::recolorVertex(int u) {
    // Step 1: Calculate the saturation colors of u's neighbors
    std::set<int> neighborColors;
    for (int neighbor : adj[u]) {
        if (colors[neighbor] != -1) {
            neighborColors.insert(colors[neighbor]);
        }
    }

    // Step 2: Find the smallest unassigned color cmin
    int cmin = 0;
    while (neighborColors.find(cmin) != neighborColors.end()) {
        ++cmin;
    }

    // Step 3: Determine the maximum color in the saturation set
    int cmax = neighborColors.empty() ? -1 : *neighborColors.rbegin();

    // Step 4: Decide which color to assign to vertex u
    if (cmin < cmax) {
        colors[u] = cmin;
    } else {
        // Step 5: Calculate the maximal saturation degree for each color
        std::unordered_map<int, int> mcolor;
        for (int neighbor : adj[u]) {
            int neighborColor = colors[neighbor];
            if (neighborColor != -1) {
                // Calculate the saturation degree for neighborColor
                std::set<int> neighborNeighborColors;
                for (int neighborOfNeighbor : adj[neighbor]) {
                    if (colors[neighborOfNeighbor] != -1 && neighborOfNeighbor != u) {
                        neighborNeighborColors.insert(colors[neighborOfNeighbor]);
                    }
                }
                mcolor[neighborColor] = std::max(mcolor[neighborColor], (int)neighborNeighborColors.size());
            }
        }

        // Step 6: Find the candidate color with the smallest maximal saturation
        int ccand = -1;
        int minSaturation = INT_MAX;
        for (const auto& [color, saturation] : mcolor) {
            if (saturation < minSaturation) {
                minSaturation = saturation;
                ccand = color;
            }
        }

        // Step 7: Assign the best color to u
        if (ccand < cmin - 1) {
            colors[u] = ccand;
            for (int neighbor : adj[u]) {
                if (colors[neighbor] == ccand) {
                    colors[neighbor] = smallestUnassignedColor(neighbor);
                }
            }
        } else {
            colors[u] = cmin;
        }
    }
}

int Graph::smallestUnassignedColor(int u) {
    std::set<int> neighborColors;
    for (int neighbor : adj[u]) {
        if (colors[neighbor] != -1) {
            neighborColors.insert(colors[neighbor]);
        }
    }

    int color = 0;
    while (neighborColors.find(color) != neighborColors.end()) {
        ++color;
    }
    return color;
}

void Graph::displayColors() {
    for (int i = 0; i < V; ++i) {
        std::cout << "Vertex " << i << " ---> Color " << colors[i] << std::endl;
    }
}

void Graph::displayGraph() {
    for (int u = 0; u < V; ++u) {
        std::cout << "Adjacency list of vertex " << u << ":\n head ";
        for (auto x : adj[u]) {
            std::cout << "-> " << x << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    auto start = high_resolution_clock::now();

    // Read the data from the file
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

    Graph graph(V);

    while (std::getline(file, line)) {
        if (line[0] == '#') continue; // Skip comment lines

        std::istringstream iss(line);
        int type, u, v;
        if (iss >> type >> u >> v) {
            if (type == 1) {
                graph.addEdge(u, v);
            } else if (type == 0) {
                graph.removeEdge(u, v);
            }
        }
    }

    file.close();

    graph.recolorGraph();

    std::cout << "\nVertex Colors:\n";
    graph.displayColors();
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " milliseconds" << endl;

    return 0;
}
