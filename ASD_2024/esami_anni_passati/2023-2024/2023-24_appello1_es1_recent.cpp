#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

/* TESTO ESERCIZIO1  APPELLO1 2023-2024

Sia arr un vettore di interi di dimensione n. Si assuma che nel vettore arr siano stati inseriti numeri interi
positivi provenienti da un albero binario di ricerca completo T. In particolare, gli elementi di T sono stati
inseriti in arr usando la stessa convenzione che si usa normalmente per la memorizzazione di uno heap in un
vettore.

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

/*#endregion utilities functions*/

// ---------------------------------------------------------------------   Funzione richiesta all'esame
// --------------------------------------------------------------------- PUNTO A
int maxBST_ricHelper(vector<int>& arr, int dim, int i){
    if(i >= dim) return INT_MIN;

    int left = i*2+1;
    int right = i*2+2;
    if(right >= dim) return arr[i];

    return maxBST_ricHelper(arr, dim, right);
       
}
int maxBST_ric(vector<int>& arr){
    int dim = arr.size();
    return maxBST_ricHelper(arr, dim, 0);
}
int maxBST_SMART(vector<int>& arr){ //VERSIONE SMART ottimizzata sulla consegna dell'es --> BST COMPLETO, elemento più grande in ultima posizione array
    return arr[arr.size()-1];
}

// --------------------------------------------------------------------- PUNTO B
// ------------------------------------------------------------ SOLUZIONE NON SEMPRE EFFICACE
vector<int> mergeBST(vector<int>& arr1, vector<int>& arr2, int val){
    int dim = arr1.size(); // i 2 array hanno stessa dimensione    

    vector<int> ret;

    ret.push_back(val); // k è la nuova radice

    int sx = 0; // indice per scorrere arr1
    int dx = 0; // indice per scorrere arr2
    int elementsPerLevel = 1; // *2 ad ogni livello
    while(sx < dim){
        int endLine = sx+elementsPerLevel;
        while(sx < endLine){
            ret.push_back(arr1[sx]);
            sx++; 
        }

        while(dx < endLine){
            ret.push_back(arr2[dx]);
            dx++; 
        }

        elementsPerLevel*=2;
    }

    return ret;
}
// ------------------------------------------------------------ SOLUZIONE SEMPRE EFFICACE
/*
 * 1) Inorder traversal di un BST memorizzato come vettore heap-style.
 *    Popola 'result' con gli elementi in ordine crescente.
 */
void inorderFromArray(const vector<int>& arr, int idx, vector<int>& result) {
    if (idx >= (int)arr.size()) 
        return;
    // Visito il sottoalbero sinistro
    inorderFromArray(arr, 2*idx + 1, result);
    // Visito il nodo corrente
    result.push_back(arr[idx]);
    // Visito il sottoalbero destro
    inorderFromArray(arr, 2*idx + 2, result);
}

/*
 * 2) Costruzione ricorsiva di un BST COMPLETO (heap-style) a partire da un vettore ordinato.
 *
 *   sorted:    vettore ordinato [l..r]
 *   tree:      vettore di destinazione già inizializzato a size = totale nodi
 *   pos:       posizione corrente in 'tree' (indice heap)
 */
void buildCompleteBST(const vector<int>& sorted, int l, int r, vector<int>& tree, int pos) {
    if (l > r || pos >= (int)tree.size()) 
        return;
    
    // Scegliamo l'elemento di mezzo del sottoarray per garantire
    // che i livelli superiori siano riempiti completamente
    int mid = l + (r - l)/2;
    tree[pos] = sorted[mid];
    
    // Ricorsione per i figli
    buildCompleteBST(sorted, l, mid-1, tree, 2*pos + 1);  // figlio sinistro
    buildCompleteBST(sorted, mid+1, r, tree, 2*pos + 2);  // figlio destro
}

/*
 * 3) Funzione mergeBST:
 *    - Prende due vettori arr1, arr2 (ognuno rappresenta un BST completo di n nodi, tutti valori < val per arr1 e > val per arr2)
 *    - Val: chiave di mezzo da inserire come radice
 *    - Restituisce un vettore di lunghezza 2n+1 che rappresenta il BST completo fuso.
 */
vector<int> mergeBST(const vector<int>& arr1, const vector<int>& arr2, int val) {
    int n = arr1.size();
    // 3.1) Estrazione inorder dei due alberi
    vector<int> inorder1, inorder2;
    inorderFromArray(arr1, 0, inorder1);
    inorderFromArray(arr2, 0, inorder2);
    
    // 3.2) Fusione in un unico vettore ordinato
    vector<int> merged;
    merged.reserve(2*n + 1);
    merged.insert(merged.end(), inorder1.begin(), inorder1.end());
    merged.push_back(val);
    merged.insert(merged.end(), inorder2.begin(), inorder2.end());
    
    // 3.3) Costruzione del BST completo heap-style
    vector<int> result(2*n + 1, 0);
    buildCompleteBST(merged, 0, 2*n, result, 0);
    return result;
}

// Main di test
int main() {
    // Test 1: semplice
    vector<int> bst1 = {8, 4, 12, 2, 6, 10, 14}; // BST completo
    cout << "Massimo in bst1 maxBST_ric: " << maxBST_ric(bst1) << endl;
    cout << "Massimo in bst1 maxBST_SMART: " << maxBST_SMART(bst1) << endl;

    vector<int> arr1 = {2, 1, 3};
    vector<int> arr2 = {7, 6, 8};
    int k = 5;

    vector<int> merged = mergeBST(arr1, arr2, k);
    cout << "Albero fuso (test 1): ";
    for (int x : merged) cout << x << " ";
    cout << endl;

    // Test 2: più grande
    vector<int> bigArr1 = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15}; // BST con 15 nodi
    vector<int> bigArr2 = {24, 20, 28, 18, 22, 26, 30, 17, 19, 21, 23, 25, 27, 29, 31}; // altro BST
    int midVal = 16;

    vector<int> bigMerged = mergeBST(bigArr1, bigArr2, midVal);
    cout << "Albero fuso (test 2): ";
    for (int x : bigMerged) cout << x << " ";
    cout << endl;

    return 0;
}