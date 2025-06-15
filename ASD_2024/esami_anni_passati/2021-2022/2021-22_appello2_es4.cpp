#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <limits>
#include <iomanip>

using namespace std;
// <>

/* TESTO ESERCIZIO4 APPELLO2
Sia G = (V, E) un grafo orientato con funzione peso w : E --> R e vertici numerati da 1 a n, cioè V = {1, 2, ... , n}, e
sia k una costante intera con k £ n. Si scriva un algoritmo che, per ogni coppia di vertici i, j Î V, determini la lunghezza
del cammino minimo tra i e j i cui vertici intermedi non superino k. Si dimostri la correttezza dell’algoritmo proposto
e si determini la sua complessità (in funzione di n). Si assuma che i pesi sugli archi siano positivi e che quindi G non
contenga cicli negativi.
*/

/*#region utilities functions*/
const double INF = numeric_limits<double>::infinity();

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
void shortestPathsUpToK(int n, int k, const vector<vector<double>>& w, vector<vector<double>>& dist) {
    dist = w; // dist[i][j] inizializza con i pesi sugli archi

    for (int intermediate = 1; intermediate <= k; ++intermediate) { // DIFF CON ALGO STANDARD DI F.W., LIMITO A <= K
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][intermediate] != INF && dist[intermediate][j] != INF &&
                    dist[i][intermediate] + dist[intermediate][j] < dist[i][j]) {
                    dist[i][j] = dist[i][intermediate] + dist[intermediate][j];
                }
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN

void printMatrix(const vector<vector<double>>& mat, int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (mat[i][j] == INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << mat[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int n = 4;
    vector<vector<double>> w(n + 1, vector<double>(n + 1, INF));

    // Inizializzazione: diagonale a 0
    for (int i = 1; i <= n; ++i) {
        w[i][i] = 0;
    }

    // Aggiungiamo archi diretti
    w[1][2] = 3;
    w[1][3] = 10;
    w[2][3] = 1;
    w[2][4] = 2;
    w[3][4] = 4;

    cout << "Matrice dei pesi iniziale:" << endl;
    printMatrix(w, n);

    for (int k = 1; k <= n; ++k) {
        vector<vector<double>> dist;
        shortestPathsUpToK(n, k, w, dist);
        cout << "Distanze minime con vertici intermedi ≤ " << k << ":" << endl;
        printMatrix(dist, n);
    }

    return 0;
}