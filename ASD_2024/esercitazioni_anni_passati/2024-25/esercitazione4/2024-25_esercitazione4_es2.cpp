#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

/* TESTO
ESERCIZIO 2
Si consideri il problema della Longest Common Subsequence: trovare una "longest common subsequence" (LCS) di due sequenze, ovvero, 
date le sequenze X = x1 ... xm e Y = y1 ... yn trovare W = w1 ... wk tale che:
 
-W è sottosquenza di X e Y
-W è di lunghezza massima.

-1) Definire in modo ricorsivo la lunghezza di una soluzione ottima del problema della LCS.

-2) Calcolare la lunghezza di una LCS utilizzando la programmazione dinamica con il metodo bottom-up. 
Si deve ottimizzare l'uso della memoria utilizzando non una tabella di m+1 x n+1 elementi ma un array di dimensione  min(m, n)+1 elementi.

-3)Costruire un algoritmo di programmazione dinamica con il metodo top-down che permetta anche di trovare una longest common subsequence, 
non solo la sua lunghezza. Si deve cercare di minimizzare lo spazio utilizzato (Usare una sola tabella di m+1 x n+1 elementi).
 
Il prototipo della funzione del punto 2 è: 
int lcsOttSpazio(const string& s1, const string& s2)
 
Il prototipo della funzione del punto 3 è: 
string lcs(const string& s1, const string& s2)

*/

/*#region utilities functions*/

/*#endregion utilities functions*/
//------------------------LCS CON APPROCCIO NORMALE MATRICE
//((BOTTOM-UP))
int lcsClassicBottomUp(const string& s1, const string& s2){ //extra per capire meglio, usando una matrice e non un vettore
    int m = s1.size();
    int n = s2.size();

    // Crea matrice (m+1) x (n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for(int i=1; i<=m; i++){ // SI PARTE DA 1
        for(int j=1; j<=n; j++){ // SI PARTE DA 1
            if(s1[i -1 ] == s2[j - 1]){ // attenzione all’indice -1
                dp[i][j] =dp[i-1][j-1] +1;
            }
            else{
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            } 
        }
    }

    // La soluzione sta in dp[m][n]
    return dp[m][n];
}

//------------------------helper function

//------------------------main function
//((TOP-DOWN))
int lcsClassicTopDownRicHelper(const string& s1, const string& s2, vector<vector<int>>& dp, int m, int n){
    // Caso base: una delle due stringhe è vuota
    if (m == 0 || n == 0) return 0;

     // Se già calcolato, ritorna valore memorizzato
    if (dp[m][n] != -1) return dp[m][n];

    if(s1[m-1]==s2[n-1]){
        dp[m][n] = 1 + lcsClassicTopDownRicHelper(s1, s2, dp, m-1, n-1);
    }
    else {
        dp[m][n] = max(lcsClassicTopDownRicHelper(s1, s2, dp, m, n-1), lcsClassicTopDownRicHelper(s1, s2, dp, m-1, n));
    }

    return dp[m][n];
}
int lcsClassicTopDownRic(const string& s1, const string& s2){ //extra per capire meglio, usando una matrice e non un vettore
    int m = s1.size();
    int n = s2.size();

    // Crea matrice (m+1) x (n+1)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    return lcsClassicTopDownRicHelper(s1, s2, dp, m, n);
}

//((BOTTOM-UP SPACE OPTIMIZATION))
int lcsOttSpazio(const string& s1, const string& s2){
    // Identifica le due stringhe in modo che 'shorter' sia la più corta.
    const string& shorter = (s1.size() < s2.size()) ? s1 : s2;
    const string& longer  = (s1.size() < s2.size()) ? s2 : s1;

    int m = shorter.size();
    int n = longer.size();

    // Array monodimensionale di dimensione m+1 (dove m = lunghezza della stringa più corta)
    // dp[j] rappresenta la LCS tra i primi i caratteri di 'longer' e i primi j caratteri di 'shorter'.
    vector<int> dp(m + 1, 0);

    // Variabile temporanea per memorizzare il valore di dp[j] alla riga precedente (dp[i-1][j-1])
    int prev;

    for (int i = 1; i <= n; ++i) {
        // Salviamo il valore della cella dp[0] prima di modificarla.
        prev = 0;
        for (int j = 1; j <= m; ++j) {
            // tmp memorizza il valore corrente di dp[j] prima che venga aggiornato,
            // che ci servirà come "prev" nella prossima iterazione j+1
            int tmp = dp[j];
            if (longer[i - 1] == shorter[j - 1]) {
                // Se i caratteri corrispondono, estendo la LCS trovata finora con +1
                dp[j] = 1 + prev;
            } else {
                // Altrimenti, prendo il massimo tra ignorare il carattere corrente di una o dell'altra stringa
                dp[j] = max(dp[j], dp[j - 1]);
            }
            // Aggiorno prev per la prossima colonna (j+1)
            prev = tmp;
        }
    }

    // dp[m] contiene la lunghezza della LCS tra s1 e s2
    return dp[m];
}

string lcs(const string& s1, const string& s2){
    return "wip";
}


void testLCS(const string& s1, const string& s2, const string& expectedLCS = "") {
    int len = lcsOttSpazio(s1, s2);
    string subseq = lcs(s1, s2);

    cout << "Test:\n";
    cout << "  s1 = \"" << s1 << "\"\n";
    cout << "  s2 = \"" << s2 << "\"\n";
    cout << "  LCS length: " << len << "\n";
    cout << "  LCS: \"" << subseq << "\"\n";

    // Verifica che la lunghezza corrisponda
    assert((int)subseq.length() == len);

    // Verifica che subseq sia effettivamente sottosequenza di s1 e s2
    auto isSubsequence = [](const string& sub, const string& full) {
        int i = 0;
        for (char c : full) {
            if (i < sub.length() && sub[i] == c) ++i;
        }
        return i == sub.length();
    };

    assert(isSubsequence(subseq, s1));
    assert(isSubsequence(subseq, s2));

    // Se è stato specificato un LCS atteso, controlla che sia valido
    if (!expectedLCS.empty()) {
        assert(subseq == expectedLCS);
    }

    cout << "  --> Test passed!\n\n";
}

int main() {
    testLCS("ABCBDAB", "BDCABA"); // Expected LCS length: 4 (e.g., "BDAB", "BCAB", etc.)
    testLCS("AGGTAB", "GXTXAYB"); // Expected LCS length: 4 (e.g., "GTAB")
    testLCS("AAAA", "AA");        // Expected: "AA"
    testLCS("ABCDEF", "FBDAMN");  // Expected: "BD"
    testLCS("", "ABC");           // Expected: ""
    testLCS("ABC", "");           // Expected: ""
    testLCS("", "");              // Expected: ""
    testLCS("ABCDEF", "ABCDEF", "ABCDEF"); // Identica

    return 0;
}
