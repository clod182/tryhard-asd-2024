#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO1
Sia arr un vettore di interi di dimensione n. 
Si assuma che nel vettore arr siano stati inseriti numeri interi
positivi provenienti da un albero binario di ricerca completo T. 
In particolare, gli elementi di T sono stati inseriti in arr usando la stessa convenzione 
che si usa normalmente per la memorizzazione di uno heap in un vettore.

a) Scrivere una funzione efficiente int maxBST(vector<int>& arr) che restituisce il massimo
di arr.

b) Siano arr1 ed arr2 due vettori che memorizzano due alberi binari di ricerca completi T1 e T2
aventi ciascuno n elementi, con le convenzioni sopra fissate. Sia k una chiave intera tale che tutte le
chiavi di T1 sono minori di k e tutte le chiavi di T2 sono maggiori di k. Sia arr un vettore di dimensione
2n + 1. Si vuole memorizzare in arr l’albero binario di ricerca completo T che si otterrebbe dalla
fusione di T1, k, e T2. Scrivere una funzione efficiente che restituisce arr. La funzione ha il seguente
prototipo:
vector<int> mergeBST(vector<int>& arr1, vector<int>& arr2, int val)

c) Determinare e giustificare la complessità delle funzioni maxBST e mergeBST.
*/

/*#region utilities functions*/
// Prototipi delle funzioni
int maxBST(vector<int>& arr);
vector<int> mergeBST(vector<int>& arr1, vector<int>& arr2, int val);
/*#endregion utilities functions*/

//--------------------------------------------------------------------  (A)
/*
Grazie alla rappresentazione dell'albero binario di ricerca completo come vettore, l'accesso all'elemento più grande 
(che si trova nell'ultimo indice dell'array) è immediato e in tempo costante O(1).
*/
int maxBST(vector<int>& arr){
    // Caso base: se il vettore arr è vuoto, ritorna -infinity
    if (arr.empty()) {
        return INT_MIN;
    }

    return arr[arr.size()-1];
}

//--------------------------------------------------------------------  (B)

vector<int> mergeBST(vector<int>& arr1, vector<int>& arr2, int val) {
    int n1 = arr1.size();
    int n2 = arr2.size();
    int totalSize = n1 + n2 + 1; // Dimensione totale del nuovo array (arr1 + val + arr2)

    vector<int> ret(totalSize); // Vettore risultato

    // Inserisci il valore k (val) come radice
    ret[0] = val;

    // Copia arr1 come sottoalbero sinistro
    for (int i = 0; i < n1; ++i) {
        ret[1 + i] = arr1[i];
    }

    // Copia arr2 come sottoalbero destro
    for (int i = 0; i < n2; ++i) {
        ret[1 + n1 + i] = arr2[i];
    }

    return ret;
}

int main() {
    // Test 1: Albero binario di ricerca completo memorizzato come heap
    vector<int> bst1 = {1, 2, 3, 4, 5, 6, 7}; // Rappresenta un BST completo
    cout << "Test 1 - Massimo valore nel BST: " << maxBST(bst1) << endl;

    // Test 2: Un altro albero binario di ricerca completo
    vector<int> bst2 = {8, 9, 10, 11, 12, 13, 14}; // Rappresenta un altro BST completo
    cout << "Test 2 - Massimo valore nel BST: " << maxBST(bst2) << endl;

    // Test 3: Merge di due alberi binari di ricerca
    int k = 7; // Valore della chiave intermedia
    vector<int> mergedBST = mergeBST(bst1, bst2, k);
    cout << "Test 3 - BST unito: ";
    for (int val : mergedBST) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}