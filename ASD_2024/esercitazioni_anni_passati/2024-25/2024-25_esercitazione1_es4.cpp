#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue> // Usata solo nel main per testing

using namespace std;

/* TESTO
ESERCIZIO 4
Dato un vettore di n interi, eventualmente ripetuti, ordinati in senso NON crescente, e un intero k, 
definire una funzione occ, di complessità ottima(Θ(log n)), che conta il numero di occorrenze di k in v. Il prototipo della funzione è:
 
int occ(const vector<int>& v, int k)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function------------------------
int occ_start(const vector<int>& v, int k, int start, int end) {
  if (start > end)
      return 0; // valore indicante che k non è presente
  int mid = start + (end - start) / 2;
  if (v[mid] == k) {
      // Verifica se è il primo indice, altrimenti cerca ulteriormente a sinistra
      if (mid == 0 || v[mid - 1] != k)
          return mid;
      else
          return occ_start(v, k, start, mid - 1);
  }
  // confronti per l'ordine non crescente
  if (k > v[mid])
      return occ_start(v, k, start, mid - 1);
  else
      return occ_start(v, k, mid + 1, end);
}

int occ_end(const vector<int>& v, int k, int start, int end) {
  if (start > end)
      return 0; // valore indicante che k non è presente
  int mid = start + (end - start) / 2;
  if (v[mid] == k) {
      // Verifica se è l'ultimo indice, altrimenti cerca ulteriormente a destra
      if (mid == end || v[mid + 1] != k)
          return mid;
      else
          return occ_end(v, k, mid + 1, end);
  }
  // confronti per l'ordine non crescente
  if (k > v[mid])
      return occ_end(v, k, start, mid - 1);
  else
      return occ_end(v, k, mid + 1, end);
}

//------------------------main function------------------------
int occ(const vector<int>& v, int k) {
  int size = v.size();
  if (size <= 0) return 0;

  int start = occ_start(v, k, 0, size);
  int end = occ_end(v, k, 0, size);

  return end-start +1;
}

int main() {
  vector<int> test1 = {9, 9, 8, 8, 8, 7, 6, 5, 5, 5, 3}; // valori ripetuti
  vector<int> test2 = {9, 8, 7, 6, 5, 4, 3, 2, 1};       // valori unici
  vector<int> test3 = {5, 5, 5, 5, 5};                   // tutti uguali
  vector<int> test4 = {};                                // vettore vuoto
  vector<int> test5 = {10, 10, 9, 9, 7, 7, 6, 4, 4};     // test con k non presente

  cout << "Test 1 (k = 5): " << occ(test1, 5) << " (atteso: 3)\n";
  cout << "Test 2 (k = 6): " << occ(test2, 6) << " (atteso: 1)\n";
  cout << "Test 3 (k = 5): " << occ(test3, 5) << " (atteso: 5)\n";
  cout << "Test 4 (k = 1): " << occ(test4, 1) << " (atteso: 0)\n";
  cout << "Test 5 (k = 8): " << occ(test5, 8) << " (atteso: 0)\n";

  return 0;
}