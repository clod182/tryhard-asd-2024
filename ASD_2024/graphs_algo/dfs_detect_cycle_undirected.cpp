#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;

bool checkCycle(int starting_node, int parent, const std::vector<std::vector<int>>& adjList, int visited[]) {  
    
    visited[starting_node] = 1;
    for(int i = 0; i < adjList[starting_node].size(); i++) {
        int vis_node = adjList[starting_node][i];
        if(visited[vis_node] == 1 && vis_node != parent) {
            return true;
        }
        if (visited[vis_node] == 0) {
            if (checkCycle(vis_node, starting_node, adjList, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

//this second function is needed for detecting a cycle when we have CONNECTED COMPONENTS
bool hasCycle(int size, const std::vector<std::vector<int>>& adjList) {
    int visited[size] = {0};

    for(int i = 0; i < size; i++) {
        if(!visited[i]) {
            bool res = checkCycle(i, -1, adjList, visited);
            if(res) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    // Sample graph (modify as needed)
    int numVertices = 5;
    std::vector<std::vector<int>> adjList(numVertices);

    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 3}, {0, 3}};

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Add reverse edge for undirected graph
    }

    // Call the cycle detection function
    if (hasCycle(numVertices, adjList)) {
        std::cout << "DFS The graph CONTAINS a cycle.\n";
    } else {
        std::cout << "DFS The graph does NOT CONTAIN a cycle.\n";
    }

    return 0;
}