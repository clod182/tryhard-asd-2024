#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*

Sia H1 un vettore di lunghezza 2n contenente un max-heap di interi, di dimensione n, secondo lo schema visto a
lezione (e nel libro di testo). 
Sia H2 un vettore di lunghezza n contenente un max-heap di interi di lunghezza n,
secondo lo schema visto a lezione (e nel libro di testo). 
Si consideri il problema di trasformare il vettore H1 in un
vettore ordinato contenente tutti gli elementi degli heap H1 ed H2, senza allocare altri vettori ausiliari.

a. Fornire lo pseudocodice di un algoritmo efficiente per risolvere il problema proposto utilizzando, tra le
procedure viste a lezione, solamente max-heapify.
b. Determinarne e giustificare la complessità.

*/
// Funzione per max-heapify
void maxHeapify(vector<int>& heap, int i, int heap_size) {
    int largest = i;          // Assumiamo che il nodo corrente sia il più grande
    int left = 2 * i + 1;     // Indice del figlio sinistro
    int right = 2 * i + 2;    // Indice del figlio destro

    // Se il figlio sinistro è più grande del nodo corrente
    if (left < heap_size && heap[left] > heap[largest]) {
        largest = left;
    }

    // Se il figlio destro è più grande del più grande trovato finora
    if (right < heap_size && heap[right] > heap[largest]) {
        largest = right;
    }

    // Se il più grande non è il nodo corrente
    if (largest != i) {
        swap(heap[i], heap[largest]); // Scambiamo il nodo corrente con il più grande
        maxHeapify(heap, largest, heap_size); // Ricorsivamente sistemiamo il sotto-albero
    }
}

// Funzione di test per l'esercizio
void transformHeaps(vector<int>& H1, vector<int>& H2) {
    int n = H2.size();
    
    // Copia gli elementi di H2 in H1 (n elementi successivi)
    for(int i = 0; i < n; i++){
        H1[i + n] = H2[i];
    }

    // Heapify bottom-up: partiamo dal primo nodo non foglia verso l'alto
    for(int i = (2 * n) / 2 - 1; i >= 0; i--) {
        maxHeapify(H1, i, 2 * n);  // H1 ha ora 2n elementi
    }
}

int main() {
    int n = 5; // Dimensione di H2 e metà di H1

    // H1 è lungo 2n, ma solo i primi n elementi formano un max-heap
    vector<int> H1 = {16, 14, 10, 8, 7, 0, 0, 0, 0, 0}; // max-heap con n elementi

    // H2 è un max-heap di dimensione n
    vector<int> H2 = {15, 13, 5, 6, 11}; // max-heap con n elementi

    // Output iniziale
    cout << "Heap H1 iniziale: ";
    for (int x : H1) cout << x << " ";
    cout << endl;

    cout << "Heap H2 iniziale: ";
    for (int x : H2) cout << x << " ";
    cout << endl;

    // Chiamata alla funzione che devi implementare
    transformHeaps(H1, H2);

    // Output finale
    cout << "Vettore trasformato (ordinato): ";
    for (int x : H1) cout << x << " ";
    cout << endl;

    return 0;
}