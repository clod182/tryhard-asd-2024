#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;
// <>

/* TESTO ESERCIZIO3 APPELLO1
La rete ferroviaria italiana può essere descritta mediante un grafo orientato pesato G = (V, E, w), dove
i vertici rappresentato le stazioni, la presenza di un arco tra due vertici indica l’esistenza di una tratta
ferroviaria diretta tra le corrispondenti stazioni e, per ogni arco (u,v) ∈ E, il peso w(u,v) rappresenta
la quantità di carburante necessaria per raggiungere la stazione v partendo da u. Si scriva un algoritmo
che, dati in ingresso il grafo G, la quantità C di carburante inizialmente presente nel serbatoio della
locomotiva di un treno, e due nodi s e d, restituisca TRUE se esiste un cammino che consente al treno
di raggiungere la stazione d partendo dalla stazione s, e FALSE in caso contrario.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// Funzione che verifica se è possibile arrivare a 'd' da 's' con massimo 'C' carburante
bool canReachWithFuel(int n, const vector<vector<pair<int, int>>>& adj, int s, int d, int C) {
    vector<int> dist(n, INT_MAX);
    dist[s] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [fuel_used, u] = pq.top(); pq.pop();

        if (u == d && fuel_used <= C) return true; // DIFFERNZA CON DJIKSTRA NORMALE
        if (fuel_used > C) continue; // DIFFERNZA CON DJIKSTRA NORMALE

        for (auto [v, cost] : adj[u]) {
            int new_cost = fuel_used + cost;
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                pq.push({new_cost, v});
            }
        }
    }

    return false;
}
//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN

void addEdge(vector<vector<pair<int, int>>>& adj, int u, int v, int w) {
    adj[u].push_back({v, w});
}

int main() {
    const int n = 5; // Numero di stazioni
    vector<vector<pair<int, int>>> adj(n);

    // Costruzione della rete ferroviaria
    addEdge(adj, 0, 1, 4);
    addEdge(adj, 1, 2, 3);
    addEdge(adj, 0, 3, 10);
    addEdge(adj, 3, 4, 1);
    addEdge(adj, 2, 4, 2);

    // Test case 1: percorso esiste con carburante sufficiente
    cout << "Test 1 (0 → 2, C=7): " << (canReachWithFuel(n, adj, 0, 2, 7) ? "TRUE" : "FALSE") << endl;

    // Test case 2: percorso esiste ma carburante insufficiente
    cout << "Test 2 (0 → 2, C=6): " << (canReachWithFuel(n, adj, 0, 2, 6) ? "TRUE" : "FALSE") << endl;

    // Test case 3: percorso lungo ma valido
    cout << "Test 3 (0 → 4, C=9): " << (canReachWithFuel(n, adj, 0, 4, 9) ? "TRUE" : "FALSE") << endl;

    // Test case 4: percorso diretto troppo costoso
    cout << "Test 4 (0 → 3, C=9): " << (canReachWithFuel(n, adj, 0, 3, 9) ? "TRUE" : "FALSE") << endl;

    // Test case 5: nodo isolato (nessun arco entrante o uscente)
    cout << "Test 5 (4 → 0, C=100): " << (canReachWithFuel(n, adj, 4, 0, 100) ? "TRUE" : "FALSE") << endl;

    // Test case 6: costo esattamente uguale al carburante disponibile
    cout << "Test 6 (0 → 2, C=7): " << (canReachWithFuel(n, adj, 0, 2, 7) ? "TRUE" : "FALSE") << endl;

    return 0;
}