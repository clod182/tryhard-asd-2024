#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <unordered_map>
#include <algorithm>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO4
Dato un vettore A di n numeri naturali, scrivere una procedura efficiente che ordini A in modo tale
che nel vettore risultante, dati i e j con 1 <= i <= j<=n, vale mod(A[i], 3) <= mod(A[j], 3), dove
mod(x, 3) è il resto della divisione di x per 3.

a. Dire se la soluzione proposta è in loco e se è stabile.
b. Valutare e giustificare la complessità della procedura proposta.

/*#region utilities functions*/

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
void ordina_mod3(vector<int>& A) {
    int n = A.size();
    vector<int> B(n);  // spazio temporaneo

    int index = 0;

    // Copia tutti quelli con mod 0
    for (int i = 0; i < n; ++i) {
        if (A[i] % 3 == 0) {
            B[index++] = A[i];
        }
    }

    // Copia tutti quelli con mod 1
    for (int i = 0; i < n; ++i) {
        if (A[i] % 3 == 1) {
            B[index++] = A[i];
        }
    }

    // Copia tutti quelli con mod 2
    for (int i = 0; i < n; ++i) {
        if (A[i] % 3 == 2) {
            B[index++] = A[i];
        }
    }

    // Riscrivi il contenuto ordinato in A
    for (int i = 0; i < n; ++i) {
        A[i] = B[i];
    }
}

//modo alternativo -----------------------------------------------------
void ordina_mod3ALT(vector<int>& A) {
    int n = A.size();
    if (n <= 1) return;
    
    // Contiamo gli elementi per ogni resto (0, 1, 2)
    int count[3] = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        count[A[i] % 3]++;
    }
    
    // Calcoliamo le posizioni di partenza per ogni gruppo
    int pos[3];
    pos[0] = 0;                    // elementi con resto 0 iniziano da posizione 0
    pos[1] = count[0];             // elementi con resto 1 iniziano dopo quelli con resto 0
    pos[2] = count[0] + count[1];  // elementi con resto 2 iniziano dopo 0 e 1
    
    // Creiamo un vettore ausiliario per il risultato
    vector<int> result(n);
    
    // Distribuiamo gli elementi nel vettore risultato
    for (int i = 0; i < n; i++) {
        int resto = A[i] % 3;
        result[pos[resto]] = A[i];
        pos[resto]++;
    }
    
    // Copiamo il risultato nel vettore originale
    A = result;
}


//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
// Stampa un vettore
void printVector(const vector<int>& A) {
    for (int x : A) cout << x << " ";
    cout << endl;
}

int main() {
    // Test 1: Vettore misto con tutti i residui
    vector<int> A1 = {4, 7, 3, 6, 1, 9, 2};
    cout << "Test 1 - Prima: ";
    printVector(A1);
    ordina_mod3(A1);
    cout << "Test 1 - Dopo:  ";
    printVector(A1);

    // Test 2: Tutti elementi con mod 3 = 0
    vector<int> A2 = {3, 6, 0, 9, 12};
    cout << "Test 2 - Prima: ";
    printVector(A2);
    ordina_mod3(A2);
    cout << "Test 2 - Dopo:  ";
    printVector(A2);

    // Test 3: Tutti elementi con mod 3 = 1
    vector<int> A3 = {1, 4, 7, 10};
    cout << "Test 3 - Prima: ";
    printVector(A3);
    ordina_mod3(A3);
    cout << "Test 3 - Dopo:  ";
    printVector(A3);

    // Test 4: Tutti elementi con mod 3 = 2
    vector<int> A4 = {2, 5, 8, 11};
    cout << "Test 4 - Prima: ";
    printVector(A4);
    ordina_mod3(A4);
    cout << "Test 4 - Dopo:  ";
    printVector(A4);

    // Test 5: Elementi già ordinati per mod 3
    vector<int> A5 = {3, 6, 1, 4, 2, 5};
    cout << "Test 5 - Prima: ";
    printVector(A5);
    ordina_mod3(A5);
    cout << "Test 5 - Dopo:  ";
    printVector(A5);

    // Test 6: Ordinati in ordine inverso
    vector<int> A6 = {2, 5, 8, 1, 4, 7, 3, 6, 9};
    cout << "Test 6 - Prima: ";
    printVector(A6);
    ordina_mod3(A6);
    cout << "Test 6 - Dopo:  ";
    printVector(A6);

    // Test 7: Duplicati
    vector<int> A7 = {3, 3, 4, 4, 2, 2};
    cout << "Test 7 - Prima: ";
    printVector(A7);
    ordina_mod3(A7);
    cout << "Test 7 - Dopo:  ";
    printVector(A7);

    // Test 8: Vuoto
    vector<int> A8 = {};
    cout << "Test 8 - Prima: ";
    printVector(A8);
    ordina_mod3(A8);
    cout << "Test 8 - Dopo:  ";
    printVector(A8);

    // Test 9: Singolo elemento
    vector<int> A9 = {7};
    cout << "Test 9 - Prima: ";
    printVector(A9);
    ordina_mod3(A9);
    cout << "Test 9 - Dopo:  ";
    printVector(A9);

    // Test 10: Grande vettore casuale
    vector<int> A10;
    for (int i = 0; i < 100; ++i) A10.push_back(rand() % 100);
    cout << "Test 10 - Prima: ";
    printVector(A10);
    ordina_mod3(A10);
    cout << "Test 10 - Dopo:  ";
    printVector(A10);

    return 0;
}