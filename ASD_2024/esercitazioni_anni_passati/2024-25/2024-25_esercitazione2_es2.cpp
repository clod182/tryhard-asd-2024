#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 2
Sia arr un vettore di interi di dimensione n. 
Si assuma che nel vettore arr siano stati inseriti numeri interi positivi provenienti da un albero binario di ricerca completo T. 
In particolare, gli elementi di T sono stati inseriti in arr usando la stessa convenzione che si usa normalmente per la 
memorizzazione di uno heap in un vettore.

1)Scrivere una procedura void
void stampa((const vector<int>& arr)

2)Scrivere una funzione efficiente
int maxBST(const vector<int>& arr)
che restituisce il massimo di arr.

3)Scrivere una funzione efficiente
int minBST(const vector<int>& arr)
che restituisce il minimo di arr.

4)Siano arr1 ed arr2 due vettori che memorizzano due alberi binari di ricerca completi T1 e T2 aventi ciascuno n elementi, 
con le convenzioni sopra fissate. Sia k una chiave intera tale che tutte le chiavi di T1 sono minori di k e tutte le chiavi di T2 sono maggiori di k. 
Si vuole costruire l’albero binario di ricerca completo T che si otterrebbe dalla fusione di T1, k, e T2. 
Scrivere una funzione efficiente che restituisce l'array che memorizza T. La funzione ha il seguente prototipo:
vector mergeBST(vector<int>& arr1, vector<int>& arr2, int val)

5)Determinare e giustificare la complessità delle funzioni
stampa, maxBST, minBST e mergeBST.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
// 1) Stampa in forma strutturata l'albero rappresentato dal vettore
//    Es: livello per livello con indentazione
//in sostanza è una stampa in order
void stampaAux(const vector<int>& arr, int i){
    if(i >= arr.size()) return;
    stampaAux(arr, 2 * i + 1);  // sinistro
    cout << arr[i] << " ";          // radice
    stampaAux(arr, 2 * i + 2);  // destro
}

void stampa(const vector<int>& arr){
    int i=0;
    stampaAux(arr, i);
}

// 2) Restituisce il massimo elemento di arr in modo efficiente
template<typename T>
int maxBST(const vector<T>& arr){
    int dim = arr.size();
    int i=0;
    while(i*2+2 < dim){
        i = i*2+2;
    }
    return arr[i];
}

// 3) Restituisce il minimo elemento di arr in modo efficiente
template<typename T>
int minBST(const vector<T>& arr){
    int dim = arr.size();
    int i=0;
    while(i*2+1 < dim){
        i = i*2+1;
    }
    return arr[i];
}

// 4) Fusione di due BST completi arr1, arr2 con tutti i valori di arr1 < k < arr2
//    Restituisce il vettore che rappresenta il BST completo ottenuto
vector<int> mergeBST(const vector<int>& arr1, const vector<int>& arr2, int k){
    if(arr1.size() <= 0 && arr2.size() <= 0 ) return arr1;
    if(arr1.size() <= 0) return arr2;
    if(arr2.size() <= 0) return arr1;

    
}

// Funzioni di utilità per creare esempi
vector<int> buildSampleBST1() {
    // BST completo:
    //       15
    //     /    \
    //   10      20
    //  /  \    /  \
    // 8   12  17   25
    return {15, 10, 20, 8, 12, 17, 25};
}

vector<int> buildSampleBST2() {
    // BST completo:
    //       5
    //     /   \
    //    3     7
    //   / \   / \
    //  2  4  6   8
    return {5, 3, 7, 2, 4, 6, 8};
}

int main() {
    // Preparazione dati
    vector<int> arr = buildSampleBST1();
    vector<int> arr1 = buildSampleBST1();
    vector<int> arr2 = buildSampleBST2();
    int k = 13; // chiave di separazione

    // 1) Test stampa
    cout << "=== Test Stampa ===" << endl;
    stampa(arr);

    // 2) Test maxBST
    cout << "\n=== Test Max ===" << endl;
    cout << "Massimo: " << maxBST(arr) << endl;

    // 3) Test minBST
    cout << "\n=== Test Min ===" << endl;
    cout << "Minimo: " << minBST(arr) << endl;

    // 4) Test mergeBST
    cout << "\n=== Test Merge ===" << endl;
    vector<int> merged = mergeBST(arr1, arr2, k);
    stampa(merged);

    return 0;
}