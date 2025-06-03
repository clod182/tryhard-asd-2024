#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>
#include <string>
#include <unordered_set>

using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO4
Questa settimana Carlotta ha ricevuto del denaro dai suoi genitori e vuole spenderlo tutto acquistando
libri. Per finire un libro Carlotta impiega una settimana e poiché riceve denaro ogni due settimane, ha
deciso di acquistare due libri, così potrà leggerli fino a quando riceverà altri soldi. Desidera spendere
tutti i soldi così vorrebbe scegliere due libri i cui prezzi sommati sono pari ai soldi che ha ricevuto.
Data la quantità di soldi che Carlotta ha a disposizione e un array contenente i prezzi dei libri (tutti
distinti), restituire le coppie di prezzi di libri che soddisfano la condizione. Le coppie di prezzi devono
contenere prima il prezzo più basso e poi quello più alto.

a. Scrivere una funzione efficiente il cui prototipo è il seguente:
int libriSelezionati(array prezzolibri, double soldi, array ris)
La funzione restituisce la dimensione dell’array ris. Si devono scrivere eventuali
funzioni/procedure ausiliari utilizzate.

b. Valutare e giustificare la complessità della funzione.

*/

/*#region utilities functions*/
// Funzione ausiliaria per il merge
void merge(vector<int>& arr, int left, int mid, int right) {
    // Calcola le dimensioni dei due sottoarray
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Crea array temporanei
    vector<int> leftArr(n1);
    vector<int> rightArr(n2);
    
    // Copia i dati negli array temporanei
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    // Merge dei due array temporanei nell'array originale
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    // Copia gli elementi rimanenti di leftArr, se ce ne sono
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    // Copia gli elementi rimanenti di rightArr, se ce ne sono
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

// Funzione ricorsiva per il mergesort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        // Trova il punto medio per dividere l'array in due metà
        int mid = left + (right - left) / 2;
        
        // Ordina ricorsivamente la prima e la seconda metà
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge delle due metà ordinate
        merge(arr, left, mid, right);
    }
}
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
//========================================================================
// APPROCCIO 1: O(n log n) - ORDINAMENTO + DUE PUNTATORI
//========================================================================

int libriSelezionati(vector<int>& prezzolibri, double soldi, vector<pair<int, int>>& ris) {
    if (prezzolibri.size() < 2) return 0;
    
    // Crea una copia per l'ordinamento (per preservare l'array originale)
    vector<int> prezzi_ordinati = prezzolibri;
    
    // Ordinamento con mergesort implementato manualmente
    mergeSort(prezzi_ordinati, 0, prezzi_ordinati.size() - 1);
    
    int left = 0;
    int right = prezzi_ordinati.size() - 1;
    int count = 0;
    int target = (int)soldi; // Assumiamo che i soldi siano interi per semplicità
    
    while (left < right) {
        int somma = prezzi_ordinati[left] + prezzi_ordinati[right];
        
        if (somma == target) {
            // Trovata una coppia valida
            ris[count] = {prezzi_ordinati[left], prezzi_ordinati[right]};
            count++;
            left++;
            right--;
        }
        else if (somma < target) {
            // Somma troppo piccola, aumenta il puntatore sinistro
            left++;
        }
        else {
            // Somma troppo grande, diminuisci il puntatore destro
            right--;
        }
    }
    
    return count;
} 

//========================================================================
// APPROCCIO 2: O(n) - HASH MAP
//========================================================================

int libriSelezionati_HashMap(vector<int>& prezzolibri, double soldi, vector<pair<int, int>>& ris) {
    if (prezzolibri.size() < 2) return 0;
    
    unordered_set<int> prezzi_visti;
    unordered_set<string> coppie_trovate; // Per evitare duplicati
    int count = 0;
    int target = (int)soldi;
    
    for (int prezzo : prezzolibri) {
        int complemento = target - prezzo;
        
        // Se il complemento esiste nei prezzi già visti
        if (prezzi_visti.find(complemento) != prezzi_visti.end()) {
            // Ordina la coppia (minore, maggiore)
            int minore = min(prezzo, complemento);
            int maggiore = max(prezzo, complemento);
            
            // Crea una chiave univoca per la coppia
            string chiave = to_string(minore) + "," + to_string(maggiore);
            
            // Se non abbiamo già trovato questa coppia
            if (coppie_trovate.find(chiave) == coppie_trovate.end()) {
                ris[count] = {minore, maggiore};
                count++;
                coppie_trovate.insert(chiave);
            }
        }
        
        prezzi_visti.insert(prezzo);
    }
    
    return count;
}


//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
// FUNZIONI DI UTILITÀ PER I TEST

// Stampa un array di prezzi
void printArray(const vector<int>& arr, const string& name) {
    cout << name << ": [";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Stampa le coppie risultato
void printResult(const vector<pair<int, int>>& ris, int count) {
    cout << "Coppie trovate (" << count << "):" << endl;
    if (count == 0) {
        cout << "  Nessuna coppia trovata" << endl;
    } else {
        for (int i = 0; i < count; i++) {
            cout << "  (" << ris[i].first << ", " << ris[i].second << ") -> somma = " 
                 << (ris[i].first + ris[i].second) << endl;
        }
    }
}

// Verifica che una coppia sia corretta
bool isValidPair(int price1, int price2, double soldi) {
    return abs((price1 + price2) - soldi) < 0.01; // Tolleranza per double
}

// Verifica che le coppie siano ordinate correttamente (prezzo minore prima)
bool isPairOrdered(const pair<int, int>& p) {
    return p.first <= p.second;
}

// Verifica che non ci siano duplicati nelle coppie
bool hasDuplicates(const vector<pair<int, int>>& ris, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (ris[i].first == ris[j].first && ris[i].second == ris[j].second) {
                return true;
            }
        }
    }
    return false;
}

