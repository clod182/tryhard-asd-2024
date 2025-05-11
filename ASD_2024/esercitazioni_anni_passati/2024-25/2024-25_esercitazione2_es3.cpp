#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 3
Questa settimana Carlotta ha ricevuto del denaro dai suoi genitori e vuole spenderlo tutto acquistando libri. ù
Per finire un libro Carlotta impiega una settimana e poiché riceve denaro ogni due settimane, ha deciso di acquistare due libri, 
così potrà leggerli fino a quando riceverà altri soldi. 
Desidera spendere tutti i soldi così vorrebbe scegliere due libri i cui prezzi sommati sono pari ai soldi che ha ricevuto.

Data la quantità di soldi che Carlotta ha a disposizione e un array contenente i prezzi dei libri (tutti distinti), 
restituire le coppie di prezzi di libri che soddisfano la condizione. 
Le coppie di prezzi devono contenere prima il prezzo più basso e poi quello più alto.

Scrivere una funzione efficiente il cui prototipo è il seguente:
int libriSelezionati(vector<int>& prezzolibri, double soldi, vector<pair<int,int>>& ris)
La funzione restituisce la dimensione dell’array ris. Si devono scrivere eventuali funzioni/procedure ausiliari utilizzate.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
int libriSelezionati(vector<int>& prezzolibri, double soldi, vector<pair<int, int>>& ris){

}


int main() {
    // Test 1: caso base, c'è una coppia valida
    vector<int> prezzi1 = {10, 15, 20, 5, 25};
    double soldi1 = 30;
    vector<pair<int, int>> ris1;
    int count1 = libriSelezionati(prezzi1, soldi1, ris1);
    cout << "Test 1: Coppie trovate = " << count1 << "\n";
    for (auto& p : ris1) cout << "(" << p.first << ", " << p.second << ")\n";

    // Test 2: più coppie possibili
    vector<int> prezzi2 = {8, 12, 17, 13, 22, 5};
    double soldi2 = 25;
    vector<pair<int, int>> ris2;
    int count2 = libriSelezionati(prezzi2, soldi2, ris2);
    cout << "\nTest 2: Coppie trovate = " << count2 << "\n";
    for (auto& p : ris2) cout << "(" << p.first << ", " << p.second << ")\n";

    // Test 3: nessuna coppia valida
    vector<int> prezzi3 = {1, 2, 3, 4};
    double soldi3 = 100;
    vector<pair<int, int>> ris3;
    int count3 = libriSelezionati(prezzi3, soldi3, ris3);
    cout << "\nTest 3: Coppie trovate = " << count3 << "\n";

    // Test 4: array vuoto
    vector<int> prezzi4 = {};
    double soldi4 = 50;
    vector<pair<int, int>> ris4;
    int count4 = libriSelezionati(prezzi4, soldi4, ris4);
    cout << "\nTest 4: Coppie trovate = " << count4 << "\n";

    // Test 5: array con un solo elemento
    vector<int> prezzi5 = {50};
    double soldi5 = 100;
    vector<pair<int, int>> ris5;
    int count5 = libriSelezionati(prezzi5, soldi5, ris5);
    cout << "\nTest 5: Coppie trovate = " << count5 << "\n";

    return 0;
}