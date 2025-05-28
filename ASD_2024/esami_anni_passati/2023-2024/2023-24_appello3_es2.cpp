#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <unordered_map>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO3
Sia A un vettore di n interi e si consideri il problema di determinare se esistono due interi che occorrono in A lo
stesso numero di volte.

a. Si scriva un algoritmo efficiente per il problema proposto.

b. Si scriva un algoritmo efficiente per il problema proposto nel caso in cui in A occorrono c valori
distinti, dove c è una costante intera positiva.

c. Si determini e giustifichi la complessità degli algoritmi proposti.
Si devono scrivere eventuali funzioni/procedure ausiliarie utilizzate.
*/

/*#region utilities functions*/


/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// --- Parte (a): algoritmo generale ---
// Restituisce true se esistono almeno due interi con la stessa frequenza
bool hasEqualFrequencies(const vector<int>& A) {
    int size = A.size();
    if(size <= 1) return false;

    unordered_map<int, int> map;
    for(int i=0; i<size; i++){
        map[A[i]] += 1;
    }

    return false;
}

// --- Parte (b): algoritmo ottimizzato per c costante (pochi valori distinti) ---
// Restituisce true se esistono almeno due valori distinti con la stessa frequenza
bool hasEqualFrequenciesConstC(const vector<int>& A) {
    // TO DO: completa l'implementazione
    return false;
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

int main() {
    // Test case 1: stesso numero ripetuto → false
    vector<int> test1 = {5, 5, 5, 5};
    assert(hasEqualFrequencies(test1) == false);
    assert(hasEqualFrequenciesConstC(test1) == false);

    // Test case 2: frequenze uniche → false
    vector<int> test2 = {1, 2, 2, 3, 3, 3};
    assert(hasEqualFrequencies(test2) == false);
    assert(hasEqualFrequenciesConstC(test2) == false);

    // Test case 3: due valori con stessa frequenza → true
    vector<int> test3 = {1, 1, 2, 2, 3, 4};
    assert(hasEqualFrequencies(test3) == true);
    assert(hasEqualFrequenciesConstC(test3) == true);

    // Test case 4: tanti valori distinti ma due frequenze uguali → true
    vector<int> test4 = {1, 2, 2, 3, 3, 4, 4, 5};
    assert(hasEqualFrequencies(test4) == true);
    assert(hasEqualFrequenciesConstC(test4) == true);

    // Test case 5: c è costante (3 valori distinti), frequenze tutte diverse → false
    vector<int> test5 = {10, 10, 10, 20, 20, 30};
    assert(hasEqualFrequencies(test5) == false);
    assert(hasEqualFrequenciesConstC(test5) == false);

    cout << "Tutti i test passati correttamente!" << endl;
    return 0;
}