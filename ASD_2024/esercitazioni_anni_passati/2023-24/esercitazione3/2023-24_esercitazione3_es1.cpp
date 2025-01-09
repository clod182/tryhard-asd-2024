#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
// <>

/* TESTO ESERCIZIO 1
Scrivere una funzione EFFICIENTE order che ordini in modo decrescente n numeri interi compresi nell'intervallo da 0 a n^4 - 1 nel tempo O(n).
Il prototipo della procedura è:
 
void order(vector<int>& arr)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
/*#region utilities functions*/

/*#endregion utilities functions*/

// Funzione per eseguire un Counting Sort su una cifra specifica
void countingSortByDigit(std::vector<int>& arr, int n, int exp) {
    std::vector<int> output(n);
    std::vector<int> count(10, 0);  // Per contare le occorrenze delle cifre (0-9)

    // Conta le occorrenze delle cifre nell'array
    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
    }

    // Modifica il count[] per contenere le posizioni finali di ogni cifra
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Costruisce l'array ordinato basato sulla cifra corrente
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copia l'array ordinato in arr[]
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Funzione per eseguire Radix Sort
void radixSort(std::vector<int>& arr) {
    int n = arr.size();
    int maxVal = *max_element(arr.begin(), arr.end());  // Trova il massimo valore nell'array

    /* Esegui il Counting Sort per ogni cifra (unità, decine, centinaia, ...)    
    -Ordina in base alla cifra delle unità (più a destra).
    -Poi ordina in base alla cifra delle decine.
    -Successivamente ordina in base alla cifra delle centinaia.
    -Infine ordina in base alla cifra dei migliaia.
    */
    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        countingSortByDigit(arr, n, exp);
    }
}

void order(std::vector<int>& arr) {
    // Ordina l'array usando Radix Sort (non crescente)
    radixSort(arr);

    // Poiché Radix Sort ordina in modo crescente, basta invertire l'array per ottenere l'ordinamento non crescente
    std::reverse(arr.begin(), arr.end());
}
int main() {
    // Array di test
    vector<int> arr = {81, 16, 1, 256, 0, 1296, 625, 4096, 2401};

    // Stampa dell'array originale
    cout << "Array originale: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Chiamata alla funzione di ordinamento
    order(arr);

    // Stampa dell'array ordinato
    cout << "Array ordinato (non crescente): ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}