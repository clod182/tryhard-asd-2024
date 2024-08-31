#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <climits>
#include <cassert>

using namespace std;

/*
Un giovane amante del trekking vuole organizzare la prossima camminata e ha raccolto nel vettore alture l'altitudine di n punti che vorrebbe raggiungere. 
Dal punto in posizione 0<= i<n, il giovane può raggiungere qualsiasi altro punto in posizione i<j<n, data una condizione: 
l'altitudine del punto in posizione j deve essere minore o uguale a quella del punto in posizione i. Una sequenza di punti consecutivi forma percorso, 
la cui lunghezza è il numero dei punti.

fornire una caratterizzazione ricorsiva della lunghezza l, di un percorso di lunghezza massima che abbia come ultimo punto alture[i]; 
tradurre tale definizione determina la un algoritmo di programmazione dinamica con il metodo bottom-up che lunghezza del percorso più lungo percorribile dal giovane. 

valutare e giustificare la complessità dell'algoritmo. 

Il prototipo della funzione è il seguente: int percorso_piu lungo (vector<int>& alture)
*/

//---------------------------------------------------------------- MEMONIZATION top-down
int lengthOfLIS_helper(vector<int>& alture, int index, vector<int>& dp) {
    if (index >= alture.size()) {
        return 0;
    }

    if (dp[index] != -1) {
        return dp[index];
    }

    int max_length = 1; // Include il punto corrente

    for (int i = index + 1; i < alture.size(); i++) {
        if (alture[i] > alture[index]) {
            int length = 1 + lengthOfLIS_helper(alture, i, dp);
            max_length = max(max_length, length);
        }
    }

    dp[index] = max_length;
    return max_length;
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, -1);
    int max_length = 0;
    
    for (int i = 0; i < n; i++) {
        max_length = max(max_length, lengthOfLIS_helper(nums, i, dp));
    }
    
    return max_length;   
}


int main() {
    // Test Case 1: Sequenza semplice
    std::vector<int> alture1 = {5, 4, 3, 2, 1};
    int risultato1 = percorso_piu_lungo(alture1);
    std::cout << "Test Case 1: " << risultato1 << " (Expected: 5)" << std::endl;
    assert(risultato1 == 5);

    // Test Case 2: Alture con un solo punto
    std::vector<int> alture2 = {10};
    int risultato2 = percorso_piu_lungo(alture2);
    std::cout << "Test Case 2: " << risultato2 << " (Expected: 1)" << std::endl;
    assert(risultato2 == 1);

    // Test Case 3: Alture non decrescenti
    std::vector<int> alture3 = {1, 2, 3, 4, 5};
    int risultato3 = percorso_piu_lungo(alture3);
    std::cout << "Test Case 3: " << risultato3 << " (Expected: 1)" << std::endl;
    assert(risultato3 == 1);

    // Test Case 4: Alture con valori alternati
    std::vector<int> alture4 = {10, 8, 10, 7, 6, 5};
    int risultato4 = percorso_piu_lungo(alture4);
    std::cout << "Test Case 4: " << risultato4 << " (Expected: 4)" << std::endl;
    assert(risultato4 == 5);

    // Test Case 5: Alture casuali
    std::vector<int> alture5 = {8, 9, 5, 7, 3, 6, 2, 4, 1};
    int risultato5 = percorso_piu_lungo(alture5);
    std::cout << "Test Case 5: " << risultato5 << " (Expected: 5)" << std::endl;
    assert(risultato5 == 5);

    std::cout << "Tutti i test sono stati superati con successo!" << std::endl;
    return 0;
}