#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;
// <>

/* TESTO ESERCIZIO 1

Sia arr un array di lunghezza n di numeri naturali positivi (> 0). 
Si consideri il problema di determinare una sottosequenza crescente di lunghezza massima. 
Ad esempio, dato l'array [10, 22, 9, 33, 21, 50, 41, 60, 80], una sottosequenza crescente di lunghezza massima è 
[10, 22, 33, 50, 60, 80], che ha lunghezza 6.

Definire in modo ricorsivo la lunghezza massima di una sottosequenza crescente;
tradurre tale definizione in un algoritmo di programmazione dinamica con il metodo bottom-up che determina 
la lunghezza massima di una sottosequenza crescente;
trasformare l’algoritmo di modo che determini anche una sottosequenza crescente di lunghezza massima;
valutare le complessità degli algoritmi.

I prototipi delle funzioni sono:
int lunglongestIncreasingSubsequence(vector<int>& arr)
vector<int> longestIncreasingSubsequence(vector<int>& arr)

*/

/*#region utilities functions*/

/*#endregion utilities functions*/

int lunglongestIncreasingSubsequence(vector<int>& arr);
vector<int> longestIncreasingSubsequence(vector<int>& arr);

int main() {
    // Test di esempio
    vector<int> arr = {10, 22, 9, 33, 21, 50, 41, 60, 80};
    
    // Testare la lunghezza della LIS
    cout << "Lunghezza della LIS: " << lunglongestIncreasingSubsequence(arr) << endl;

    // Testare la sottosequenza LIS
    vector<int> lis = longestIncreasingSubsequence(arr);
    cout << "Sottosequenza crescente massima: ";
    for (int num : lis) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}