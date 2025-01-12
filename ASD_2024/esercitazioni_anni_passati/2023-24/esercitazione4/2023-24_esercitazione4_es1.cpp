#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
// <>

/* TESTO ESERCIZIO 1

Sia arr un array di lunghezza n di numeri naturali positivi (> 0). 
Si consideri il problema di determinare una sottosequenza crescente di lunghezza massima. 
Ad esempio, dato l'array [10, 22, 9, 33, 21, 50, 41, 60, 80], una sottosequenza crescente di lunghezza massima è 
[10, 22, 33, 50, 60, 80], che ha lunghezza 6.

Definire in modo ricorsivo la lunghezza massima di una sottosequenza crescente;
tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo bottom-up che determina 
la lunghezza massima di una sottosequenza crescente;
trasformare l’algoritmo di modo che determini anche una sottosequenza crescente di lunghezza massima;
valutare le complessità degli algoritmi.

I prototipi delle funzioni sono:
int lunglongestIncreasingSubsequence(vector<int>& arr)
vector<int> longestIncreasingSubsequence(vector<int>& arr)

*/

/*#region utilities functions*/
//firme funzioni
int lunglongestIncreasingSubsequence(vector<int>& arr);
vector<int> longestIncreasingSubsequence(vector<int>& arr);
/*#endregion utilities functions*/

//------------------------------------------------------------------ TOP-DOWN RICORSIVO
// Funzione helper ricorsiva con memoizzazione
int lunglongestIncreasingSubsequenceHelper(vector<int>& arr, vector<int>& dp, int i) {
    // Se il valore è già stato calcolato, restituiscilo
    if (dp[i] != -1) return dp[i];

    // Ogni elemento è almeno una LIS di lunghezza 1
    dp[i] = 1;

    // Calcola LIS considerando tutti gli elementi precedenti
    for (int j = 0; j < i; j++) {
        if (arr[j] < arr[i]) {
            dp[i] = max(dp[i], 1 + lunglongestIncreasingSubsequenceHelper(arr, dp, j));
        }
    }

    return dp[i];
}
// Funzione principale
int lunglongestIncreasingSubsequenceTopDown(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0; // Caso base: array vuoto

    // Inizializza il vettore dp con -1 per indicare che i valori non sono calcolati
    vector<int> dp(n, -1);

    int max_length = 0;
    // Chiama la funzione helper per ogni indice
    for (int i = 0; i < n; i++) {
        max_length = max(max_length, lunglongestIncreasingSubsequenceHelper(arr, dp, i));
    }

    return max_length;
}

//------------------------------------------------------------------ BOTTOM-UP ITERATIVO
int lunglongestIncreasingSubsequence(vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;

    vector<int> dp(n, 1); // Ogni elemento è una LIS di lunghezza 1
    int maxLIS = 1;

    for (int i = 1; i < n; i++) { // Itera su ogni elemento
        for (int j = 0; j < i; j++) { // Controlla tutti gli elementi precedenti
            if (arr[j] < arr[i]) { // Condizione di LIS
                dp[i] = max(dp[i], dp[j] + 1); // Aggiorna la LIS per arr[i]
            }
        }
        maxLIS = max(maxLIS, dp[i]); // Mantieni traccia della LIS massima
    }

    return maxLIS;
}

vector<int> longestIncreasingSubsequence(vector<int>& arr) {
    int n = arr.size();
    vector<int> ret;

    if (n == 0) return ret;

    vector<int> dp(n, 1); // Ogni elemento è una LIS di lunghezza 1
    vector<int> prevIndex(n, -1); // Per tracciare gli indici precedenti
    int maxLIS = 1, endIndex = 0;

    // Calcola dp e traccia gli indici precedenti
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prevIndex[i] = j; // Salva l'indice precedente
            }
        }
        if (dp[i] > maxLIS) {
            maxLIS = dp[i];
            endIndex = i; // Salva l'indice finale della LIS
        }
    }

    // Ricostruisci la LIS usando prevIndex
    while (endIndex != -1) {
        ret.push_back(arr[endIndex]);
        endIndex = prevIndex[endIndex];
    }

    reverse(ret.begin(), ret.end()); // La LIS è costruita in ordine inverso
    return ret;
}



int main() {
    // Test di esempio
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    
    // Testare la lunghezza della LIS
    cout << "Lunghezza della LIS: " << lunglongestIncreasingSubsequence(arr) << endl;

    // Testare la sottosequenza LIS
    
    
    vector<int> lis = longestIncreasingSubsequence(arr);
    cout << "Sottosequenza crescente massima: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}