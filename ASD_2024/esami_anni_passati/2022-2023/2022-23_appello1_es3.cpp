#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <iostream>
#include <queue>
#include <limits>
using namespace std;
// <>

/* TESTO ESERCIZIO3 APPELLO1
Il diametro di un grafo pesato è definito come la massima distanza tra due vertici del grafo, dove, come è noto, per “distanza tra due vertici” u e v si intende la lunghezza del cammino minimo tra u e v. 
Si sviluppi un algoritmo  efficiente (ovvero polinomiale) che accetti in ingresso un grafo G e ne calcoli il suo diametro (si assuma che G non contenga cicli negativi). 
Si dimostri la correttezza dell’algoritmo proposto e si determini la sua complessità computazionale.

Nota. Nel caso in cui si faccia uso di algoritmi noti si dimostri anche la loro correttezza.

*/

/*#region utilities functions*/
const int INF = numeric_limits<int>::max();

// Struttura per rappresentare un arco (vicino, peso)
typedef pair<int, int> Edge;

// Funzione Dijkstra: calcola le distanze minime da sorgente a tutti i nodi
vector<int> dijkstra(int start, const vector<vector<Edge>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INF);
    dist[start] = 0;

    // Min-heap: (distanza, nodo)
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        // Se la distanza attuale è maggiore di quella salvata, scarto
        if (d > dist[u]) continue;

        // Controllo tutti i vicini
        for (const auto& [v, weight] : adj[u]) {
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }

    return dist;
}
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// O(n(n+m)log n)
int graphDiameter(const vector<vector<Edge>>& adj) {
    int n = adj.size();      // Numero di nodi nel grafo
    int diameter = 0;        // Variabile per tracciare la massima distanza trovata

    // Esegui Dijkstra da ogni nodo del grafo
    for (int u = 0; u < n; ++u) {
        // Calcola le distanze minime da u a tutti gli altri nodi
        vector<int> dist = dijkstra(u, adj);

        // Scorri tutte le distanze ottenute da u
        for (int v = 0; v < n; ++v) {
            if (dist[v] != INF) { // Se v è raggiungibile da u
                // Aggiorna il diametro se troviamo una distanza più grande
                diameter = max(diameter, dist[v]);
            }
            // Se dist[v] == INF, significa che v non è raggiungibile da u → il grafo non è connesso.
            // In questo caso, il diametro tecnicamente è infinito (oppure si potrebbe segnalare con -1).
        }
    }

    // Alla fine del doppio ciclo, 'diameter' contiene la massima distanza minima tra due nodi qualsiasi.
    return diameter;
}


//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

int main() {
    int n = 5; // numero di nodi
    vector<vector<Edge>> adj(n);

    // Aggiungiamo archi (es. grafo non orientato)
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[2].push_back({3, 4});
    adj[3].push_back({2, 4});

    adj[3].push_back({4, 1});
    adj[4].push_back({3, 1});

    int diam = graphDiameter(adj);
    cout << "Diametro del grafo: " << diam << endl;

    return 0;
}