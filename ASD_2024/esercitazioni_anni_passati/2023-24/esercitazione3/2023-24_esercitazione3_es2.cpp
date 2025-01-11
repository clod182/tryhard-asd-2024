#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
// <>

/* TESTO ESERCIZIO 2

Sia A un vettore in cui ogni elemento contiene due campi: A[i].value contiene un numero intero ed A[i].color contiene un colore ('b' o 'n'). 
Gli elementi di A sono ordinati in ordine crescente rispetto al campo value.

a) Si consideri il problema di ordinare gli elementi di A rispetto al campo color secondo l’ordinamento b < n, 
facendo in modo che gli elementi dello stesso colore siano ordinati rispetto al campo value. 
Si scriva una procedura EFFICIENTE per risolvere il problema proposto. Si valuti e giustifichi la complessità.

Il prototipo della procedura è:
void ordinaPerColore(vector<ValCol>& arr)

b) Si consideri il problema di ordinare gli elementi di A rispetto al campo value, 
facendo in modo che gli elementi che hanno stesso value siano ordinati rispetto al campo colore (sempre con la convenzione b < n). 
Si scriva una procedura EFFICIENTE per risolvere il problema proposto. Si valuti e giustifichi la complessità.

Il prototipo della procedura è:
void ordinaPerValore(vector<ValCol>& arr)

Il tipo ValCol e' cosi' definito:

typedef struct{
    int value;
    char colour;
} ValCol;

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
/*#region utilities functions*/
typedef struct {
    int value;     // Campo intero per il valore
    char colour;   // Campo carattere per il colore ('b' o 'n')
} ValCol;

// Prototipi delle funzioni
void ordinaPerColore(vector<ValCol>& arr);
void ordinaPerValore(vector<ValCol>& arr);

// Funzione per stampare il vettore
void stampaVettore(const vector<ValCol>& arr) {
    for (const auto& elem : arr) {
        cout << "(" << elem.value << ", " << elem.colour << ") ";
    }
    cout << endl;
}
/*#endregion utilities functions*/

void ordinaPerColore(vector<ValCol>& arr) {
    vector<ValCol> temp(arr.size());
    int num_n = 0, num_b = 0;

    // Conta il numero di colori
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].colour == 'b') num_b++;
        else num_n++;
    }

    // Indici per i colori
    int c1 = 0;
    int c2 = num_b;

    // Ordina gli elementi in temp
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].colour == 'b') {
            temp[c1] = arr[i];
            c1++;
        } else {
            temp[c2] = arr[i];
            c2++;
        }
    }

    // Copia temp in arr
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = temp[i];
    }
}

// Funzione per riorganizzare i colori in un blocco di elementi
void riorganizza(vector<ValCol>& arr, int inizio, int fine) {
    ValCol temp; // Variabile temporanea per gli scambi
    int bianchi = inizio - 1; // Indice per tracciare la fine dei bianchi

    // Scorre il blocco da "inizio" a "fine"
    for (int neri = inizio; neri <= fine; neri++) {
        if (arr[neri].colour == 'b') { // Se è bianco:
            bianchi++; // Incrementa la posizione finale dei bianchi
            // Scambia l'elemento bianco con quello in posizione "bianchi"
            temp = arr[neri];
            arr[neri] = arr[bianchi];
            arr[bianchi] = temp;
        }
    }
}

// Funzione principale per ordinare per valore
void ordinaPerValore(vector<ValCol>& arr) {
    int i = 0, j;

    // Itera su tutti gli elementi dell'array
    while (i < arr.size()) {
        j = i + 1;

        // Trova l'estensione del blocco di elementi con lo stesso valore
        while (j < arr.size() && arr[i].value == arr[j].value) {
            j++;
        }

        // Riorganizza il blocco [i, j-1] per colore
        riorganizza(arr, i, j - 1);

        // Passa al prossimo blocco
        i = j;
    }
}



int main() {
    // Vettore di test, già ordinato per il campo value
    vector<ValCol> arr = {
        {1, 'b'}, {2, 'n'}, {3, 'b'}, {3, 'n'}, {4, 'b'}, {5, 'n'}
    };

    cout << "Array originale:" << endl;
    for (const auto& el : arr) {
        cout << "{" << el.value << ", " << el.colour << "} ";
    }
    cout << endl;

    // Test della funzione ordinaPerColore
    ordinaPerColore(arr);
    cout << "Array ordinato per colore:" << endl;
    for (const auto& el : arr) {
        cout << "{" << el.value << ", " << el.colour << "} ";
    }
    cout << endl;

    // Riordiniamo per valore (per testare ordinaPerValore)
    vector<ValCol> arr2 = {
        {1, 'b'}, {2, 'n'}, {3, 'b'}, {3, 'n'}, {4, 'b'}, {5, 'n'}, {5, 'b'}, {5, 'n'}
    };
    cout << "Array disordinato per valore (prima dell'ordinamento):" << endl;
    for (const auto& el : arr2) {
        cout << "{" << el.value << ", " << el.colour << "} ";
    }
    cout << endl;

    ordinaPerValore(arr2);
    cout << "Array ordinato per valore:" << endl;
    for (const auto& el : arr2) {
        cout << "{" << el.value << ", " << el.colour << "} ";
    }
    cout << endl;

    return 0;
}
