#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO1
Si consideri la struttura dati Max-Heap implementata tramite un vettore (secondo lo schema visto a lezione).

a) Si scriva la definizione di Max-Heap. 

b) Si realizzi in modo efficiente la funzione Intersezione (H1, H2) che dati due Max-Heap H1 e H2 
contenenti rispettivamente n1 e n2 interi (anche ripetuti), ritorna in output un nuovo Max-Heap contenente gli elementi che appartengono sia a Hl che a H2. 
In presenza di duplicati se x compare kl volte in Hl e k2 volte in H2, nel Max-Heap intersezione x dovrà comparire min kl,k2). 

c)Si determini e giustifichi la complessità in funzione di nl e n2. 
Si devono scrivere le eventuali funzioni/procedure ausiliarie utilizzate.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
void max_heapify(vector<int>& A, int i, int heap_size) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int largest = i;

    if (l < heap_size && A[l] > A[largest]) largest = l;
    if (r < heap_size && A[r] > A[largest]) largest = r;

    if (largest != i) {
        swap(A[i], A[largest]);
        max_heapify(A, largest, heap_size);
    }
}

int extractMAx(vector<int>& A, int& heap_size){
    int ret = A[0];
    A[0] = A[heap_size-1];
    heap_size--;
    max_heapify(A, 0, heap_size); // da 0 e non da (heapsize/2)-1 in questo caso, dobbiamo ricontrollare tutto l'heap
    return ret;
}

// TC tot = O(n1 log n1) + O(n2 log n2)?
vector<int> Intersezione(vector<int>& H1, vector<int>& H2) { 
    vector<int> ret;

    int dim1 = H1.size();
    int dim2 = H2.size();
    if(dim1 > 0 && dim2 > 0){
        int max1 = extractMAx(H1, dim1);
        int max2 = extractMAx(H2, dim2);

        while(dim1 > 0 && dim2 > 0){
            if(max1 == max2){
                ret.push_back(max1);
                max1 = extractMAx(H1, dim1);
                max2 = extractMAx(H2, dim2);
            }
            else if(max1 > max2) max1 = extractMAx(H1, dim1); 
            else if(max1 < max2) max2 = extractMAx(H2, dim2);
        }
    }    

    return ret; // WIP dobbiamo ritornare un maxheap, non il semplice vettore ordianto così
}
//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
// === Funzione di utilità ===
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

// === MAIN di test avanzato ===
int main() {
    cout << "=== TEST AVANZATI SU MAX-HEAP ===\n";

    // Caso 1: Heap lunghi con molti duplicati
    vector<int> H1 = {
        100, 90, 90, 80, 70, 60, 60, 55, 50, 45,
        40, 40, 35, 30, 25, 20, 20, 15, 10, 5
    };
    vector<int> H2 = {
        95, 90, 80, 75, 70, 65, 60, 55, 50, 45,
        40, 35, 35, 30, 25, 20, 15, 10, 10, 5
    };
    cout << "\nCaso 1 (intersezione ampia):\n";
    vector<int> res1 = Intersezione(H1, H2);
    printVector(res1); // Attesi: elementi comuni ripetuti min volte

    // Caso 2: Heap con intersezione parziale e duplicati disallineati
    vector<int> H3 = {
        200, 150, 120, 100, 100, 100, 90, 80, 70, 60, 50
    };
    vector<int> H4 = {
        190, 150, 130, 100, 90, 90, 70, 60, 40
    };
    cout << "\nCaso 2 (intersezione parziale con ripetizioni):\n";
    vector<int> res2 = Intersezione(H3, H4);
    printVector(res2); // Attesi: 150, 100, 90, 70, 60

    // Caso 3: Heap con intersezione completa (stesso contenuto)
    vector<int> base = {
        50, 48, 45, 42, 40, 38, 36, 34, 32, 30,
        28, 26, 24, 22, 20, 18, 16, 14, 12, 10
    };
    vector<int> H5 = base;
    vector<int> H6 = base;
    cout << "\nCaso 3 (heap identici):\n";
    vector<int> res3 = Intersezione(H5, H6);
    printVector(res3); // Tutti gli elementi

    // Caso 4: Heap con un singolo valore ripetuto
    vector<int> H7(15, 77); // 15 elementi tutti 77
    vector<int> H8(10, 77); // 10 elementi tutti 77
    cout << "\nCaso 4 (valore unico ripetuto):\n";
    vector<int> res4 = Intersezione(H7, H8);
    printVector(res4); // 10 volte 77

    // Caso 5: Heap con piccola intersezione e ordine inverso
    vector<int> H9 = {99, 97, 95, 92, 90, 85, 80, 70};
    vector<int> H10 = {100, 98, 95, 85, 60, 55, 50};
    cout << "\nCaso 5 (intersezione ristretta):\n";
    vector<int> res5 = Intersezione(H9, H10);
    printVector(res5); // 95 e 85

    return 0;
}
