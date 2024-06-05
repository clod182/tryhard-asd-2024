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

bool checkCycle(int starting_node, const std::vector<std::vector<int>>& adjList, int visited[]) {  

    queue<pair<int, int>> q;    
    //node, parent
    q.push({starting_node, -1});
    visited[starting_node] = 1;

    while(!q.empty()) { 
        int node = q.front().first;
        int parent = q.front().second;

        q.pop();
        //visited[node] = 1;
        for(int i = 0; i < adjList[node].size(); i++) {
            int node_vis = adjList[node][i];
            if(visited[node_vis]==1 && node_vis != parent) {
                return true;
            }
            if(visited[node_vis] == 0) {                
                q.push({node_vis, node});
                visited[node_vis] = 1;
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
            bool res = checkCycle(i, adjList, visited);
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

    vector<pair<int, int>> edges = {{0, 1}, {0, 2}, {2, 3}, {3, 0}};

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Add reverse edge for undirected graph
    }

    // Call the cycle detection function
    if (hasCycle(numVertices, adjList)) {
        std::cout << "The graph CONTAINS a cycle.\n";
    } else {
        std::cout << "The graph does NOT CONTAIN a cycle.\n";
    }

    return 0;
}