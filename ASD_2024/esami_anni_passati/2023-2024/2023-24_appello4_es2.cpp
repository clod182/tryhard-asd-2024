#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO4
Per ordinare l’array A[1..n], si ordina in modo ricorsivo il sottoarray A[1.. n-1] e poi si inserisce A[n] nel sottoarray ordinato A[1.. n-1].

a. Scrivere lo pseudocodice per questa variante ricorsiva dell’insertion sort.

b. Fornire una ricorrenza per il suo tempo di esecuzione nel caso peggiore e risolverla in modo
formale.

c. Quale è il tempo di esecuzione nel caso migliore? Mostrare un esempio di input che determina
il caso migliore.

*/

/*#region utilities functions*/


/*#endregion utilities functions*/

//versione iterativa per confronto
/*
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) { //partiamo da 1 perchè Il primo elemento (arr[0]) 
															    //è già "ordinato" da solo
        int key = arr[i];
        int j = i - 1;
        
        // Sposta gli elementi di arr[0..i-1], che sono maggiori di key, 
        //di una posizione avanti
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
*/

//----------------------------------------------------------------------------------------------------------------------------------------
void insertionSortRic(vector<int>& vect, int n) {
    // Caso base: un solo elemento è già ordinato
    if (n <= 1)
        return;

    // Ordina ricorsivamente il sottoarray vect[0..n-2]
    insertionSortRic(vect, n - 1);

    // Inserisci vect[n-1] nella posizione corretta in vect[0..n-2]
    int key = vect[n - 1];
    int j = n - 2;

    // Sposta gli elementi maggiori di key a destra
    while (j >= 0 && vect[j] > key) {
        vect[j + 1] = vect[j];
        j--;
    }

    // Inserisci key nella posizione corretta
    vect[j + 1] = key;
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

void printVector(const vector<int>& vect) {
    for (int val : vect)
        cout << val << " ";
    cout << endl;
}

// Overload comodo per chiamare la funzione dal main senza passare la taglia
void insertionSortRic(vector<int>& vect) {
    insertionSortRic(vect, vect.size());
}

int main() {
    vector<int> test1 = {5, 2, 4, 6, 1, 3};
    vector<int> test2 = {1, 2, 3, 4, 5, 6};   // già ordinato
    vector<int> test3 = {6, 5, 4, 3, 2, 1};   // ordine inverso
    vector<int> test4 = {9};                 // un solo elemento
    vector<int> test5 = {};                  // vettore vuoto

    vector<vector<int>> tests = {test1, test2, test3, test4, test5};

    for (int i = 0; i < tests.size(); ++i) {
        cout << "Test " << i+1 << " - Prima:  ";
        printVector(tests[i]);

        insertionSortRic(tests[i]);

        cout << "         Dopo:   ";
        printVector(tests[i]);
        cout << "------------------------" << endl;
    }

    return 0;
}