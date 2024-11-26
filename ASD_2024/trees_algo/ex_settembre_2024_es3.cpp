#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>

using namespace std;
/*
    Sia A un vettore di n interi e si consideri il problema di determinare se esistono due interi che occorrono in A lo
    stesso numero di volte.
        a. Si scriva un algoritmo efficiente per il problema proposto.

        b. Si scriva un algoritmo efficiente per il problema proposto nel caso in cui in A occorrono c valori
        distinti, dove c è una costante intera positiva.

        c. Si determini e giustifichi la complessità degli algoritmi proposti.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

// Main function 
//  A)============================================================
bool hasDuplicateFrequencies(const vector<int>& A) {
    unordered_map<int, int> frequencyMap;

    // Calcolo delle frequenze degli elementi in A
    for (int num : A) {
        frequencyMap[num]++;
    }

    // Creazione di un array contenente tutte le frequenze
    vector<int> frequencies;
    for (const auto& pair : frequencyMap) {
        frequencies.push_back(pair.second);
    }

    // Ordinamento dell'array delle frequenze
    sort(frequencies.begin(), frequencies.end());

    // Verifica di frequenze duplicate
    for (size_t i = 1; i < frequencies.size(); ++i) {
        if (frequencies[i] == frequencies[i - 1]) {
            return true; // Frequenze duplicate trovate
        }
    }

    return false; // Nessuna frequenza duplicata
}
//Per il punto A la complessità temporale è quindi ==> n*O(log n)

//  A)============================================================ OTTIMIZZATO
bool check_occorrenze_A(vector<int>& A) {

    // Mappa delle occorrenze
    std::unordered_map<int, int> occorrenze;
    
    for(int i=0; i<A.size(); i++){
        occorrenze[A[i]] ++; 
    }

    // Set per memorizzare le frequenze, il set ci permette 
    //di cercare se un'occorenza è già presente in O(n)
    unordered_set<int> frequencies;

    // Controlla se ci sono duplicati di frequenze
    for (const auto& entry : occorrenze) {
        int freq = entry.second;

        // Se la frequenza è già nel set, c'è un duplicato
        if (frequencies.count(freq)) {
            return true;
        }

        // Aggiungi la frequenza al set
        frequencies.insert(freq);
    }

    return false;
}
//Per il punto A la complessità temporale è quindi ==> O(n)

//  B)============================================================
bool check_occorrenze_B(vector<int>& A, int c) {

    map<int, int> frequencyMap;

    // Conta le occorrenze
    for (int num : A) {
        frequencyMap[num]++;
    }

    // Vettore per memorizzare le frequenze già viste
    vector<bool> seenFrequencies(c + 1, false);

    // Controlla duplicati tra le frequenze
    for (const auto& entry : frequencyMap) {
        int freq = entry.second;
        if (seenFrequencies[freq]) {
            return true; // Frequenza duplicata trovata
        }
        seenFrequencies[freq] = true;
    }

    return false; // Nessun duplicato trovato
}
//Per il punto B la complessità temporale è O(n+c) quindi ==> O(n)

int main() {
    // Test 1: Caso con duplicati di frequenze
    vector<int> test1 = {1, 2, 2, 3, 3};
    cout << "Test 1 (true): " << (check_occorrenze_A(test1) ? "true" : "false") << endl;

    // Test 2: Caso senza duplicati di frequenze
    vector<int> test2 = {1, 2, 2, 3, 3, 3};
    cout << "Test 2 (false): " << (check_occorrenze_A(test2) ? "true" : "false") << endl;

    // Test 3: Vettore vuoto
    vector<int> test3 = {};
    cout << "Test 3 (false): " << (check_occorrenze_A(test3) ? "true" : "false") << endl;

    // Test 4: Caso con un solo elemento ripetuto
    vector<int> test4 = {5, 5, 5, 5};
    cout << "Test 4 (false): " << (check_occorrenze_A(test4) ? "true" : "false") << endl;

    // Test 5: Caso con elementi distinti
    vector<int> test5 = {10, 20, 30, 40};
    cout << "Test 5 (false): " << (check_occorrenze_A(test5) ? "true" : "false") << endl;

    // Test 6: Caso con numeri negativi
    vector<int> test6 = {-1, -1, -2, -2, -3, -3};
    cout << "Test 6 (true): " << (check_occorrenze_A(test6) ? "true" : "false") << endl;

        // Test 1: Caso con duplicati di frequenze
    vector<int> test10 = {1, 2, 2, 3, 3};
    cout << "Test FUNB 1 (true): " << (check_occorrenze_B(test10, 3) ? "true" : "false") << endl;

    // Test 2: Caso senza duplicati di frequenze
    vector<int> test20 = {1, 2, 2, 3, 3, 3};
    cout << "Test FUNB 2 (false): " << (check_occorrenze_B(test20, 3) ? "true" : "false") << endl;

    // Test 3: Vettore vuoto
    vector<int> test30 = {};
    cout << "Test FUNB 3 (false): " << (check_occorrenze_B(test30, 0) ? "true" : "false") << endl;

    // Test 4: Caso con un solo elemento ripetuto
    vector<int> test40 = {5, 5, 5, 5};
    cout << "Test FUNB 4 (false): " << (check_occorrenze_B(test40, 1) ? "true" : "false") << endl;

    // Test 5: Caso con elementi distinti
    vector<int> test50 = {10, 20, 30, 40};
    cout << "Test FUNB 5 (false): " << (check_occorrenze_B(test50, 4) ? "true" : "false") << endl;

    // Test 6: Caso con numeri negativi
    vector<int> test60 = {-1, -1, -2, -2, -3, -3};
    cout << "Test FUNB 6 (true): " << (check_occorrenze_B(test60, 3) ? "true" : "false") << endl;

    return 0;
}