#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#include <stack>

using namespace std;

void dfs(int v, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited, vector<int>& result) {
    visited[v] = true;
    result.push_back(v);

    for(int i=0; i<adj[v].size(); i++){
        int current = adj[v][i].first;
        if(!visited[current]){
            dfs(current, adj, visited, result);
        }
    }
}

void dfs_iterative(int start, const vector<vector<pair<int, int>>>& adj, vector<bool>& visited, vector<int>& result) {
    stack<int> s;
    s.push(start);

    while(!s.empty()){
        int v = s.top();
        s.pop();

        if (!visited[v]) {
            visited[v] = true;
            result.push_back(v);

            for(int i=0; i<adj[v].size(); i++){
                int current = adj[v][i].first;
                if(!visited[current]){
                    s.push(current);
                }
            }
        }       
    }
}

int main() {
    int n = 10; // number of vertices
    vector<vector<pair<int, int>>> adj(n);

    // Constructing the graph
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 1});
    adj[1].push_back({3, 1});
    adj[1].push_back({4, 1});
    adj[2].push_back({5, 1});
    adj[2].push_back({6, 1});
    adj[3].push_back({7, 1});
    adj[4].push_back({8, 1});
    adj[5].push_back({9, 1});

    vector<bool> visited(n, false);
    vector<int> result;

    // Perform DFS starting from vertex 0
    dfs(0, adj, visited, result);

    // Output the DFS traversal
    cout << "DFS Traversal recursive: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;

    vector<bool> visited2(n, false);
    vector<int> result2;

    dfs_iterative(0, adj, visited2, result2);

    // Output the DFS traversal
    cout << "DFS Traversal iterative: ";
    for (int v : result2) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}