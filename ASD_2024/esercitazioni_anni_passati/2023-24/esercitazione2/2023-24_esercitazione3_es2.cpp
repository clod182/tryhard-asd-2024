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

/*#endregion utilities functions*/


int main() {
    // Array di test
    vector<int> arr = {81, 16, 1, 256, 0, 1296, 625, 4096, 2401};

    // Stampa dell'array originale
    cout << "Array originale: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Chiamata alla funzione di ordinamento
    order(arr);

    // Stampa dell'array ordinato
    cout << "Array ordinato (non crescente): ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}