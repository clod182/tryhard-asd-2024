#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO ESERCIZIO 6
In un parcheggio destinato ad automobili di lusso, ogni auto e' assicurata per un determinato valore.  
Il parcheggiatore deve riorganizzare le auto di modo che la differenza tra i valori di auto parcheggiate consecutivamente 
sia la più piccola possibile. Più precisamente l'obiettivo è minimizzare la somma delle differenze in valore assoluto dei valore tra auto adiacenti. 
Ovviamente il parcheggiatore vuole ottenere questo risultato con il numero minimo di scambi di automobili. 
Si richiede quindi la creazione di un algoritmo EFFICENTE che determini il numero minimo di scambi necessari.
 
Le auto sono rappresentate da un array di numeri naturali, e l'output desiderato è un singolo numero naturale che indica il numero minimo di scambi richiesti.
 
Il prototipo della funzione è:
 
int numscambi(vector<int>& v)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/
/*#region utilities functions*/

// Funzione di supporto per stampare l'array
void stampaArray(const vector<int>& v) {
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}

/*#endregion utilities functions*/

// Funzione di merge per il merge sort
void mymerge(vector<pair<int, int>>& arr, int p, int med, int r) {
    vector<pair<int, int>> aux;
    int i = p, j = med + 1;
    
    while (i <= med && j <= r) {
        if (arr[i] <= arr[j]) {
            aux.push_back(arr[i]);
            ++i;
        } else {
            aux.push_back(arr[j]);
            ++j;
        }
    }
    
    if (i <= med) {
        for (j = med; j >= i; --j) {
            arr[r] = arr[j];
            --r;
        }
    }

    for (i = 0; i < aux.size(); ++i)
        arr[p + i] = aux[i];
}

// Funzione ricorsiva di merge sort
void mymergesort(vector<pair<int, int>>& arr, int p, int r) {
    if (p < r) {
        int med = (p + r) / 2;
        mymergesort(arr, p, med);
        mymergesort(arr, med + 1, r);
        mymerge(arr, p, med, r);
    }
}

// Funzione per invertire l'array
void reverse(vector<pair<int, int>>& arr) {
    int first = 0;
    int last = arr.size() - 1;
    
    while (first < last) {
        swap(arr[first], arr[last]);
        first++;
        last--;
    }
}

int numscambi(vector<int>& v) {
    int result = -1;
    int n = v.size();
    
    // Crea un array di coppie (valore, indice originale)
    vector<pair<int, int>> arrPos(n);
    for (int i = 0; i < n; i++) {
        arrPos[i].first = v[i];     // valore dell'auto
        arrPos[i].second = i;       // indice originale
    }

    // Itera due volte per ordinare in entrambe le direzioni
    for (int rev = 0; rev < 2; rev++) {
        int curSwap = 0;
        vector<bool> vis(n, false);

        if (rev) {
            reverse(arrPos);
        } else {
            mymergesort(arrPos, 0, arrPos.size() - 1);
        }

        // Trova il numero di scambi necessari
        for (int i = 0; i < v.size(); i++) {
            if (!vis[i] && arrPos[i].second != i) {
                int cycle_size = 0;
                int j = i;
                
                while (!vis[j]) {
                    vis[j] = true;
                    j = arrPos[j].second;
                    cycle_size++;
                }

                if (cycle_size > 0) {
                    curSwap += (cycle_size - 1);
                }
            }
        }

        if (result == -1) {
            result = curSwap;
        } else {
            result = min(result, curSwap);
        }
    }

    return result;
}

int main() {
    // Esempio di array di test
    vector<int> v = {5, 6, 11, 9, 3};
    
    // Stampa dell'array originale
    cout << "Array originale: ";
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;

    // Calcolo del numero minimo di scambi
    int scambi = numscambi(v);
    cout << "Numero minimo di scambi: " << scambi << endl;

    return 0;
}