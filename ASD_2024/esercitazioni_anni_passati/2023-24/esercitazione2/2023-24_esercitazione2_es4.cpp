#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO ESERCIZIO 4
Sia H1 un vettore di lunghezza 2n contenente un max-heap di interi, di dimensione n. Sia H2 un vettore di lunghezza n contenente un max-heap 
di interi di lunghezza n. Si consideri il problema di trasformare il vettore H1 in un vettore ordinato contenente tutti gli elementi degli heap H1 ed H2, 
senza allocare altri vettori ausiliari.

Fornire una procedura EFFICENTE per risolvere il problema proposto utilizzando, tra le procedure viste a lezione, SOLAMENTE max-heapify.

Il prototipo della funzione è:
void ordinaMaxHeap(PMaxHeap h1, PMaxHeap h2)

Dove il tipo PMaxHeap è definito nel seguente modo:

struct MaxHeap{

  vector<int> elements;

  int heapsize;

  int dim;

};

typedef MaxHeap *PMaxHeap;

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/

struct MaxHeap {
    vector<int> elements;
    int heapsize;
    int dim;
};

typedef MaxHeap* PMaxHeap;

// Funzioni di utilità per il max-heap
int parent(int i) { return (i - 1) / 2; }
int left(int i) { return 2 * i + 1; }
int right(int i) { return 2 * i + 2; }

// Funzione per eseguire max-heapify, mantenendo la proprietà di max-heap
void maxHeapify(PMaxHeap h, int i) {
    int l = left(i);
    int r = right(i);
    int massimo = i;

    if (l < h->heapsize && h->elements[l] > h->elements[massimo])
        massimo = l;
    if (r < h->heapsize && h->elements[r] > h->elements[massimo])
        massimo = r;

    if (massimo != i) {
        swap(h->elements[i], h->elements[massimo]);
        maxHeapify(h, massimo);
    }
}

// Funzione per estrarre il massimo (radice) dall'heap
int extractMax(PMaxHeap heap) {
    if (heap->heapsize == 0) return -1;  // se l'heap è vuoto, ritorna un valore di errore
    int max = heap->elements[0];
    heap->elements[0] = heap->elements[heap->heapsize - 1];
    heap->heapsize--;
    maxHeapify(heap, 0);
    return max;
}

// Funzione per inserire un elemento nell'heap
void insert(PMaxHeap h, int value) {
    if (h->heapsize == h->dim) {
        cout << "Heap pieno, impossibile inserire altri elementi!" << endl;
        return;
    }

    // Aggiungiamo l'elemento alla fine e aumentiamo la dimensione
    h->elements[h->heapsize] = value;
    int i = h->heapsize;
    h->heapsize++;

    // Heapify verso l'alto per mantenere la proprietà del max-heap
    while (i > 0 && h->elements[parent(i)] < h->elements[i]) {
        swap(h->elements[i], h->elements[parent(i)]);
        i = parent(i);
    }
}

/*#endregion utilities functions*/

// Funzione principale per ordinare H1 e H2 combinandoli
void ordinaMaxHeap(PMaxHeap h1, PMaxHeap h2) {
    // Uniamo gli elementi di H2 in H1
    for (int i = 0; i < h2->heapsize; i++) {
        insert(h1, h2->elements[i]);
    }

    // Ordinamento dell'heap combinato in-place
    /*Il ciclo parte dall'ultima posizione di H1 (h1->dim - 1) e si muove verso la prima posizione (i = 0).
    Questo ci permette di riempire progressivamente H1 con gli elementi ordinati in ordine crescente, partendo dal più piccolo. 
    Poiché riempiamo il vettore dall'ultima posizione alla prima, ogni elemento estratto (derivante dal extractMax) si trova automaticamente 
    nella posizione corretta per un ordinamento crescente.*/
    for (int i = h1->dim - 1; i >= 0; i--) {
        h1->elements[i] = extractMax(h1);
    }
}

int main() {
    // Creazione del primo heap H1
    MaxHeap heap1;
    heap1.elements = vector<int>(8);
    heap1.elements[0] = 50;
    heap1.elements[1] = 30;
    heap1.elements[2] = 20;
    heap1.elements[3] = 10;
    heap1.heapsize = 4;
    heap1.dim = 8;

    // Creazione del secondo heap H2
    MaxHeap heap2;
    heap2.elements = vector<int>(4);
    heap2.elements[0] = 40;
    heap2.elements[1] = 25;
    heap2.elements[2] = 15;
    heap2.elements[3] = 5;
    heap2.heapsize = 4;
    heap2.dim = 4;

    // Ordinamento di H1
    ordinaMaxHeap(&heap1, &heap2);

    // Stampa del risultato
    //H1 ordinato: 5 10 15 20 25 30 40 50
    cout << "H1 ordinato: ";
    for (int i = 0; i < heap1.dim; i++) {
        cout << heap1.elements[i] << " ";
    }
    cout << endl;

    return 0;
}