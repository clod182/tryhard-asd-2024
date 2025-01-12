#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
// <>

/* TESTO ESERCIZIO 2

Data una griglia di monete n x m, dove ogni cella contiene un certo numero di monete, 
trova il massimo numero di monete che si possono raccogliere partendo dall'angolo in alto a 
inistra della griglia e spostandosi solo verso destra o verso il basso fino all'angolo in basso a destra.

Dare una caratterizzazione ricorsiva della soluzione;
tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo top-down che risolve il problema;
valutare la complessità dell’algoritmo.
Il prototipo della funzione è:

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------------------------------------------------ RICORSIVO "puro"
int massimaRaccoltaMoneteRicorsiva(vector<vector<int>>& arr, int i, int j) {
    // Caso base: se siamo fuori dalla griglia, ritorniamo 0
    if (i >= arr.size() || j >= arr[0].size()) {
        return 0;
    }

    // Se siamo nell'angolo in basso a destra, ritorniamo il valore della cella
    if (i == arr.size() - 1 && j == arr[0].size() - 1) {
        return arr[i][j];
    }

    // Altrimenti, calcoliamo il massimo tra muoversi a destra o verso il basso
    int moveRight = massimaRaccoltaMoneteRicorsiva(arr, i, j + 1);
    int moveDown = massimaRaccoltaMoneteRicorsiva(arr, i + 1, j);

    // Aggiungiamo il valore della cella corrente
    return arr[i][j] + max(moveRight, moveDown);
}

//------------------------------------------------------------------ TOP-DOWN RICORSIVO
// Funzione ricorsiva con memoizzazione
int massimaRaccoltaMoneteTopDownHelper(vector<vector<int>>& arr, vector<vector<int>>& dp, int i, int j) {
    // Caso base: se siamo fuori dalla griglia, ritorniamo 0
    if (i >= arr.size() || j >= arr[0].size()) {
        return 0;
    }

    // Se abbiamo già calcolato il valore per questa cella, lo restituiamo
    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    // Se siamo nell'angolo in basso a destra, ritorniamo il valore della cella
    if (i == arr.size() - 1 && j == arr[0].size() - 1) {
        return arr[i][j];
    }

    // Calcoliamo il massimo tra muoversi a destra o verso il basso
    int moveRight = massimaRaccoltaMoneteTopDownHelper(arr, dp, i, j + 1);
    int moveDown = massimaRaccoltaMoneteTopDownHelper(arr, dp, i + 1, j);

    // Salviamo il risultato nella tabella dp
    dp[i][j] = arr[i][j] + max(moveRight, moveDown);

    return dp[i][j];
}

// Funzione principale per chiamare la funzione ricorsiva con memoizzazione
int massimaRaccoltaMoneteTopDown(vector<vector<int>>& arr) {
    int n = arr.size();
    int m = arr[0].size();
    
    // Inizializziamo la tabella dp con -1 (indica che non è stato ancora calcolato)
    vector<vector<int>> dp(n, vector<int>(m, -1));

    return massimaRaccoltaMoneteTopDownHelper(arr, dp, 0, 0);
}

int main() {
    // Test 1: Griglia di esempio 1
    vector<vector<int>> griglia1 = {
        {5, 3, 2, 1},
        {1, 9, 8, 3},
        {4, 7, 2, 6},
        {1, 3, 4, 10}
    };

    cout << "Test 1 (Griglia 1) - Massima raccolta di monete (ricorsiva): " 
         << massimaRaccoltaMoneteRicorsiva(griglia1, 0, 0) << endl;

    cout << "Test 1 (Griglia 1) - Massima raccolta di monete (top-down): " 
         << massimaRaccoltaMoneteTopDown(griglia1) << endl;


    // Test 2: Griglia di esempio 2
    vector<vector<int>> griglia2 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    cout << "Test 2 (Griglia 2) - Massima raccolta di monete (ricorsiva): " 
         << massimaRaccoltaMoneteRicorsiva(griglia2, 0, 0) << endl;

    cout << "Test 2 (Griglia 2) - Massima raccolta di monete (top-down): " 
         << massimaRaccoltaMoneteTopDown(griglia2) << endl;


    // Test 3: Griglia 1x1 (caso limite)
    vector<vector<int>> griglia3 = {
        {10}
    };

    cout << "Test 3 (Griglia 1x1) - Massima raccolta di monete (ricorsiva): " 
         << massimaRaccoltaMoneteRicorsiva(griglia3, 0, 0) << endl;

    cout << "Test 3 (Griglia 1x1) - Massima raccolta di monete (top-down): " 
         << massimaRaccoltaMoneteTopDown(griglia3) << endl;

    // Test 4: Griglia vuota (caso limite)
    vector<vector<int>> griglia4 = {};

    if (griglia4.empty() || griglia4[0].empty()) {
        cout << "Test 4 (Griglia vuota) - Impossibile calcolare la raccolta di monete, griglia vuota!" << endl;
    } else {
        cout << "Test 4 (Griglia vuota) - Massima raccolta di monete (ricorsiva): " 
             << massimaRaccoltaMoneteRicorsiva(griglia4, 0, 0) << endl;

        cout << "Test 4 (Griglia vuota) - Massima raccolta di monete (top-down): " 
             << massimaRaccoltaMoneteTopDown(griglia4) << endl;
    }

    return 0;
}