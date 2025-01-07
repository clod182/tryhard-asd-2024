#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO
Esercizio 5
Nel centro di Preparazione Olimpica Acqua Acetosa "Giulio Onesti" si allenano la nazionale maschile e femminile di sollevamento pesi. 
Purtroppo, anche qui può accadere che i pesi vengano rimessi nei posti sbagliati.
Date n coppie di manubri con pesi distinti, i manubri sono posizionati senza un ordine particolare su due rastrelliere. 
Inizialmente ogni fila ha un numero uguale di manubri. Trattandosi di una palestra professionale ben finanziata, 
c'è spazio infinito alle due estremità di ciascuna rastrelliera per sostenere eventuali pesi aggiuntivi.
Per spostare un manubrio, si può farlo rotolare in uno spazio vicino libero sulla stessa rastrelliera quasi senza sforzo, oppure si può prenderlo, 
sollevarlo e posizionarlo in un altro posto libero; questo richiede forza proporzionale al suo peso.
Qual è il peso più pesante che si deve sollevare per poter mettere pesi identici uno accanto all'altro? 
Si tenga presente che su ciascuna rastrelliera dopo la riorganizzazione potrebbe esserci sistemato un numero diverso di pesi; questo è consentito.

Il prototipo della funzione è:
int PesoMinimo(vector<int> pesi_1, vector<int> pesi_2)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.

Esempio:

input:                       output:
2 1 8 2 8                   2
9 9 4 1 4

input:                       output:
7 7 15 15 2 2 4 4      0
5 5 3 3 9 9 1 1
*/

/*#region utilities functions*/


/*#endregion utilities functions*/

bool solve(vector<int>& v, int w) {
    int target = -1;  // Indica il peso "non abbinato"
    size_t i = 0;
    bool result = true;
    while (i < v.size() && result) {
        int el = v[i];
        if (el <= w) {
            // Se il peso è minore o uguale a w, non facciamo nulla
        } else {
            if (target == -1) {
                // La prima volta che vediamo un peso troppo pesante
                target = el;
            } else {
                if (target != el) {
                    // Se il nuovo peso è diverso dall'ultimo visto
                    result = false;  // Non possiamo risolvere
                } else {
                    // Abbiniamo i pesi
                    target = -1;
                }
            }
        }
        i++;
    }
    // Se non ci sono pesi non abbinati, restituiamo true
    return result && target == -1;
}

int PesoMinimo(vector<int> pesi_1, vector<int> pesi_2) {
    // Troviamo il massimo valore nei due vettori
    int low = 0, high = 0, best;
    
    for (int val : pesi_1)
        if (high < val) high = val;
    for (int val : pesi_2)
        if (high < val) high = val;
    
    best = high;  // Impostiamo il miglior valore iniziale
    
    // Eseguiamo la ricerca binaria
    while (low <= high) {
        int mid = (high + low) / 2;
        bool works = solve(pesi_1, mid) && solve(pesi_2, mid);
        
        if (works) {
            // Se funziona, cerchiamo un peso più basso
            high = mid - 1;
            best = mid;  // Memorizziamo la soluzione migliore
        } else {
            // Altrimenti, cerchiamo un peso più alto
            low = mid + 1;
        }
    }
    
    return best;
}

int main() {
    // Esempio 1
    vector<int> pesi_1 = {5, 1, 3};  // Pesi della prima rastrelliera
    vector<int> pesi_2 = {4, 2, 6};  // Pesi della seconda rastrelliera
    
    cout << "Peso massimo da sollevare: " << PesoMinimo(pesi_1, pesi_2) << endl;
    
    // Esempio 2
    vector<int> pesi_1_2 = {10, 1, 3, 7};  // Pesi della prima rastrelliera
    vector<int> pesi_2_2 = {5, 8, 6, 4};  // Pesi della seconda rastrelliera
    
    cout << "Peso massimo da sollevare: " << PesoMinimo(pesi_1_2, pesi_2_2) << endl;

    return 0;
}