#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
#include <unordered_map>
#include <algorithm>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO3
Sia A un array di n numeri naturali. Si consideri il problema di stampare in ordine crescente tutti i numeri che
compaiono in A almeno ⌈n/k⌉ volte, dove k > 0 è una costante.

Si scriva una procedura efficiente che, dati A, n e k, risolva il problema proposto.
Valutare e giustificare la complessità dell’algoritmo proposto.
Si devono scrivere le eventuali funzioni/procedure ausiliarie utilizzate.

/*#region utilities functions*/
// Funzione ausiliaria per il merge
void merge(vector<int>& arr, int left, int mid, int right) {
    // Calcola le dimensioni dei due sottoarray
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crea array temporanei
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    
    // Copia i dati negli array temporanei
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    // Merge dei due array temporanei nell'array originale
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copia gli elementi rimanenti di leftArr, se ce ne sono
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copia gli elementi rimanenti di rightArr, se ce ne sono
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Funzione ricorsiva per il mergesort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Trova il punto medio per dividere l'array in due metà
        int mid = left + (right - left) / 2;
        
        // Ordina ricorsivamente la prima e la seconda metà
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge delle due metà ordinate
        merge(arr, left, mid, right);
    }
}
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
//O(n log n)
void printFrequentElements(const vector<int>& A, int k){
    if(A.empty() || k <= 0) return;

    int n = A.size();
    int threshold = (n + k - 1) / k; // ceil(n/k)

    vector<int> sorted = A;
    mergeSort(sorted, 0, n - 1);

    int current = sorted[0];
    int count = 1;

    for(int i = 1; i < n; i++){
        if(sorted[i] == current){
            count++;
        } else {
            if(count >= threshold){
                cout << current << ", ";
            }
            current = sorted[i];
            count = 1;
        }
    }

    // Gestione dell'ultimo gruppo
    if (count >= threshold) {
        cout << current << ", ";
    }

}

//Versione ottimizzata O(n) 
//SOLO SE POTESSIMO USARE FUNZIONI DI LIBRERIE COME SORT
/*void printFrequentElementsHashMap(const vector<int>& A, int k) {
    if (A.empty() || k <= 0) return;
    
    int n = A.size();
    int threshold = (n + k - 1) / k; // ceil(n/k)
    
    // Conta le frequenze
    unordered_map<int, int> freq;
    for (int x : A) {
        freq[x]++;
    }
    
    // Raccogli elementi frequenti
    vector<int> frequent;
    for (const auto& pair : freq) {
        if (pair.second >= threshold) {
            frequent.push_back(pair.first);
        }
    }
    
    // Ordina solo gli elementi frequenti
    sort(frequent.begin(), frequent.end());
    
    // Stampa risultato
    for (size_t i = 0; i < frequent.size(); i++) {
        if (i > 0) cout << ", ";
        cout << frequent[i];
    }
    if (!frequent.empty()) cout << endl;
}*/

//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
int main() {
    vector<vector<int>> testVectors = {
        {1, 2, 3, 2, 1, 2, 3, 3, 3, 4},     // frequenze: 1(2), 2(3), 3(4), 4(1)
        {5, 5, 5, 5, 5},                   // tutto uguale
        {1, 2, 3, 4, 5, 6, 7},             // tutti distinti
        {7, 7, 8, 8, 8, 9, 9, 9, 9},       // varie frequenze
        {},                                // caso vuoto
        {1, 1, 2, 2, 3, 3, 3}              // con ripetuti ma nessuno molto frequente
    };

    vector<int> ks = {3, 2, 1, 4, 1, 3}; // valori di k corrispondenti ai vettori sopra

    for (size_t i = 0; i < testVectors.size(); ++i) {
        cout << "Test case " << i+1 << ": A = [ ";
        for (int val : testVectors[i]) cout << val << " ";
        cout << "], k = " << ks[i] << endl;

        cout << "Output: ";
        printFrequentElements(testVectors[i], ks[i]);
        cout << "\n---------------------\n";
    }

    return 0;
}