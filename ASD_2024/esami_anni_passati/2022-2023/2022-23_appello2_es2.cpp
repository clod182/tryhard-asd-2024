#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO2
Sia A un vettore in cui ogni elemento contiene due campi: A[i].value contiene un numero intero ed A[i].color contiene un colore (BIANCO o NERO). 
Gli elementi di A sono ordinati in ordine crescente rispetto al campo value.

a. Si consideri il problema di ordinare gli elementi di A rispetto al campo color secondo l’ordinamento BIANCO<NERO, facendo in modo che gli elementi dello stesso colore siano ordinati rispetto al
campo value. 
firma: void ordinaPerColore(vector<ValCol>& arr)

b. Si consideri il problema di ordinare gli elementi di A rispetto al campo value, facendo in modo che
gli elementi che hanno stesso value siano ordinati rispetto al campo color (sempre con la convenzione
BIANCO<NERO).
firma: void ordinaPerValore(vector<ValCol>& arr)

*/

/*#region utilities functions*/
enum Color { BIANCO, NERO };

struct ValCol {
    int value;
    Color color;
};

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// PUNTO A

/*
// Versione alternativa più semplice (Two-pointer approach)
void ordinaPerColoreAlternativo(vector<ValCol>& arr) {
    int sinistra = 0;
    int destra = arr.size() - 1;
    
    while(sinistra < destra) {
        // Trova elemento NERO a sinistra
        while(sinistra < destra && arr[sinistra].color == BIANCO) {
            sinistra++;
        }
        
        // Trova elemento BIANCO a destra  
        while(sinistra < destra && arr[destra].color == NERO) {
            destra--;
        }
        
        // Scambia se necessario
        if(sinistra < destra) {
            swap(arr[sinistra], arr[destra]);
            sinistra++;
            destra--;
        }
    }
}
*/
void ordinaPerColore(vector<ValCol>& arr){
    if(arr.size() <= 0) return;

    int dim = arr.size();
    vector<int> count(2, 0); // abbiamo solo 2 colori da consegna

    for(int i=0; i<dim; i++){
        if(arr[i].color == BIANCO){ // BIANCO<NERO
            count[0]++;
        }
        else count[1]++;
    }

    // cumulative sum per mantere ordine og
    for(int i=1; i<count.size(); i++){
        count[i] = count[i]+count[i-1];
    }

    vector<ValCol> output(arr.size());

    for(int i=dim-1; i>=0; i--){
        if(arr[i].color == BIANCO){
             output[count[0] -1] = arr[i];
             count[0]--;
        }
        else{
            output[count[1] -1] = arr[i];
             count[1]--;
        }
    }

    arr = output;
}

//----------------------------------------------------------------------------------------------------------------------------------------
// PUNTO B

// Funzione ausiliaria per ordinare per colore un sottoarray [start, end)
//E' UNA VERSIONE LEGGERMENTE MODIFICATA DEL PUNTO A
void ordinaPerColoreRange(vector<ValCol>& arr, int start, int end) {
    int n = end - start;
    vector<int> count(2, 0);

    // Conteggio
    for (int i = start; i < end; ++i) {
        count[arr[i].color]++;
    }

    // Cumulative count 
    for(int i = 1; i < count.size(); i++) {
        count[i] = count[i] + count[i-1];
    }
    // count[0] = fine_bianchi, count[1] = fine_totale

    vector<ValCol> temp(n);
    
    // IMPORTANTE: Scorrimento all'indietro per stabilità
    for (int i = end - 1; i >= start; --i) {
        int idx = --count[arr[i].color];  // Pre-decremento!
        temp[idx] = arr[i];
    }

    // Copia nel vettore originale
    for (int i = 0; i < n; ++i) {
        arr[start + i] = temp[i];
    }
}

// Funzione principale punto (b)
void ordinaPerValore(vector<ValCol>& arr) {
    int n = arr.size();
    int i = 0;

    while (i < n) {
        int j = i + 1;
        while (j < n && arr[j].value == arr[i].value) {
            ++j;
        }

        // Ora [i, j) è il blocco con stesso value
        ordinaPerColoreRange(arr, i, j);
        i = j;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

void stampa(const vector<ValCol>& arr) {
    for (const auto& v : arr) {
        cout << "(" << v.value << "," << (v.color == BIANCO ? "B" : "N") << ") ";
    }
    cout << "\n";
}

int main() {
    // arr1: già ordinato per value crescente (come richiede la consegna del punto a)
    vector<ValCol> arr1 = {
        {5, BIANCO}, {5, NERO}, {7, BIANCO}, {7, NERO}, {10, BIANCO}, {10, NERO}
    };

    cout << "Originale 1 --------------------:\n";
    stampa(arr1);

    ordinaPerColore(arr1);
    cout << "Ordina per colore (stabile):\n";
    stampa(arr1);

    // arr2: ordine qualsiasi per testare il sort completo su value e colore
    vector<ValCol> arr2 = {
        {3, NERO}, {3, BIANCO}, {3, NERO}, {3, BIANCO},
        {5, BIANCO}, {5, NERO}, {5, BIANCO}, {5, NERO},
        {7, NERO}, {7, BIANCO}, {7, NERO}, {7, BIANCO},
        {10, NERO}, {10, BIANCO}, {10, NERO}, {10, BIANCO}
    };

    cout << "Originale 2 --------------------:\n";
    stampa(arr2);

    ordinaPerValore(arr2);
    cout << "Ordina per valore e tie-break colore:\n";
    stampa(arr2);

    return 0;
}
