#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>
using namespace std;
// <>

/* TESTO ESERCIZIO2 APPELLO1
Scrivere un algoritmo per individuare, all’interno di una stringa x1 . . . xn la lunghezza massima di una sottostringa
(di caratteri consecutivi) palindroma. Ad esempio, nella stringa colonna la sottostringa palindroma di lunghezza
massima è olo, dunque la lunghezza massima è 3. Più precisamente:

a) dare una caratterizzazione ricorsiva della lunghezza massima lung[i, j] di una sottostringa palindroma
di xi ...xj;

b) tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo top-down che
determina la lunghezza massima;

c) valutare e giustificare la complessità dell’algoritmo

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
//Longest Palindromic Subsequence (LPS)
/*int longestPalindromeSubsequenceHelper(const string& s, vector<vector<int>>& dp, int i, int j) {
    if(i > j){
        return 0;
    }
    if(i == j){
        return 1;
    }

    if(dp[i][j] != -1) return dp[i][j];

    if(s[i] == s[j]){
        dp[i][j] = 2 + longestPalindromeSubsequenceHelper(s, dp, i+1, j-1);
    }
    else {
        dp[i][j] = max(longestPalindromeSubsequenceHelper(s, dp, i+1, j), longestPalindromeSubsequenceHelper(s, dp, i, j-1));
    }

    return dp[i][j];
}

int longestPalindromeSubstr(const string& s) {
    if(s.size() <= 0) return 0;
    int dim = s.size();
    vector<vector<int>> dp(dim, vector<int>(dim, -1));
    return longestPalindromeSubsequenceHelper(s, dp, 0, dim-1);
}*/

//Longest Palindromic Substring
//TOP-DOWN ********************************************************************************************
bool isPalindrome(const string& s, int i, int j, vector<vector<int>>& dp) {
    if(i >= j){
        return true;
    }
    if(dp[i][j] != -1) return dp[i][j];
    if(s[i] == s[j]){
        dp[i][j] = isPalindrome(s, i+1, j-1, dp);
    }
    else dp[i][j] = false;
    return dp[i][j];
}

int longestPalindromeSubstr(const string& s) {
    if(s.size() <= 0) return 0;
    int dim = s.size();
    vector<vector<int>> dp(dim, vector(dim, -1));
    int countMax = 0;
    for (int i = 0; i < dim; ++i) {
        for (int j = i; j < dim; ++j) {
            if(isPalindrome(s, i, j, dp)){
                countMax = max(countMax, j-i+1);
            }
        }
    }
    return countMax;
}
//BOTTOM-UP ********************************************************************************************
int longestPalindromeSubstrBOTTOMUP(const string& s) {
    int n = s.length();
    if (n == 0) return 0;
    
    // dp[i][j] = true se s[i...j] è palindroma
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLength = 1;
    
    // FASE 1: Tutti i caratteri singoli sono palindromi
    for (int i = 0; i < n; i++) {
        dp[i][i] = true;
    }
    
    // FASE 2: Controlla palindromi di lunghezza 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            maxLength = 2;
        }
    }
    
    // FASE 3: Controlla palindromi di lunghezza 3 e oltre
    // CHIAVE: Procediamo per lunghezze crescenti
    for (int length = 3; length <= n; length++) {
        // Scorriamo tutte le possibili sottostringhe di questa lunghezza
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            
            // Condizione per essere palindroma:
            // 1) estremi uguali
            // 2) la parte interna (i+1..j-1) è già palindroma
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                maxLength = length;
            }
        }
    }
    
    return maxLength;
}

//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
int main() {
    assert(longestPalindromeSubstr("colonna") == 3); // "olo"
    assert(longestPalindromeSubstr("banana") == 5);  // "anana"
    assert(longestPalindromeSubstr("abcba") == 5);   // "abcba"
    assert(longestPalindromeSubstr("abacdfgdcaba") == 3); // "aba"
    assert(longestPalindromeSubstr("abcd") == 1);    // ogni singolo char
    assert(longestPalindromeSubstr("") == 0);        // stringa vuota
    assert(longestPalindromeSubstr("a") == 1);       // stringa con 1 solo carattere

    cout << "Tutti i test sono passati con successo ✅" << endl;
    return 0;
}