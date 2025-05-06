#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue> // Usata solo nel main per testing

using namespace std;

/* TESTO
ESERCIZIO 3
La larghezza di un albero è il numero massimo di nodi che stanno tutti al medesimo livello.
Si fornisca una funzione che calcoli in tempo ottimo la larghezza di un albero generale T di n nodi.
I nodi hanno campi key, left_child e right_sib.
 
Il prototipo della funzione è:
 
int larghezza(PNodeG r)
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
 
Il tipo del nodo è definito come segue:
 
struct NodeG{  
  int key;
  NodeG* left_child;
  NodeG* right_sib;
};
 
typedef NodeG* PNodeG;
*/

/*#region utilities functions*/

struct NodeG {
  int key;
  NodeG* left_child;
  NodeG* right_sib;
};

typedef NodeG* PNodeG;

PNodeG createNode(int key) {
  PNodeG node = new NodeG;
  node->key = key;
  node->left_child = nullptr;
  node->right_sib = nullptr;
  return node;
}

// Funzione di supporto per stampare l’albero livello per livello (solo per debugging)
void printLevelOrder(PNodeG root) {
  if (!root) return;
  queue<PNodeG> q;
  q.push(root);
  while (!q.empty()) {
      int level_size = q.size();
      for (int i = 0; i < level_size; ++i) {
          PNodeG current = q.front(); q.pop();
          cout << current->key << " ";
          PNodeG child = current->left_child;
          while (child) {
              q.push(child);
              child = child->right_sib;
          }
      }
      cout << endl;
  }
}
/*#endregion utilities functions*/

////------------------------helper function------------------------
// Questa funzione ricorsiva aggiorna il vettore "counts" che tiene conto
// del numero di nodi presenti a ciascun livello.
// - "level" indica il livello corrente, partendo da 0 per la radice.
void computeWidthLevels(PNodeG r, int level, vector<int>& counts) {
  if (r == nullptr)
      return;
  
  // Se siamo a un livello non ancora presente nel vettore, ne espandiamo la dimensione.
  if (level >= counts.size())
      counts.resize(level + 1, 0);
  
  // Incrementa il contatore del livello corrente.
  counts[level]++;
  
  // Visita il sottoalbero dei figli (il livello successivo).
  computeWidthLevels(r->left_child, level + 1, counts);
  
  // Visita il fratello a destra, che è allo stesso livello.
  computeWidthLevels(r->right_sib, level, counts);
}

//------------------------main function------------------------
/*
  Funzione: larghezza
  --------------------
  Calcola la larghezza dell'albero (il numero massimo di nodi presenti in un unico livello)
  utilizzando una strategia ricorsiva in Θ(n).
  Il vettore "counts" mantiene il numero di nodi per ogni livello e, al termine della visita,
  si ritorna il massimo.
*/
int larghezza(PNodeG r) {
  vector<int> counts;
  computeWidthLevels(r, 0, counts);
  
  int maxWidth = 0;
  for (int cnt : counts) {
      maxWidth = max(maxWidth, cnt);
  }
  return maxWidth;
}

/*
 Funzione: larghezza_queue
--------------------------
  Calcola la larghezza (massimo numero di nodi presenti in un livello) di un albero generale T
  rappresentato tramite i campi left_child/right_sib.
  
  Algoritmo:
  - Si utilizza una visita in ampiezza (level order traversal) con una coda.
  - Per ogni livello, si conta il numero di nodi presenti (ossia il numero di elementi nella coda all'inizio del ciclo).
  - Per ogni nodo in un livello, si inseriscono in coda tutti i suoi figli: si parte da left_child e si percorrono i right_sib.
  - Alla fine, viene restituito il massimo di questi contatori.
  
  Complessità:
  - Tempo: Θ(n), poiché ogni nodo viene inserito ed estratto dalla coda una volta sola.
*/
int larghezza_queue(PNodeG r) {
    if (r == nullptr)
        return 0;
    
    queue<PNodeG> q;
    q.push(r);
    int best = 0;
    
    // Ciclo finché ci sono nodi da processare
    while (!q.empty()) {
        int levelSize = q.size();  // Numero di nodi nel livello corrente
        best = max(best, levelSize);
        
        // Processa tutti i nodi del livello corrente
        for (int i = 0; i < levelSize; i++) {
            PNodeG current = q.front();
            q.pop();
            
            // Aggiungi alla coda tutti i figli di current
            // I figli sono legati tramite left_child e right_sib.
            PNodeG child = current->left_child;
            while (child) {
                q.push(child);
                child = child->right_sib;
            }
        }
    }
    
    return best;
}


int main() {
  // Costruzione dell’albero generale:
  //           1
  //         / | \
  //        2  3  4
  //       /       \
  //      5         6
  //     / \
  //    7   8

  PNodeG root = createNode(1);
  root->left_child = createNode(2);
  root->left_child->right_sib = createNode(3);
  root->left_child->right_sib->right_sib = createNode(4);

  root->left_child->left_child = createNode(5);
  root->left_child->left_child->left_child = createNode(7);
  root->left_child->left_child->left_child->right_sib = createNode(8);

  root->left_child->right_sib->right_sib->left_child = createNode(6);

  cout << "Stampa per livelli dell’albero:\n";
  printLevelOrder(root);

  cout << "\nLarghezza dell'albero: ";
  cout << larghezza(root) << endl; // Da implementare

  return 0;
}