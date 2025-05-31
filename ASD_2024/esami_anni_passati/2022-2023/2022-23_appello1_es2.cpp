#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO1
Scrivere un algoritmo che date due sequenze X e Y, rispettivamente di m e n caratteri, restituisca la lunghezza di
una sottosequenza di lunghezza massima comune a X e Y (LCS). Più precisamente:

a. dare una caratterizzazione ricorsiva della lunghezza di una LCS, definendo lung[i, j] come la lunghezza
di una LCS delle sequenze Xi e Yj. Si ricordi che Xi è il prefisso di X di lunghezza i e Yj è il prefisso di Y di lunghezza j;

b. tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo top-down che
determina la lunghezza di una LCS;

c. valutare e giustificare la complessità dell’algoritmo.

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------RIC NO OPTIMIZATION
// TC = Θ(2^(m + n))

int lcsLengthHelperNoOpt(string& s1, string& s2, int i, int j){
    if(i<0 || j<0) return 0;

    if(s1[i] == s2[j]) return 1 + lcsLengthHelperNoOpt(s1, s2, i-1, j-1);
    else return max(lcsLengthHelperNoOpt(s1, s2, i, j-1), lcsLengthHelperNoOpt(s1, s2, i-1, j));
}
int lcsLengthNoOpt(string& s1, string& s2){
    int i = s1.size();
    int j = s2.size();

    return lcsLengthHelperNoOpt(s1, s2, i-1, j-1);
}

//----------------------------------------------------------------------------------------------------------------------------------------RIC TOP-DOWN
// TC = Θ(m × n)

int lcsLengthHelper(string& s1, string& s2, int i, int j, vector<vector<int>>& dp) {
    // Caso base: se uno degli indici è negativo, significa che abbiamo raggiunto la fine di una stringa
    // quindi la LCS è 0 (non ci sono più caratteri da confrontare)
    if (i < 0 || j < 0) return 0;

    // Se abbiamo già calcolato dp[i][j], lo ritorniamo subito (memoization)
    if (dp[i][j] != -1) return dp[i][j];

    // Se i caratteri attuali coincidono, aggiungiamo 1 alla LCS
    // e chiamiamo ricorsivamente per i-1, j-1 (caratteri precedenti)
    if (s1[i] == s2[j]) {
        dp[i][j] = 1 + lcsLengthHelper(s1, s2, i - 1, j - 1, dp);
        return dp[i][j];
    } 
    else {
        // Se i caratteri non coincidono, la LCS è il massimo tra:
        // - escludere il carattere corrente di s1 e considerare s1[0..i-1], s2[0..j]
        // - escludere il carattere corrente di s2 e considerare s1[0..i], s2[0..j-1]
        dp[i][j] = max(lcsLengthHelper(s1, s2, i, j - 1, dp), lcsLengthHelper(s1, s2, i - 1, j, dp));
        return dp[i][j];
    }
}

// Funzione principale che inizializza la struttura dp e richiama la funzione helper
int lcsLengthTD(string& s1, string& s2) {
    int i = s1.size();
    int j = s2.size();

    // Creiamo una matrice dp di dimensioni i x j inizializzata a -1,
    // che indica che nessun sottoproblema è stato ancora calcolato
    vector<vector<int>> dp(i, vector<int>(j, -1));
    
    return lcsLengthHelper(s1, s2, i - 1, j - 1, dp);
}

//----------------------------------------------------------------------------------------------------------------------------------------BOTTOM-UP
//  TC = Θ(m × n)

int lcsLength(string& s1, string& s2) {
    int m = s1.size(); 
    int n = s2.size();

    // Creiamo una matrice dp di dimensioni (m+1) x (n+1)
    // dp[i][j] rappresenta la lunghezza della LCS delle sottostringhe
    // s1[0..i-1] e s2[0..j-1]
    // Inizializziamo tutto a 0: le sottostringhe vuote hanno LCS 0
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

    // Iteriamo su ogni sottostringa di s1 (da 1 a m)
    for (int i = 1; i <= m; ++i) {
        // Iteriamo su ogni sottostringa di s2 (da 1 a n)
        for (int j = 1; j <= n; ++j) {
            // Se i caratteri attuali coincidono, significa che la LCS cresce di 1 rispetto alle sottostringhe precedenti
            if (s1[i-1] == s2[j-1]) {
                // Prendiamo il risultato precedente in diagonale (i-1, j-1) e aggiungiamo 1
                dp[i][j] = 1 + dp[i-1][j-1];
            } else {
                // Se i caratteri sono diversi, la LCS è il massimo tra:
                // - escludere l'ultimo carattere di s1 (dp[i-1][j])
                // - escludere l'ultimo carattere di s2 (dp[i][j-1])
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    // Alla fine, dp[m][n] contiene la lunghezza della LCS tra le due stringhe complete
    return dp[m][n];
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

int main() {
    {
        std::string X = "ABCBDAB";
        std::string Y = "BDCABA";
        int expected = 4; // LCS: BCBA, BDAB, BCAB, etc.
        int result = lcsLength(X, Y);
        std::cout << "Test 1 - Expected: " << expected << ", Got: " << result << "\n";
        assert(result == expected);
    }

    {
        std::string X = "AGGTAB";
        std::string Y = "GXTXAYB";
        int expected = 4; // LCS: GTAB
        int result = lcsLength(X, Y);
        std::cout << "Test 2 - Expected: " << expected << ", Got: " << result << "\n";
        assert(result == expected);
    }

    {
        std::string X = "AAAA";
        std::string Y = "AA";
        int expected = 2; // LCS: AA
        int result = lcsLength(X, Y);
        std::cout << "Test 3 - Expected: " << expected << ", Got: " << result << "\n";
        assert(result == expected);
    }

    {
        std::string X = "ABC";
        std::string Y = "DEF";
        int expected = 0; // No common subsequence
        int result = lcsLength(X, Y);
        std::cout << "Test 4 - Expected: " << expected << ", Got: " << result << "\n";
        assert(result == expected);
    }

    {
        std::string X = "";
        std::string Y = "ABC";
        int expected = 0; // Empty string
        int result = lcsLength(X, Y);
        std::cout << "Test 5 - Expected: " << expected << ", Got: " << result << "\n";
        assert(result == expected);
    }

    std::cout << "All tests passed successfully.\n";
    return 0;
}