#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 3
Scrivere una funzione che, ricevuto in input un intero k (1 ≤ k ≤ n) e un array v, NON ordinato, di n elementi distinti, 
restituisce il k−esimo elemento più piccolo di v. 

Trovare una soluzione di costo in tempo:
1. Θ(n log n) avente prototipo:
int cercaK esimoPrimaSol(vector<int>& arr, int k);

2. O(n + k log n) avente prototipo:
int cercaK esimoSecondaSol(vector<int>& arr, int k);

3. O(n log k) avente prototipo:
int cercaK esimoTerzaSol(vector<int>& arr, int k).

Dimostrare che la complessità delle funzioni è quella richiesta.
Se k è costante quale delle soluzioni in ordine di grandezza è la migliore?
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
//----------1 Θ(n log n)
// Funzione merge per unire due metà ordinate
// Funzione per unire (merge) due sottovettori ordinati
void merge(vector<int>& v, int sx, int mid, int dx) {
    // Calcolo delle dimensioni dei due sottovettori
    int dimensione_sx = mid - sx + 1;
    int dimensione_dx = dx - mid;
    
    // Creazione dei vettori temporanei
    vector<int> sinistra(dimensione_sx);
    vector<int> destra(dimensione_dx);
    
    // Copia degli elementi nei vettori temporanei
    for(int i = 0; i < dimensione_sx; i++) {
        sinistra[i] = v[sx + i];
    }    
    for(int j = 0; j < dimensione_dx; j++) {
        destra[j] = v[mid + 1 + j];
    }
    
    // Indici per scorrere i vettori
    int indice_sx = 0;     // indice per il vettore sinistra
    int indice_dx = 0;     // indice per il vettore destra
    int indice_merge = sx; // indice per il vettore originale v
    
    // Fase di merge: confronta e inserisce gli elementi in ordine
    while(indice_sx < dimensione_sx && indice_dx < dimensione_dx) {
        if(sinistra[indice_sx] <= destra[indice_dx]) {
            // L'elemento a sinistra è minore (o uguale), lo inseriamo
            v[indice_merge] = sinistra[indice_sx];
            indice_sx = indice_sx + 1;
        } else {
            // L'elemento a destra è minore, lo inseriamo
            v[indice_merge] = destra[indice_dx];
            indice_dx = indice_dx + 1;
        }
        indice_merge = indice_merge + 1;
    }
    
    // Copiamo eventuali elementi rimasti nel vettore sinistra
    while(indice_sx < dimensione_sx) {
        v[indice_merge] = sinistra[indice_sx];
        indice_sx = indice_sx + 1;
        indice_merge = indice_merge + 1;
    }
    
    // Copiamo eventuali elementi rimasti nel vettore destra
    while(indice_dx < dimensione_dx) {
        v[indice_merge] = destra[indice_dx];
        indice_dx = indice_dx + 1;
        indice_merge = indice_merge + 1;
    }
}

// Funzione principale del Merge Sort
void mergeSort(vector<int>& v, int sx, int dx) {
    // Condizione di base: se la sezione contiene più di un elemento
    if(sx < dx) {
        // Troviamo il punto medio
        int mid = (sx + dx) / 2;
        
        // Ordiniamo ricorsivamente le due metà
        mergeSort(v, sx, mid);        // Ordina la metà sinistra
        mergeSort(v, mid + 1, dx);    // Ordina la metà destra
        
        // Uniamo (merge) le due metà ordinate
        merge(v, sx, mid, dx);
    }
    // Se sx >= dx, il sottovettore ha 0 o 1 elementi ed è già ordinato
}

int cercaKesimoPrimaSol(vector<int>& arr, int k){
  if(arr.size() <= 0) return -1;
  mergeSort(arr, 0, arr.size()-1);
  return arr[k-1];
}

//----------2 O(n + k log n)
/* Funzione di min_heapify Mantiene la proprietà del Min Heap */
void min_heapify(vector<int>& arr, int heap_size, int i) {
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    int minimo;

    // Trova il figlio con valore più piccolo rispetto a arr[i]
    if (left < heap_size && arr[left] < arr[i])
        minimo = left;
    else minimo = i;

    if (right < heap_size && arr[right] < arr[minimo])
        minimo = right;

    // Se uno dei figli ha valore minore, scambia e continua ricorsivamente
    if (minimo != i) {
        swap(arr[i], arr[minimo]);
        min_heapify(arr, heap_size, minimo);
    }
}

