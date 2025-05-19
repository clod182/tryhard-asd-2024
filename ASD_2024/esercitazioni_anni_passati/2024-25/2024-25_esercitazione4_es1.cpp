#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

/* TESTO
ESERCIZIO 1
Un giovane amante del trekking vuole organizzare la prossima camminata e ha raccolto nel vettore alture l’altitudine di n punti che vorrebbe raggiungere. 
Data l’altitudine del punto in posizione 0 <= i < n nel vettore, il giovane può raggiungere qualsiasi altro punto in posizione i < j < n, 
data una condizione: l’altitudine del punto in posizione j deve essere minore o uguale a quella del punto in posizione i. 
Una sequenza di punti consecutivi forma un percorso, la cui lunghezza è il numero dei punti.
 
Fornire una caratterizzazione ricorsiva della lunghezza l_i di un percorso di lunghezza massima che abbia come ultimo punto x_i;
tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo bottom-up che determina la lunghezza del percorso più lungo percorribile dal giovane.

Il prototipo della funzione è: 
int percorso_piu_lungo(const vector<int>& alture)
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function
int percorso_piu_lungoHelper(const vector<int>& alture, vector<int>& dp, int i){
    if(dp[i] != -1) return dp[i];

    int maxLength = 1; //almeno il punto stesso
    for(int j=0; j<i; j++){
        if(alture[i] <= alture[j]){
            maxLength = max(maxLength, 1+percorso_piu_lungoHelper(alture,dp,j));            
        }
    }

    dp[i] = maxLength;
    return dp[i];
}

//------------------------main function
//TOP DOWN
int percorso_piu_lungo(const vector<int>& alture){
    int n = alture.size();
    if( n== 0) return 0;

    vector<int> dp(n, -1);
    int maxLength = 1;

    // Considera tutti i punti come possibili finali
    for(int i=0; i<n; i++){
        maxLength = max(maxLength, percorso_piu_lungoHelper(alture, dp, i));
    }

    return maxLength;
}

int main() {
    // Test 1: esempio base decrescente
    vector<int> test1 = {1000, 800, 600, 400, 200};
    cout << "Test 1 (decrescente): " << percorso_piu_lungo(test1) << " (atteso: 5)" << endl;
    assert(percorso_piu_lungo(test1) == 5);

    // Test 2: esempio crescente
    vector<int> test2 = {100, 200, 300, 400, 500};
    cout << "Test 2 (crescente): " << percorso_piu_lungo(test2) << " (atteso: 1)" << endl;
    assert(percorso_piu_lungo(test2) == 1);

    // Test 3: valori misti
    vector<int> test3 = {500, 400, 600, 300, 200};
    // Possibile percorso più lungo: 500 -> 400 -> 300 -> 200 (lunghezza 4)
    cout << "Test 3 (misto): " << percorso_piu_lungo(test3) << " (atteso: 4)" << endl;
    assert(percorso_piu_lungo(test3) == 4);

    // Test 4: tutti uguali
    vector<int> test4 = {100, 100, 100, 100};
    cout << "Test 4 (tutti uguali): " << percorso_piu_lungo(test4) << " (atteso: 4)" << endl;
    assert(percorso_piu_lungo(test4) == 4);

    // Test 5: solo uno
    vector<int> test5 = {1200};
    cout << "Test 5 (uno solo): " << percorso_piu_lungo(test5) << " (atteso: 1)" << endl;
    assert(percorso_piu_lungo(test5) == 1);

    // Test 6: vuoto
    vector<int> test6 = {};
    cout << "Test 6 (vuoto): " << percorso_piu_lungo(test6) << " (atteso: 0)" << endl;
    assert(percorso_piu_lungo(test6) == 0);

    // Test 7: alture irregolari
    vector<int> test7 = {300, 400, 250, 260, 240, 230, 220};
    // Percorso più lungo: 300 → 250 → 240 → 230 → 220 → lunghezza 5
    cout << "Test 7 (irregolare): " << percorso_piu_lungo(test7) << " (atteso: 5)" << endl;
    assert(percorso_piu_lungo(test7) == 5);

    cout << "Tutti i test superati correttamente!" << endl;
    return 0;
}