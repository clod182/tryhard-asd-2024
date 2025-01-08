#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO ESERCIZIO 3

Dato un vettore v di n numeri naturali, scrivere una procedura EFFICENTE che ordini v in modo tale che nel vettore risultante,
dati i e j con 0 <= i <= j<=n-1 , vale  mod(v[i], 3) <= mod(v[j], 3), dove  mod(x, 3) è il resto della divisione di x per 3.
 
Dire se la soluzione proposta è in loco e se è stabile
Valutare e giustificare la complessità della procedura proposta.
Il prototipo della funzione è:
 
void ordinaMod3(vector<int>& v)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

// Funzione per ordinare il vettore secondo il criterio mod(x, 3)
void ordinaMod3(vector<int>& v) {
    int low = 0, mid = 0, high = v.size() - 1;

    while (mid <= high) {
        int modValue = v[mid] % 3;

        if (modValue == 0) {
            // Elemento con resto 0: scambialo con la zona "low" e avanza entrambi i puntatori
            swap(v[low], v[mid]);
            low++;
            mid++;
        } else if (modValue == 1) {
            // Elemento con resto 1: è già nella zona corretta, avanza mid
            mid++;
        } else {
            // Elemento con resto 2: scambialo con la zona "high" e riduci high
            swap(v[mid], v[high]);
            high--;
        }
    }
}

int main() {
    // Esempio di test
    vector<int> v = {5, 9, 7, 3, 6, 12, 10, 4};
    //ordine atteso -->  9 3 6 12 7 4 10 5

    cout << "Vettore originale: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;

    ordinaMod3(v);

    cout << "Vettore ordinato secondo mod(x, 3): ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}