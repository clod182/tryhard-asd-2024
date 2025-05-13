#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 3
Scrivere una funzione che, ricevuto in input un intero k (1 ≤ k ≤ n) e un array v, NON ordinato, di n elementi distinti, 
restituisce il k−esimo elemento più piccolo di v. 

Trovare una soluzione di costo in tempo:
1. Θ(n log n) avente prototipo:
int cercaK esimoPrimaSol(vector<int>& arr, int k);

2. O(n + k log n) avente prototipo:
int cercaK esimoSecondaSol(vector<int>& arr, int k);

3. O(n log k) avente prototipo:
int cercaK esimoTerzaSol(vector<int>& arr, int k).

Dimostrare che la complessità delle funzioni è quella richiesta.
Se k è costante quale delle soluzioni in ordine di grandezza è la migliore?
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
// Θ(n log n)
int cercaKesimoPrimaSol(vector<int>& arr, int k){

}

// O(n + k log n)
int cercaKesimoSecondaSol(vector<int>& arr, int k){
  return -1;
}

// O(n log k)
int cercaKesimoTerzaSol(vector<int>& arr, int k){
  return -1;
}


// Funzione di utilità per stampare vettori
void stampaVettore(const vector<int>& v) {
    for (int x : v)
        cout << x << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    vector<int> v1 = {12, 3, 5, 7, 4, 19, 26};
    int k = 3;

    cout << "Vettore di partenza: ";
    stampaVettore(v1);
    cout << "k = " << k << endl;

    vector<int> copia1 = v1;
    vector<int> copia2 = v1;
    vector<int> copia3 = v1;

    int sol1 = cercaKesimoPrimaSol(copia1, k);
    int sol2 = cercaKesimoSecondaSol(copia2, k);
    int sol3 = cercaKesimoTerzaSol(copia3, k);

    cout << "[Soluzione 1 - n log n]       Risultato: " << sol1 << endl;
    cout << "[Soluzione 2 - n + k log n]   Risultato: " << sol2 << endl;
    cout << "[Soluzione 3 - n log k]       Risultato: " << sol3 << endl;

    return 0;
}

