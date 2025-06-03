#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO3
Sia H1 un vettore di lunghezza 2n contenente un max-heap di interi, di dimensione n, secondo lo schema visto a
lezione (e nel libro di testo). Sia H2 un vettore di lunghezza n contenente un max-heap di interi di lunghezza n,
secondo lo schema visto a lezione (e nel libro di testo). Si consideri il problema di trasformare il vettore H1 in un
vettore ordinato contenente tutti gli elementi degli heap H1 ed H2, senza allocare altri vettori ausiliari.

a. Fornire un algoritmo efficiente in c++ per risolvere il problema proposto utilizzando, tra le procedure viste a lezione, solamente max-heapify.

b. Determinarne e giustificare la complessità.

*/

/*#region utilities functions*/
void maxHeapify(vector<int>& vect, int i, int heapSize){

    int left = i*2+1;
    int right = i*2+2;
    
    int max = i;
    if (left < heapSize && vect[left] > vect[max]){
        max = left;
    }

    if (right < heapSize && vect[right] > vect[max]){
        max = right;
    }

    if(max != i){
        swap(vect[i], vect[max]);
        maxHeapify(vect, max, heapSize);
    }

}

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
void merge_and_sort_heaps(vector<int>& H1, const vector<int>& H2){
    int n = H2.size();
// PASSO 1: Copia H2 nella seconda metà di H1
    for (int i = 0; i < n; i++) {
        H1[n + i] = H2[i];
    }
    
    // PASSO 2: Ricostruisci l'heap di dimensione 2n
    // Applica max-heapify dal penultimo livello verso l'alto
    for (int i = n - 1; i >= 0; i--) {
        maxHeapify(H1, i, 2 * n);
    }
    
    // PASSO 3: Heapsort - estrai ripetutamente il massimo
    for (int heapSize = 2 * n; heapSize > 1; heapSize--) {
        // Il massimo è sempre in H1[0]
        // Scambialo con l'ultimo elemento dell'heap
        swap(H1[0], H1[heapSize - 1]);
        
        // Ripristina la proprietà di heap per i primi heapSize-1 elementi
        maxHeapify(H1, 0, heapSize - 1);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
// Funzione di supporto per stampare un vettore
void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

// Funzione per verificare se il vettore è ordinato in senso crescente
bool isSortedAscending(const vector<int>& v) {
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i-1] > v[i]) return false;
    return true;
}

int main() {
    // Test 1: H1 e H2 con elementi distinti e ordinabili chiaramente
    vector<int> H1_test1 = {20, 15, 18, 10, 12, 17, 13, 0, 0, 0, 0, 0, 0, 0}; // dimensione 2n = 14, heap su primi 7
    vector<int> H2_test1 = {19, 14, 16, 11, 9, 8, 7}; // heap di dimensione 7
    merge_and_sort_heaps(H1_test1, H2_test1);
    assert(isSortedAscending(H1_test1));
    cout << "Test 1 passed: ";
    printVector(H1_test1);

    // Test 2: H1 e H2 già contenenti numeri ordinati decrescenti
    vector<int> H1_test2 = {100, 90, 80, 70, 60, 50, 40, 0, 0, 0, 0, 0, 0, 0};
    vector<int> H2_test2 = {95, 85, 75, 65, 55, 45, 35};
    merge_and_sort_heaps(H1_test2, H2_test2);
    assert(isSortedAscending(H1_test2));
    cout << "Test 2 passed: ";
    printVector(H1_test2);

    // Test 3: Tutti elementi uguali
    vector<int> H1_test3 = {10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0};
    vector<int> H2_test3 = {10, 10, 10, 10, 10, 10, 10};
    merge_and_sort_heaps(H1_test3, H2_test3);
    assert(isSortedAscending(H1_test3));
    cout << "Test 3 passed: ";
    printVector(H1_test3);

    // Test 4: H1 con elementi piccoli, H2 con elementi grandi
    vector<int> H1_test4 = {5, 3, 4, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> H2_test4 = {100, 99, 98, 97, 96, 95, 94};
    merge_and_sort_heaps(H1_test4, H2_test4);
    assert(isSortedAscending(H1_test4));
    cout << "Test 4 passed: ";
    printVector(H1_test4);

    // Test 5: Elementi mescolati tra H1 e H2
    vector<int> H1_test5 = {25, 18, 20, 14, 13, 16, 15, 0, 0, 0, 0, 0, 0, 0};
    vector<int> H2_test5 = {19, 17, 23, 22, 21, 12, 11};
    merge_and_sort_heaps(H1_test5, H2_test5);
    assert(isSortedAscending(H1_test5));
    cout << "Test 5 passed: ";
    printVector(H1_test5);

    cout << "\n✅ Tutti i test superati correttamente.\n";
    return 0;
}