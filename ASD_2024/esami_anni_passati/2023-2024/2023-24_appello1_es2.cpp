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
// Prototipi delle funzioni
void riordina(vector<string>& arr);
/*#endregion utilities functions*/


// Funzione che implementa il Counting Sort in modo decrescente
void countingSortByDigit(vector<string>& arr, int digitIndex) {
    vector<int> count(10, 0);  // Contatore per le cifre (0-9)
    vector<string> output(arr.size());

    // Conta quante volte ogni cifra appare in quella posizione
    for (auto& str : arr) {
        int digit = str[digitIndex] - '0';  // Converte il carattere in cifra
        count[digit]++;
    }

    // Modifica il contatore per renderlo cumulativo (per ordinamento stabile)
    for (int i = 8; i >= 0; i--) {  // Vogliamo un ordinamento decrescente
        count[i] += count[i + 1];
    }

    // Costruisci l'array ordinato in base alla cifra attuale
    for (int i = arr.size() - 1; i >= 0; i--) {
        int digit = arr[i][digitIndex] - '0';
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copia l'array ordinato nell'array originale
    arr = output;
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