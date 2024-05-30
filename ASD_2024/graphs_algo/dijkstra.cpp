#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

/* #region utility function */

void printDistances(const vector<int>& distances) {
    for (int i = 0; i < distances.size(); ++i) {
        if (distances[i] == INT_MAX) {
            cout << "INF ";
        } else {
            cout << distances[i] << " ";
        }
    }
    cout << endl;
}

/* #endregion utility function */

//find the shortest distance of all vertices from Starting node S
vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(V);
    
    for(int i=0; i<dist.size(); i++){        
        dist[i] = INT_MAX;              
    }
    dist[S] = 0;
    pq.push({0, S});

    while(pq.size() > 0){
        int node = pq.top().second;
        int weight = pq.top().first;
        pq.pop();    
        for(int i=0; i<adj[node].size(); i++){
            int cur_node = adj[node][i][0];
            int cur_weight = adj[node][i][1];
            if(weight+cur_weight < dist[cur_node]){
                dist[cur_node] = weight+cur_weight;
                pq.push({dist[cur_node], cur_node});
            }
        }        
    }

    return dist;
}



int main() {
    // Example 1: Simple graph
    int V1 = 5;
    vector<vector<int>> adj1[5];
    adj1[0].push_back({1, 9});
    adj1[0].push_back({2, 6});
    adj1[0].push_back({3, 5});
    adj1[0].push_back({4, 3});
    adj1[2].push_back({1, 2});
    adj1[2].push_back({3, 4});

    cout << "Example 1: Simple graph" << endl;    
    vector<int> distances1 = dijkstra(V1, adj1, 0);
    printDistances(distances1);

    // Example 2: Disconnected graph
    int V2 = 4;
    vector<vector<int>> adj2[4];
    adj2[0].push_back({1, 1});
    adj2[1].push_back({2, 2});

    cout << "Example 2: Disconnected graph" << endl;    
    vector<int> distances2 = dijkstra(V2, adj2, 0);
    printDistances(distances2);

    // Example 3: More complex graph
    int V3 = 6;
    vector<vector<int>> adj3[6];
    adj3[0].push_back({1, 1});
    adj3[0].push_back({2, 4});
    adj3[1].push_back({2, 2});
    adj3[1].push_back({3, 6});
    adj3[2].push_back({3, 3});
    adj3[3].push_back({4, 1});
    adj3[4].push_back({5, 2});
    adj3[2].push_back({5, 5});

    cout << "Example 3: More complex graph" << endl;    
    vector<int> distances3 = dijkstra(V3, adj3, 0);
    printDistances(distances3);

    return 0;
}