#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 3
Scrivere un algoritmo per individuare, all’interno di una stringa x1 . . . xn la lunghezza massima di una sottostringa (di caratteri consecutivi) palindroma. 
Ad esempio, nella stringa colonna la sottostringa palindroma di lunghezza massima è olo, dunque la lunghezza massima è 3. 
Più precisamente:
 
-1) Dare una caratterizzazione ricorsiva della lunghezza massima lung[i, j] di una sottostringa palindroma di xi ...xj;

-2)Costruire un algoritmo di programmazione dinamica con il metodo top-down che permetta di trovare una sottostringa palindroma di lunghezza massima.

-3)Costruire un algoritmo di programmazione dinamica con il metodo bottom-up che permetta di trovare una sottostringa palindroma di lunghezza massima.

-4)Valutare e giustificare la complessità delle soluzioni 2) e 3). Si assuma che le funzioni della libreria string abbiano complessita' costante. 
Quale delle due soluzioni e' preferibile dal punto di vista del tempo di esecuzione? Giustificare la risposta mostrando un esempio.
 
Il prototipo della funzione del punto 2 è: 
string maxPalindroma_TD(const string& s)
 
Il prototipo della funzione del punto 3 è: 
string maxPalindroma_BU(const string& s)

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function
//WIP IN ATTESA DI CONFRONTO CON LA SOLUZIONE CHE VERRA' DATA
//------------------------main function
//((TOP-DOWN)) [***PUNTO 2***]
// Funzione helper: verifica se s[i..j] è palindroma usando memoization
bool isPalindrome(const string& s, int i, int j, vector<vector<int>>& memo_pal) {
    if (i >= j) return true; // sottostringa vuota o singolo carattere
    if (memo_pal[i][j] != -1) return memo_pal[i][j];
    if (s[i] == s[j] && isPalindrome(s, i + 1, j - 1, memo_pal)) {
        memo_pal[i][j] = 1;
    } else {
        memo_pal[i][j] = 0;
    }
    return memo_pal[i][j];
}

// Soluzione Top-Down (memoization)
string maxPalindroma_TD(const string& s) {
    int n = s.size();
    vector<vector<int>> memo_pal(n, vector<int>(n, -1)); // -1 non calcolato
    int maxLen = 1;  // lunghezza massima trovata
    int start = 0;   // indice inizio sottostringa massima

    // Esplora tutte le coppie (i, j)
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            if (isPalindrome(s, i, j, memo_pal) && (j - i + 1 > maxLen)) {
                maxLen = j - i + 1;
                start = i;
            }
        }
    }

    return s.substr(start, maxLen);
}

//((BOTTOM-UP)) [***PUNTO 3***]
string maxPalindroma_BU(const string& s) {
    int n = s.size();
    if (n == 0) return "";

    vector<vector<bool>> pal(n, vector<bool>(n, false));
    int maxLen = 1;
    int start = 0;

    // ogni carattere singolo è palindromo
    for (int i = 0; i < n; ++i) {
        pal[i][i] = true;
    }

    // sottostringhe di lunghezza 2
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            pal[i][i + 1] = true;
            start = i;
            maxLen = 2;
        }
    }

    // lunghezze da 3 a n
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            if (s[i] == s[j] && pal[i + 1][j - 1]) {
                pal[i][j] = true;
                if (len > maxLen) {
                    start = i;
                    maxLen = len;
                }
            }
        }
    }

    return s.substr(start, maxLen);
}

void test(const string& s, const string& expected) {
    string td_result = maxPalindroma_TD(s);
    string bu_result = maxPalindroma_BU(s);

    cout << "Input string:     \"" << s << "\"\n";
    cout << "Expected output:  \"" << expected << "\"\n";
    cout << "Top-Down result:  \"" << td_result << "\"\n";
    cout << "Bottom-Up result: \"" << bu_result << "\"\n";
    cout << "------------------------------------------------------\n";
}

int main() {
    test("", "");
    test("a", "a");
    test("aaaaaa", "aaaaaa");
    test("colonna", "olo");
    test("abacdfgdcabba", "abba");
    test("racecarxyz", "racecar");
    test("madamimadam", "madamimadam");
    test("abcddcbafghhgf", "abcddcba");
    test("abcdefg", "a"); // qualsiasi carattere singolo va bene
    test("forgeeksskeegfor", "geeksskeeg");

    return 0;
}
