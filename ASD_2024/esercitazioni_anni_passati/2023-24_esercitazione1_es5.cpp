#include <iostream>
#include <vector>
using namespace std;
// <>

/* TESTO
Esercizio 5
Dato un albero binario, scrivere una funzione che costruisce un array bidimensionale mat tale che, 
per ogni coppia di nodi u e v, l’elemento mat[u][v] sia il minimo antenato comune di u e v. 
La funzione deve richiedere tempo O(n^2) e il suo prototipo è:

void minAntCom(PNode r, vector<vector<int>>& mat)
Per semplicità si assuma che i nodi abbiano chiavi numerate da 0 a n-1 e che queste chiavi identifichino il nodo. 
Di conseguenza gli indici della matrice rappresentano i nodi e in posizione mat[u][v] c'è la chiave del nodo 
che è il minimo antenato comune di u e v.

[Il minimo antenato comune di due nodi u e v è  l’antenato comune  di u e v che si trova più lontano dalla radice dell’albero.]
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/


/*#endregion utilities functions*/

// Funzione da implementare
int PesoMinimo(vector<int> pesi_1, vector<int> pesi_2) {
    // Implementazione richiesta qui
    return 0;
}

int main() {
    // Esempio 1
    vector<int> pesi_1 = {5, 1, 3}; // Pesi della prima rastrelliera
    vector<int> pesi_2 = {4, 2, 6}; // Pesi della seconda rastrelliera
    
    cout << "Peso minimo da sollevare: " << PesoMinimo(pesi_1, pesi_2) << endl;
    
    // Esempio 2
    vector<int> pesi_1_2 = {10, 1, 3, 7}; // Pesi della prima rastrelliera
    vector<int> pesi_2_2 = {5, 8, 6, 4}; // Pesi della seconda rastrelliera
    
    cout << "Peso minimo da sollevare: " << PesoMinimo(pesi_1_2, pesi_2_2) << endl;

    return 0;
}
