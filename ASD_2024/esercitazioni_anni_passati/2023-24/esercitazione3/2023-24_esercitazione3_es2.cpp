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

void ordinaPerColore(vector<ValCol>& arr){
    
}

int main() {
    // Test: vettore di esempio
    vector<ValCol> arr = {
        {5, 'n'}, {1, 'b'}, {3, 'b'}, {2, 'n'}, {4, 'b'}
    };

    // Stampa il vettore originale
    cout << "Vettore originale:\n";
    stampaVettore(arr);

    // Test funzione ordinaPerColore
    vector<ValCol> arrColore = arr;
    ordinaPerColore(arrColore);
    cout << "\nVettore ordinato per colore (b < n):\n";
    stampaVettore(arrColore);

    // Test funzione ordinaPerValore
    vector<ValCol> arrValore = arr;
    ordinaPerValore(arrValore);
    cout << "\nVettore ordinato per valore (con b < n per valori uguali):\n";
    stampaVettore(arrValore);

    return 0;
}