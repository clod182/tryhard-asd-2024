#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO1
Per iscriversi agli esami gli studenti devono usare il numero di matricola che è rappresentato da una stringa di 7
caratteri con il seguente formato "S######", dove "#" indica una cifra. Scrivere una procedura efficiente per
ordinare in modo decrescente l’elenco degli iscritti a un esame in base al numero di matricola.
Il prototipo della procedura è:
void riordina(vector<string>& arr)
Valutare e giustificare la complessità della procedura proposta.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/


// Funzione che implementa il Counting Sort in modo decrescente
void countingSortByDigit(vector<string>& arr, int digitIndex) {
    vector<int> count(10, 0);  // Contatore per le cifre (0-9)

    // Conta quante volte ogni cifra appare in quella posizione
    for (int i = 0; i < arr.size(); i++) {
        string str = arr[i]; // stringa corrente
        int digit = str[digitIndex] - '0';  // Converte il carattere in cifra
        count[digit]++;
    }

    // Somma cumulativa per preservare la stabilità dell'algo (scorrimento quindi inverso)
    for(int i = count.size() - 2; i >= 0; i--){ // non devo cumulare l'ultimo elemento (il più a destra), perché non ha nessun valore più grande da sommare.
        count[i] += count[i+1];
    }

    vector<string> output(arr.size());  // Output temporaneo
    for (int i = arr.size() - 1; i >= 0; i--) {
        string str = arr[i];
        int digit = str[digitIndex] - '0';
        int pos = count[digit] - 1;  // Posizione corretta nell'output, gli indici partono da 0 quindi serve il -1
        output[pos] = str;
        count[digit]--;
    }

    arr = output;  // Aggiorna l'array originale con l'ordinamento per questa cifra
}

// Funzione principale di ordinamento che ordina le matricole in modo decrescente
void riordina(vector<string>& arr) {
    // Ordinamento per ogni cifra da meno significativa a più significativa
    for (int i = 6; i >= 1; i--) {
        countingSortByDigit(arr, i);  // Passa l'indice delle cifre (1 è la cifra più a destra)
    }
}


int main() {
    // Test 1: Elenco di matricole in ordine casuale
    vector<string> arr1 = {"S1234567", "S9876543", "S3456789", "S4561237", "S2143657"};
    cout << "Test 1 - Prima dell'ordinamento:\n";
    for (const auto& matricola : arr1) {
        cout << matricola << " ";
    }
    cout << endl;

    riordina(arr1); // Chiamata alla funzione di ordinamento

    cout << "Test 1 - Dopo l'ordinamento:\n";
    for (const auto& matricola : arr1) {
        cout << matricola << " ";
    }
    cout << endl;

    // Test 2: Elenco di matricole già ordinato in modo crescente
    vector<string> arr2 = {"S1111111", "S2222222", "S3333333", "S4444444", "S5555555"};
    cout << "Test 2 - Prima dell'ordinamento:\n";
    for (const auto& matricola : arr2) {
        cout << matricola << " ";
    }
    cout << endl;

    riordina(arr2); // Chiamata alla funzione di ordinamento

    cout << "Test 2 - Dopo l'ordinamento:\n";
    for (const auto& matricola : arr2) {
        cout << matricola << " ";
    }
    cout << endl;

    // Test 3: Elenco di matricole già ordinato in modo decrescente
    vector<string> arr3 = {"S5555555", "S4444444", "S3333333", "S2222222", "S1111111"};
    cout << "Test 3 - Prima dell'ordinamento:\n";
    for (const auto& matricola : arr3) {
        cout << matricola << " ";
    }
    cout << endl;

    riordina(arr3); // Chiamata alla funzione di ordinamento

    cout << "Test 3 - Dopo l'ordinamento:\n";
    for (const auto& matricola : arr3) {
        cout << matricola << " ";
    }
    cout << endl;

    // Test 4: Un solo studente
    vector<string> arr4 = {"S1234567"};
    cout << "Test 4 - Prima dell'ordinamento:\n";
    for (const auto& matricola : arr4) {
        cout << matricola << " ";
    }
    cout << endl;

    riordina(arr4); // Chiamata alla funzione di ordinamento

    cout << "Test 4 - Dopo l'ordinamento:\n";
    for (const auto& matricola : arr4) {
        cout << matricola << " ";
    }
    cout << endl;

    // Test 5: Elenco vuoto
    vector<string> arr5 = {};
    cout << "Test 5 - Prima dell'ordinamento:\n";
    for (const auto& matricola : arr5) {
        cout << matricola << " ";
    }
    cout << endl;

    riordina(arr5); // Chiamata alla funzione di ordinamento

    cout << "Test 5 - Dopo l'ordinamento:\n";
    for (const auto& matricola : arr5) {
        cout << matricola << " ";
    }
    cout << endl;

    return 0;
}