#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 1
Sia A un array di lunghezza n − k con k ≥ 2, privo di ripetizioni e contenente interi nell’intervallo [n∗n+1, n∗n+n]. 
Si consideri il problema di determinare i k numeri interi appartenenti all’intervallo [n∗n+1, n∗n+n] che non compaiono in A.
Si scriva una funzione efficiente che, dati A, n e k, 
risolva il problema proposto restituendo un vettore che contiene gli interi che non compaiono in A.

Il prototipo della procedura è:
vector<int> trovaMancanti(const vector<int>& arr, int n, int k)

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
vector<int> trovaMancanti(const vector<int>& arr, int n, int k) {
    vector<int> mancanti;

    int dim = arr.size();
    int inizio = n * n + 1;
    vector<int> occorrenze(n, 0);

    for(int i=0; i<dim; i++){
      
       occorrenze[arr[i] - inizio] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (occorrenze[i] == 0) {
            mancanti.push_back(inizio + i);
        }
    }

    return mancanti;
}


void stampaVettore(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    cout << boolalpha;

    // Test 1: intervallo 101..110, A contiene 8 numeri -> mancano 2
    vector<int> test1 = {101, 102, 103, 104, 105, 106, 107, 108};
    int n1 = 10, k1 = 2;
    cout << "Test1: ";
    stampaVettore(trovaMancanti(test1, n1, k1));
    cout << endl;

    // Test 2: mancano i primi k dell'intervallo
    vector<int> test2 = {103, 104, 105, 106, 107, 108, 109, 110}; // mancano 101 e 102
    int n2 = 10, k2 = 2;
    cout << "Test2: ";
    stampaVettore(trovaMancanti(test2, n2, k2));
    cout << endl;

    // Test 3: array vuoto, mancano tutti
    vector<int> test3 = {};
    int n3 = 4, k3 = 4;
    cout << "Test3: ";
    stampaVettore(trovaMancanti(test3, n3, k3));
    cout << endl;

    // Test 4: manca uno in mezzo, uno alla fine
    vector<int> test4 = {101, 102, 103, 105, 106, 107, 108, 109};
    int n4 = 10, k4 = 2;
    cout << "Test4: ";
    stampaVettore(trovaMancanti(test4, n4, k4));
    cout << endl;

    return 0;
}
