#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 2
Per iscriversi agli esami gli studenti devono usare il numero di matricola che è rappresentato da una stringa di 7 caratteri 
con il seguente formato ”S######”, dove ”#” indica una cifra. 
Scrivere una procedura efficiente per ordinare in modo decrescente l’elenco degli iscritti a un esame in base al numero di matricola.

Il prototipo della procedura è:
void riordina(vector<string>& arr)
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function

//------------------------main function
// Counting sort stabile per una cifra specifica (radix)
void countingSort(vector<string>& arr, int digitIndex) {
   //UNA CIFRA ALLA VOLTA
   
    const int RADIX = 10;
    vector<int> count(RADIX, 0);
    vector<string> output(arr.size());

    // Conta occorrenze in base alla cifra corrente (da destra a sinistra)
    // Prendi la cifra in posizione pos, la converti in int ('7' - '0' = 7) e metti la stringa nel bucket corrispondente.
    for (const string& s : arr) {
        int digit = s[digitIndex] - '0';
        count[digit]++; // Metto nel bucket
    }

    // Costruzione posizione cumulativa in ordine decrescente
    // Diversamente dal counting sort classico (che somma da sinistra), 
    // qui si somma da destra verso sinistra per ottenere le posizioni di partenza in ordine decrescente.
    for (int i = RADIX - 2; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    // Costruzione output stabile in ordine decrescente
    for (int i = arr.size() - 1; i >= 0; i--) {
        int digit = arr[i][digitIndex] - '0';
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    arr = output;
}

void riordina(vector<string>& arr) {
    if (arr.empty()) return;

    // Applichiamo il radix sort sui 6 caratteri numerici (posizioni da 1 a 6)
    for (int i = 6; i >= 1; i--) {  // dalla cifra meno significativa alla più significativa
        countingSort(arr, i);
    }
}


void stampa(const vector<string>& arr) {
    for (const auto& s : arr) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    // Test 1: matricole casuali
    vector<string> test1 = {"S123456", "S654321", "S000001", "S987654"};
    cout << "Test 1 prima: ";
    stampa(test1);
    riordina(test1);
    cout << "Test 1 dopo: ";
    stampa(test1);
    cout << endl;

    // Test 2: matricole già ordinate decrescentemente
    vector<string> test2 = {"S999999", "S888888", "S777777"};
    cout << "Test 2 prima: ";
    stampa(test2);
    riordina(test2);
    cout << "Test 2 dopo: ";
    stampa(test2);
    cout << endl;

    // Test 3: matricole in ordine crescente
    vector<string> test3 = {"S111111", "S222222", "S333333"};
    cout << "Test 3 prima: ";
    stampa(test3);
    riordina(test3);
    cout << "Test 3 dopo: ";
    stampa(test3);
    cout << endl;

    // Test 4: tutte uguali
    vector<string> test4 = {"S123123", "S123123", "S123123"};
    cout << "Test 4 prima: ";
    stampa(test4);
    riordina(test4);
    cout << "Test 4 dopo: ";
    stampa(test4);
    cout << endl;

    // Test 5: vettore vuoto
    vector<string> test5 = {};
    cout << "Test 5 prima: ";
    stampa(test5);
    riordina(test5);
    cout << "Test 5 dopo: ";
    stampa(test5);
    cout << endl;

    return 0;
}
