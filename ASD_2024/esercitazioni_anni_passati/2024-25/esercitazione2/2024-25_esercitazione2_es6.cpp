#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <unordered_set>

using namespace std;

/* TESTO
ESERCIZIO 6
Sia A un vettore di n interi e si consideri il problema di determinare se esistono due interi che occorrono in A lo stesso numero di volte.

1. Si scriva un algoritmo efficiente per il problema proposto. Il prototipo della funzione è:
bool stesseOccorrenze(vector<int>& arr)

2. Si scriva un algoritmo efficiente per il problema proposto nel caso in cui in A occorrono c valori distinti, dove c è una costante intera positiva (non è nota). 
Il prototipo della funzione è:
bool stesseOccorrenzeValoriDistintiCostanti(vector<int>& arr)

3. Si determini e giustifichi la complessità degli algoritmi proposti.

Si devono scrivere eventuali funzioni/procedure ausiliarie utilizzate.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function


//------------------------main function
bool stesseOccorrenze(vector<int>& arr){ //COMPLESSITA' O(n)
    if(arr.size() <= 1) return false;

    unordered_map<int, int> ricMap;
    int dim = arr.size();
    for(int i=0; i<dim; i++){
        ricMap[arr[i]] += 1;
    }

    unordered_set<int> freqSeen;
    for (auto elem : ricMap) {
        int freq = elem.second;

        if (freqSeen.count(freq)) {
            // Questa frequenza è già stata vista
            return true;
        }
        freqSeen.insert(freq);
    }
    return false; // tutte le frequenze sono uniche
}

bool stesseOccorrenzeValoriDistintiCostanti(vector<int>& arr){ //COMPLESSITA' O(n * c) = O(n)
    if(arr.size() <= 1) return false;

    vector<pair<int, int>> conteggi; // in questo esercizio è GARANTITO ci siano al massimo c elementi distinti 
    int dim = arr.size();
    for(int i=0; i<dim; i++){
        bool find = false;
        int dimConteggi = conteggi.size();
        for(int j=0; j<dimConteggi; j++){
            if(conteggi[j].first == arr[i]){
                ++conteggi[j].second;
                find = true;
                break; //una volta trovato il valore val, ho già aggiornato il conteggio, 
                       //e non ha senso continuare a scorrere il resto del vettore
            }
        }
        if(find == false){
            conteggi.push_back({arr[i], 1});
        }
    }

    int dimConteggi = conteggi.size();
    for(int i=0; i<dimConteggi; i++){
        for(int j=i+1; j<dimConteggi; j++){ //i+1 per non confrontare ogni elem con se stesso, 
                                            //e una volta confrontato un elemento con tutti gli altri, non c'è più bisogno di farlo
            if(conteggi[i].second == conteggi[j].second) return true;
        }
    }

    return false;
}

int main() {
    vector<int> test1 = {1, 2, 2, 3, 3, 4}; // true: 2 e 3 occorrono 2 volte
    vector<int> test2 = {1, 2, 3, 4, 5};    // false: ogni elemento è unico
    vector<int> test3 = {1, 1, 2, 2, 3, 3}; // true: tutti occorrono 2 volte
    vector<int> test4 = {7, 8, 8, 9, 9, 9}; // false: occorrenze diverse
    vector<int> test5 = {};                 // false: nessun elemento

    cout << boolalpha;

    cout << "Test1: " << stesseOccorrenze(test1) << endl;
    cout << "Test2: " << stesseOccorrenze(test2) << endl;
    cout << "Test3: " << stesseOccorrenze(test3) << endl;
    cout << "Test4: " << stesseOccorrenze(test4) << endl;
    cout << "Test5: " << stesseOccorrenze(test5) << endl;

    cout << "------ Caso c costante ------" << endl;

    cout << "Test1: " << stesseOccorrenzeValoriDistintiCostanti(test1) << endl;
    cout << "Test2: " << stesseOccorrenzeValoriDistintiCostanti(test2) << endl;
    cout << "Test3: " << stesseOccorrenzeValoriDistintiCostanti(test3) << endl;
    cout << "Test4: " << stesseOccorrenzeValoriDistintiCostanti(test4) << endl;
    cout << "Test5: " << stesseOccorrenzeValoriDistintiCostanti(test5) << endl;

    return 0;
}
