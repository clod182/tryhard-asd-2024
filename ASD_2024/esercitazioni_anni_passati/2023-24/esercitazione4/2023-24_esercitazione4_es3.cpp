#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;
// <>

/* TESTO ESERCIZIO 3

Sia data una sequenza di città c1 c2 ... cn collegate da un percorso ferroviario. 
Da ciascuna città ci è possibile raggiungere cj, con i < j con un treno diretto. 
Sapendo che per i, j ∈ {1, . . . , n}, i < j il costo del biglietto del treno diretto da ci a cj risulta essere b[i,j], 
determinare il costo minimo di un tragitto, con possibili cambi intermedi, da c1 a cn. Più in dettaglio:

-Fornire una caratterizzazione ricorsiva del costo minimo min[i] di un di un tragitto dalla città ci alla città cn;
-tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo bottom-up che determina il costo 
di un tragitto di costo minimo dalla città c1 alla città cn;
-trasformare l’algoritmo di modo che determini anche la sequenza dei cambi necessari per ottenere il tragitto di costo minimo, 
privilegiando – a parità di costo – soluzioni che minimizzano il numero dei cambi;
-valutare le complessità degli algoritmi.

I prototipi delle funzioni sono:
int minTrain(vector<vector<int>>& b, int n)
vector<int> minTrainSequence(vector<vector<int>>& b, int n)

*/

/*#region utilities functions*/
// Dichiarazioni delle funzioni
int minTrain(vector<vector<int>>& b, int n);
vector<int> minTrainSequence(vector<vector<int>>& b, int n);
/*#endregion utilities functions*/

//------------------------------------------------------------------ RICORSIVO "puro"
int minTrainRecursiveHelper(vector<vector<int>>& b, int i, int n) {
    // Caso base: siamo già all'ultima città
    if (i == n - 1) {
        return 0;
    }

    int minCost = INT_MAX;

    // Calcoliamo il costo minimo scegliendo una città successiva cj (j > i)
    for (int j = i + 1; j < n; j++) {
        int cost = b[i][j] + minTrainRecursiveHelper(b, j, n);
        minCost = min(minCost, cost);
    }

    return minCost;
}

int minTrainRecursive(vector<vector<int>>& b, int n) {
    return minTrainRecursiveHelper(b, 0, n);
}

//------------------------------------------------------------------ TOP-DOWN
int minTrainRecursiveHelperTD(vector<vector<int>>& b, int i, int n, vector<int>& dp) {
    // Caso base: siamo già all'ultima città
    if (i == n - 1) {
        return 0; // No cost to reach the last city from itself
    }

    // Se abbiamo già calcolato il costo minimo da questa città, restituiamolo
    if (dp[i] != -1) {
        return dp[i];
    }

    int minCost = INT_MAX;

    // Calcoliamo il costo minimo scegliendo una città successiva cj (j > i)
    for (int j = i + 1; j < n; j++) {
        int cost = b[i][j] + minTrainRecursiveHelperTD(b, j, n, dp);
        minCost = min(minCost, cost);
    }

    // Salviamo il risultato nella tabella dp
    dp[i] = minCost;
    return dp[i];
}

int minTrainRecursiveTD(vector<vector<int>>& b, int n) {
    int size = b[0].size();
    vector<int> dp(n, -1); // Inizializza la tabella dp con -1
    return minTrainRecursiveHelperTD(b, 0, n, dp);
}

//------------------------------------------------------------------ BOTTOM-UP
// Funzione che calcola solo il costo minimo
int minTrain(vector<vector<int>>& b, int n) {
    vector<int> dp(n, INT_MAX); // dp[i]: costo minimo per raggiungere la città n partendo da i

    // Caso base: costo minimo per l'ultima città è 0
    dp[n - 1] = 0;

    // Calcoliamo iterativamente il costo minimo per ogni città
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (b[i][j] != INT_MAX) { // Controlliamo se c'è una connessione diretta
                dp[i] = min(dp[i], b[i][j] + dp[j]);
            }
        }
    }

    return dp[0]; // Restituiamo il costo minimo dalla città 1 (indice 0)
}

// Funzione che calcola il percorso ottimale
vector<int> minTrainSequence(vector<vector<int>>& b, int n) {
    vector<int> dp(n, INT_MAX); // dp[i]: costo minimo per raggiungere la città n partendo da i
    vector<int> nextCity(n, -1); // nextCity[i]: città successiva nel percorso ottimale

    // Caso base: costo minimo per l'ultima città è 0
    dp[n - 1] = 0;

    // Calcoliamo iterativamente il costo minimo e tracciamo il percorso
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (b[i][j] != INT_MAX) { // Controlliamo se c'è una connessione diretta
                int cost = b[i][j] + dp[j];
                if (cost < dp[i]) {
                    dp[i] = cost;
                    nextCity[i] = j; // Aggiorniamo la città successiva
                }
            }
        }
    }

    // Ricostruzione del percorso ottimale
    vector<int> path;
    int currentCity = 0; // Partiamo dalla prima città (indice 0)
    while (currentCity != -1) {
        path.push_back(currentCity + 1); // Aggiungiamo alla lista, convertito a base 1
        currentCity = nextCity[currentCity]; // Passiamo alla città successiva nel percorso
    }

    return path;
}


int main() {
    // Test 1: Matrice dei costi semplice
    vector<vector<int>> b1 = {
        {0, 10, 15, 30},
        {INT_MAX, 0, 35, 25},
        {INT_MAX, INT_MAX, 0, 20},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int n1 = b1.size();
    cout << "Test 1 - Costo minimo del tragitto: " << minTrain(b1, n1) << endl;

    vector<int> seq1 = minTrainSequence(b1, n1);
    cout << "Test 1 - Sequenza dei cambi: ";
    for (int city : seq1) {
        cout << city << " ";
    }
    cout << endl;

    // Test 2: Matrice con costi alti
    vector<vector<int>> b2 = {
        {0, 100, 300, 600},
        {INT_MAX, 0, 200, 400},
        {INT_MAX, INT_MAX, 0, 100},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int n2 = b2.size();
    cout << "Test 2 - Costo minimo del tragitto: " << minTrain(b2, n2) << endl;

    vector<int> seq2 = minTrainSequence(b2, n2);
    cout << "Test 2 - Sequenza dei cambi: ";
    for (int city : seq2) {
        cout << city << " ";
    }
    cout << endl;

    // Test 3: Solo due città
    vector<vector<int>> b3 = {
        {0, 50},
        {INT_MAX, 0}
    };
    int n3 = b3.size();
    cout << "Test 3 - Costo minimo del tragitto: " << minTrain(b3, n3) << endl;

    vector<int> seq3 = minTrainSequence(b3, n3);
    cout << "Test 3 - Sequenza dei cambi: ";
    for (int city : seq3) {
        cout << city << " ";
    }
    cout << endl;

    // Test 4: Matrice con più opzioni di costo minimo
    vector<vector<int>> b4 = {
        {0, 10, 20, 50},
        {INT_MAX, 0, 15, 30},
        {INT_MAX, INT_MAX, 0, 10},
        {INT_MAX, INT_MAX, INT_MAX, 0}
    };
    int n4 = b4.size();
    cout << "Test 4 - Costo minimo del tragitto: " << minTrain(b4, n4) << endl;

    vector<int> seq4 = minTrainSequence(b4, n4);
    cout << "Test 4 - Sequenza dei cambi: ";
    for (int city : seq4) {
        cout << city << " ";
    }
    cout << endl;

    return 0;
}