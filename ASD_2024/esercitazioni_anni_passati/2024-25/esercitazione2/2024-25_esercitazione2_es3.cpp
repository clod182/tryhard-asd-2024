#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 3
Questa settimana Carlotta ha ricevuto del denaro dai suoi genitori e vuole spenderlo tutto acquistando libri. ù
Per finire un libro Carlotta impiega una settimana e poiché riceve denaro ogni due settimane, ha deciso di acquistare due libri, 
così potrà leggerli fino a quando riceverà altri soldi. 
Desidera spendere tutti i soldi così vorrebbe scegliere due libri i cui prezzi sommati sono pari ai soldi che ha ricevuto.

Data la quantità di soldi che Carlotta ha a disposizione e un array contenente i prezzi dei libri (tutti distinti), 
restituire le coppie di prezzi di libri che soddisfano la condizione. 
Le coppie di prezzi devono contenere prima il prezzo più basso e poi quello più alto.

Scrivere una funzione efficiente il cui prototipo è il seguente:
int libriSelezionati(vector<int>& prezzolibri, double soldi, vector<pair<int,int>>& ris)
La funzione restituisce la dimensione dell’array ris. Si devono scrivere eventuali funzioni/procedure ausiliari utilizzate.
*/

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
//========================================================================
// APPROCCIO 1: O(n log n) - ORDINAMENTO + DUE PUNTATORI
//========================================================================

int libriSelezionati(vector<int>& prezzolibri, double soldi, vector<pair<int, int>>& ris) {
    if (prezzolibri.size() < 2) return 0;
    
    // Crea una copia per l'ordinamento (per preservare l'array originale)
    vector<int> prezzi_ordinati = prezzolibri;
    
    // Ordinamento con mergesort implementato manualmente
    mergeSort(prezzi_ordinati, 0, prezzi_ordinati.size() - 1);
    
    int left = 0;
    int right = prezzi_ordinati.size() - 1;
    int count = 0;
    int target = (int)soldi; // Assumiamo che i soldi siano interi per semplicità
    
    while (left < right) {
        int somma = prezzi_ordinati[left] + prezzi_ordinati[right];
        
        if (somma == target) {
            // Trovata una coppia valida
            ris[count] = {prezzi_ordinati[left], prezzi_ordinati[right]};
            count++;
            left++;
            right--;
        }
        else if (somma < target) {
            // Somma troppo piccola, aumenta il puntatore sinistro
            left++;
        }
        else {
            // Somma troppo grande, diminuisci il puntatore destro
            right--;
        }
    }
    
    return count;
}

int main() {
    // Test 1: caso base, c'è una coppia valida
    vector<int> prezzi1 = {10, 15, 20, 5, 25};
    double soldi1 = 30;
    vector<pair<int, int>> ris1;
    int count1 = libriSelezionati(prezzi1, soldi1, ris1);
    cout << "Test 1: Coppie trovate = " << count1 << "\n";
    for (auto& p : ris1) cout << "(" << p.first << ", " << p.second << ")\n";

    // Test 2: più coppie possibili
    vector<int> prezzi2 = {8, 12, 17, 13, 22, 5};
    double soldi2 = 25;
    vector<pair<int, int>> ris2;
    int count2 = libriSelezionati(prezzi2, soldi2, ris2);
    cout << "\nTest 2: Coppie trovate = " << count2 << "\n";
    for (auto& p : ris2) cout << "(" << p.first << ", " << p.second << ")\n";

    // Test 3: nessuna coppia valida
    vector<int> prezzi3 = {1, 2, 3, 4};
    double soldi3 = 100;
    vector<pair<int, int>> ris3;
    int count3 = libriSelezionati(prezzi3, soldi3, ris3);
    cout << "\nTest 3: Coppie trovate = " << count3 << "\n";

    // Test 4: array vuoto
    vector<int> prezzi4 = {};
    double soldi4 = 50;
    vector<pair<int, int>> ris4;
    int count4 = libriSelezionati(prezzi4, soldi4, ris4);
    cout << "\nTest 4: Coppie trovate = " << count4 << "\n";

    // Test 5: array con un solo elemento
    vector<int> prezzi5 = {50};
    double soldi5 = 100;
    vector<pair<int, int>> ris5;
    int count5 = libriSelezionati(prezzi5, soldi5, ris5);
    cout << "\nTest 5: Coppie trovate = " << count5 << "\n";

    return 0;
}