/* Costruzione del Min Heap Parte dai nodi interni fino alla radice Complessità: O(n) */
//Gli elementi situati negli indici da arr.size()/2 fino a arr.size()-1 sono tutti nodi foglia dell'heap, quindi non serve fargli min_heap
int buildminHeap(vector<int>& arr) {
    for (int i = arr.size() / 2 - 1; i >= 0; i--) {
        min_heapify(arr, arr.size(), i);
    }
    return arr.size();  // Ritorna la dimensione dell'heap iniziale
}

/* Estrazione del minimo dal Min Heap Sposta l’ultimo elemento in cima e ricostruisce l’heap Complessità: O(log n) */
int heap_extract_min(vector<int>& arr, int& heap_size) {
    int min = arr[0];  // Il minimo è sempre in cima
    arr[0] = arr[heap_size - 1];  // Sostituisco con l’ultimo elemento
    heap_size--;  // Riduco la dimensione dell’heap
    min_heapify(arr, heap_size, 0);  // Ripristino la proprietà del min heap
    return min;
}

/* Funzione principale Trova il k-esimo elemento più piccolo Complessità: O(n + k log n) */
int cercaKesimoSecondaSol(vector<int>& arr, int k) {
    int heap_size = buildminHeap(arr);  // O(n)
    int ris;
    while (k > 0) {
        ris = heap_extract_min(arr, heap_size);  // O(log n)
        k--;
    }
    return ris;
}

//----------3 O(n log k)
void max_heapify(vector<int>& arr, int heap_size, int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int massimo = i;

    if (left < heap_size && arr[left] > arr[massimo])
        massimo = left;

    if (right < heap_size && arr[right] > arr[massimo])
        massimo = right;

    if (massimo != i) {
        swap(arr[i], arr[massimo]);
        max_heapify(arr, heap_size, massimo);
    }
}

int extract_max(vector<int>& arr, int& heap_size){
  int max = arr[0];
  swap(arr[0], arr[heap_size-1]);
  heap_size --;
  max_heapify(arr, heap_size, 0);

  return max;
}

// Restituisce l'indice del padre
int parent(int i) {
    return (i - 1) / 2;
}

// Inserisce un elemento in un max-heap di dimensione k 
void max_heap_insert(vector<int>& arr, int& heap_size, int val) {
    int i = heap_size;
    int p = parent(i);
    arr[heap_size] = val;
    heap_size++;
    
    while (i > 0 && arr[i] > arr[p]) {
        swap(arr[i], arr[p]);
        i = p;
        p = parent(i);
    }
}

int cercaKesimoTerzaSol(vector<int>& arr, int k) {
    if (k <= 0 || k > arr.size()) return -1;

    vector<int> heap(k); // max-heap di dimensione al più k
    int heap_size = 0;

    // Inserisci i primi k elementi nell'heap
    for (int i = 0; i < k; i++) {
        max_heap_insert(heap, heap_size, arr[i]);
    }

    // Per ogni altro elemento, se è più piccolo del massimo, rimpiazza
    for (int i = k; i < arr.size(); i++) {
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];          // sovrascrive la radice
            max_heapify(heap, heap_size, 0); // ripristina il max-heap
        }
    }

    return heap[0]; // Il k-esimo più piccolo è in cima al max-heap
}

// Funzione di utilità per stampare vettori
void stampaVettore(const vector<int>& v) {
    for (int x : v)
        cout << x << " ";
    cout << endl;
}

int main() {
    srand(time(0));

    vector<int> v1 = {12, 3, 5, 7, 4, 19, 26};
    int k = 3;

    cout << "Vettore di partenza: ";
    stampaVettore(v1);
    cout << "k = " << k << endl;

    vector<int> copia1 = v1;
    vector<int> copia2 = v1;
    vector<int> copia3 = v1;

    int sol1 = cercaKesimoPrimaSol(copia1, k);
    int sol2 = cercaKesimoSecondaSol(copia2, k);
    int sol3 = cercaKesimoTerzaSol(copia3, k);

    cout << "[Soluzione 1 - n log n]       Risultato: " << sol1 << endl;
    cout << "[Soluzione 2 - n + k log n]   Risultato: " << sol2 << endl;
    cout << "[Soluzione 3 - n log k]       Risultato: " << sol3 << endl;

    return 0;
}