// Conta manualmente le coppie valide (per verifica)
int countExpectedPairs(const vector<int>& prezzolibri, double soldi) {
    int count = 0;
    for (size_t i = 0; i < prezzolibri.size(); i++) {
        for (size_t j = i + 1; j < prezzolibri.size(); j++) {
            if (isValidPair(prezzolibri[i], prezzolibri[j], soldi)) {
                count++;
            }
        }
    }
    return count;
}

// Funzione di test principale
void runTest(vector<int> prezzolibri, double soldi, const string& testName) {
    cout << "\n" << string(70, '=') << endl;
    cout << "TEST: " << testName << endl;
    cout << string(70, '=') << endl;
    
    printArray(prezzolibri, "Prezzi libri");
    cout << "Soldi disponibili: " << fixed << setprecision(2) << soldi << endl;
    
    // Calcola risultato atteso
    int expectedCount = countExpectedPairs(prezzolibri, soldi);
    cout << "Coppie attese: " << expectedCount << endl;
    
    // Esegui la funzione
    vector<pair<int, int>> ris(prezzolibri.size()); // Dimensione massima possibile
    int actualCount = libriSelezionati(prezzolibri, soldi, ris);
    
    cout << "\nRisultato ottenuto:" << endl;
    printResult(ris, actualCount);
    
    // Verifica correttezza
    bool isCorrect = true;
    string errors = "";
    
    // Verifica numero di coppie
    if (actualCount != expectedCount) {
        isCorrect = false;
        errors += "- Numero coppie errato (atteso: " + to_string(expectedCount) + 
                  ", ottenuto: " + to_string(actualCount) + ")\n";
    }
    
    // Verifica ogni coppia
    for (int i = 0; i < actualCount; i++) {
        // Verifica somma
        if (!isValidPair(ris[i].first, ris[i].second, soldi)) {
            isCorrect = false;
            errors += "- Coppia (" + to_string(ris[i].first) + ", " + 
                      to_string(ris[i].second) + ") ha somma errata\n";
        }
        
        // Verifica ordinamento
        if (!isPairOrdered(ris[i])) {
            isCorrect = false;
            errors += "- Coppia (" + to_string(ris[i].first) + ", " + 
                      to_string(ris[i].second) + ") non è ordinata correttamente\n";
        }
    }
    
    // Verifica duplicati
    if (hasDuplicates(ris, actualCount)) {
        isCorrect = false;
        errors += "- Trovati duplicati nelle coppie\n";
    }
    
    cout << "\nVerifica:" << endl;
    if (isCorrect) {
        cout << "✓ TEST PASSATO" << endl;
    } else {
        cout << "✗ TEST FALLITO" << endl;
        cout << "Errori trovati:" << endl;
        cout << errors;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------
// MAIN CON VARI TEST

int main() {
    cout << "Testing della funzione libriSelezionati" << endl;
    cout << "=======================================" << endl;
    
    // Test 1: Caso base semplice
    runTest({10, 20, 30, 40}, 50.0, "Caso base - una coppia");
    
    // Test 2: Più coppie possibili
    runTest({5, 10, 15, 20, 25}, 30.0, "Più coppie possibili");
    
    // Test 3: Nessuna coppia possibile
    runTest({10, 20, 30}, 5.0, "Nessuna coppia possibile");
    
    // Test 4: Array con 2 elementi - coppia perfetta
    runTest({15, 35}, 50.0, "Due elementi - coppia perfetta");
    
    // Test 5: Array con 2 elementi - nessuna coppia
    runTest({10, 20}, 50.0, "Due elementi - nessuna coppia");
    
    // Test 6: Tutti i prezzi uguali ai soldi (impossibile fare coppie)
    runTest({25, 25, 25}, 25.0, "Prezzi tutti uguali ai soldi");
    
    // Test 7: Prezzi molto piccoli
    runTest({1, 2, 3, 4, 5}, 7.0, "Prezzi piccoli");
    
    // Test 8: Prezzi grandi
    runTest({100, 200, 300, 400, 500}, 600.0, "Prezzi grandi");
    
    // Test 9: Array con molti elementi
    runTest({1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 20.0, "Array grande");
    
    // Test 10: Caso con decimali nei soldi
    runTest({10, 15, 25, 30}, 40.5, "Soldi con decimali");
    
    // Test 11: Un solo elemento (impossibile fare coppie)
    runTest({50}, 100.0, "Un solo elemento");
    
    // Test 12: Array vuoto
    runTest({}, 50.0, "Array vuoto");
    
    // Test 13: Caso con prezzi consecutivi
    runTest({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 11.0, "Prezzi consecutivi");
    
    // Test 14: Caso particolare - tutti formano coppie
    runTest({1, 9, 2, 8, 3, 7, 4, 6}, 10.0, "Tutti formano coppie");
    
    // Test 15: Prezzi casuali con molte possibilità
    runTest({12, 18, 25, 30, 35, 40, 45, 50}, 65.0, "Caso complesso con tante possibilità");
    
    cout << "\n" << string(70, '=') << endl;
    cout << "TUTTI I TEST COMPLETATI!" << endl;
    cout << "Implementa la funzione libriSelezionati e riesegui per verificare." << endl;
    cout << string(70, '=') << endl;
    
    return 0;
}
