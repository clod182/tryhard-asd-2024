#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO ESERCIZIO 5
Sia v[0..n-1] un array di n numeri distinti. Se i < j e v[i] > v[j], allora la coppia (i,j) e' detta inversione di v.
 
Elencare le inversioni dell'array <5,6,11,9,3>
Quale array con elementi estratti dall'insieme {1,2,...,n} ha piu' inversioni? Quante inversioni ha?
Qual e' la realazione fra il tempo di esecuzione di insertion sort e il numero di inversioni nell'array di input? Spiegare la vostra risposta.
Scrivere una funzione che determina il numero di inversioni in un array di n elementi distinti nel tempo Θ(n log n) nel caso peggiore.
Il prototipo della funzione è:

int numinversioni(vector<int>& v)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.

In sintesi, le inversioni sono coppie di indici che violano l'ordinamento crescente
*/
/*#region utilities functions*/

// Funzione per stampare l'array
void stampaArray(const vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}

/*#endregion utilities functions*/

// Funzione di fusione che conta le inversioni
int mergeAndCount(vector<int>& v, vector<int>& temp, int left, int right) {
    if (left == right) return 0;
    
    int mid = (left + right) / 2;
    
    // Conta inversioni nelle due metà
    int invCount = mergeAndCount(v, temp, left, mid);
    invCount += mergeAndCount(v, temp, mid + 1, right);
    
    // Conta inversioni mentre fonde i due sotto-array
    invCount += merge(v, temp, left, mid, right);
    
    return invCount;
}

// Funzione di fusione che effettivamente fonde due metà ordinate e conta le inversioni
int merge(vector<int>& v, vector<int>& temp, int left, int mid, int right) {
    int i = left;    // Indice per la parte sinistra
    int j = mid + 1; // Indice per la parte destra
    int k = left;    // Indice per il vettore temporaneo
    int invCount = 0;
    
    while (i <= mid && j <= right) {
        if (v[i] <= v[j]) {
            temp[k++] = v[i++];
        } else {
            temp[k++] = v[j++];
            invCount += (mid - i + 1); // Tutti gli elementi rimanenti nel lato sinistro sono inversioni
        }
    }
    
    // Copia i rimanenti elementi di sinistra
    while (i <= mid) {
        temp[k++] = v[i++];
    }
    
    // Copia i rimanenti elementi di destra
    while (j <= right) {
        temp[k++] = v[j++];
    }
    
    // Copia gli elementi ordinati nel vettore originale
    for (i = left; i <= right; i++) {
        v[i] = temp[i];
    }
    
    return invCount;
}

// Funzione principale che avvia il merge sort e ritorna il numero totale di inversioni
int numinversioni(vector<int>& v) {
    vector<int> temp(v.size());
    return mergeAndCount(v, temp, 0, v.size() - 1);
}

int main() {
    // Esempio di array di test
    vector<int> v = {5, 6, 11, 9, 3};
    
    // Stampa dell'array originale
    cout << "Array originale: ";
    stampaArray(v);
    
    // Calcolo del numero di inversioni
    int numInversioni = numinversioni(v);
    cout << "Numero di inversioni: " << numInversioni << endl;
    
    return 0;
}