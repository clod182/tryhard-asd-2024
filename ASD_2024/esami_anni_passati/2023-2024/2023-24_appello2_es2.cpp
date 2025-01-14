#include <iostream>
#include <vector>
using namespace std;

/* TESTO ESERCIZIO2  APPELLO2

Un giovane amante del trekking vuole organizzare la prossima camminata e ha raccolto nel vettore alture 
l’altitudine di n punti che vorrebbe raggiungere. 
Dal punto in posizione 0 <= i < n, il giovane può raggiungere qualsiasi altro punto in posizione i < j < n, data una condizione: 
l’altitudine del punto in posizione j deve essere minore o uguale a quella del punto in posizione i.
Una sequenza di punti consecutivi forma un percorso, la cui lunghezza è il numero dei punti.

a. fornire una caratterizzazione ricorsiva della lunghezza li di un percorso di lunghezza massima che abbia
come ultimo punto alture[i];

b. tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo bottom-up che
determina la lunghezza del percorso più lungo percorribile dal giovane.

c. valutare e giustificare la complessità dell’algoritmo.

Il prototipo della funzione è il seguente:
int percorso_piu_lungo(vector<int>& alture)
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

// ---------------------------------------------------------------------   Ricorsione
int percorso_piu_lungoHelper(vector<int>& alture, vector<int>& dp, int i) {
    if(dp[i] != -1) return dp[i];

    int n = alture.size();
    int maxLength = 1;

    for (int j = i + 1; j < n; ++j) {
        if(alture[i] <= alture[j]) {
            maxLength = max(maxLength, 1+percorso_piu_lungoHelper(alture, dp, j));
        }
    }
    
    dp[i] = maxLength;
    return dp[i];
}
int percorso_piu_lungoRic(vector<int>& alture) {
    int n = alture.size();
    vector<int> dp(n, -1); // Vettore per memorizzare i risultati parziali

    int maxLength = 0;
    
    // Calcoliamo la lunghezza massima del percorso per ogni punto i
    for (int i = 0; i < n; ++i) {
        maxLength = max(maxLength, percorso_piu_lungoHelper(alture, dp, i));
    }

    return maxLength;
}

// ---------------------------------------------------------------------   Bottom-up

int percorso_piu_lungoRic(vector<int>& alture) {
    int n = alture.size();
    vector<int> dp(n, -1); // Vettore per memorizzare i risultati parziali

    int maxLength = 0;
    
    // Calcoliamo la lunghezza massima del percorso per ogni punto i
    for (int i = 0; i < n; ++i) {
        maxLength = max(maxLength, percorso_piu_lungoHelper(alture, dp, i));
    }

    return maxLength;
}

int main() {
    // Esempi di test

    /*
    // Caso 1: Vettore di altezze crescente (nessun percorso valido)
    vector<int> alture1 = {1, 2, 3, 4, 5};
    cout << "Test 1 (Crescente): " << percorso_piu_lungoRic(alture1) << endl;

    // Caso 2: Vettore di altezze decrescente (il percorso massimo è l'intero vettore)
    vector<int> alture2 = {5, 4, 3, 2, 1};
    cout << "Test 2 (Decrescente): " << percorso_piu_lungoRic(alture2) << endl;

    // Caso 3: Vettore con altezze miste (alcuni punti possono essere parte del percorso)
    vector<int> alture3 = {1, 3, 2, 4, 1, 5, 0};
    cout << "Test 3 (Misto): " << percorso_piu_lungoRic(alture3) << endl;

    // Caso 4: Vettore con un solo elemento (la lunghezza massima è 1)
    vector<int> alture4 = {3};
    cout << "Test 4 (Singolo): " << percorso_piu_lungoRic(alture4) << endl;

    // Caso 5: Vettore con lunghezza di percorso che include un elemento ripetuto
    vector<int> alture5 = {2, 3, 2, 2, 1};
    cout << "Test 5 (Ripetuto): " << percorso_piu_lungoRic(alture5) << endl;
    */

    // Caso 1: Vettore di altezze crescente (nessun percorso valido)
    vector<int> alture1 = {1, 2, 3, 4, 5};
    cout << "Test 1 (Crescente): " << percorso_piu_lungo(alture1) << endl;

    // Caso 2: Vettore di altezze decrescente (il percorso massimo è l'intero vettore)
    vector<int> alture2 = {5, 4, 3, 2, 1};
    cout << "Test 2 (Decrescente): " << percorso_piu_lungo(alture2) << endl;

    // Caso 3: Vettore con altezze miste (alcuni punti possono essere parte del percorso)
    vector<int> alture3 = {1, 3, 2, 4, 1, 5, 0};
    cout << "Test 3 (Misto): " << percorso_piu_lungo(alture3) << endl;

    // Caso 4: Vettore con un solo elemento (la lunghezza massima è 1)
    vector<int> alture4 = {3};
    cout << "Test 4 (Singolo): " << percorso_piu_lungo(alture4) << endl;

    // Caso 5: Vettore con lunghezza di percorso che include un elemento ripetuto
    vector<int> alture5 = {2, 3, 2, 2, 1};
    cout << "Test 5 (Ripetuto): " << percorso_piu_lungo(alture5) << endl;

    return 0;
}