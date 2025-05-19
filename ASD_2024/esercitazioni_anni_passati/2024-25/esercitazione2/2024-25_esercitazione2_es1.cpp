#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 1
Sia T un albero binario di ricerca (BST) avente n nodi con i seguenti campi: key, p, left e right.
Si scriva una funzione efficiente
 
PTree Modify_key(PTree t, PNode x, int key)
che modifica x->key con key solo se t è ancora un BST e ritorna t se t è ancora un BST, nullptr altrimenti.
 
Valutare e giustificare la complessità della funzione.
I tipi PNode e PTree sono definiti nel modo seguente:
 
struct Node{
  int key;
  Node* p;
  Node* left;
  Node* right;
};
 
typedef Node* PNode;
struct Tree{
    PNode root;
};
typedef Tree* PTree;
*/

/*#region utilities functions*/

// Definizione del nodo
struct Node {
  int key;
  Node* p;
  Node* left;
  Node* right;
};

typedef Node* PNode;

// Definizione dell’albero
struct Tree {
  PNode root;
};

typedef Tree* PTree;

// Funzioni di supporto già pronte per il test
PNode createNode(int key) {
  PNode node = new Node{key, nullptr, nullptr, nullptr};
  return node;
}

// Inserimento BST con aggiornamento dei puntatori padre
void bstInsert(PTree t, int key) {
  // Crea un nuovo nodo con la chiave da inserire
  PNode newNode = createNode(key);

  // Caso 1: albero vuoto → il nuovo nodo diventa la radice
  if (t->root == nullptr) {
      t->root = newNode;
      return;
  }

  // Altrimenti, cerca la posizione giusta per inserirlo
  PNode current = t->root;
  PNode parent = nullptr;

  while (current != nullptr) {
      parent = current;
      if (key < current->key) {
          current = current->left;
      } else if (key > current->key) {
          current = current->right;
      } else {
          // Chiave già esistente, non inserire duplicati
          delete newNode;  // libera memoria
          return;
      }
  }

  // Imposta il padre del nuovo nodo
  newNode->p = parent;

  // Inserisce il nuovo nodo come figlio sinistro o destro
  if (key < parent->key) {
      parent->left = newNode;
  } else {
      parent->right = newNode;
  }
}


// Visita in-order per stampare il BST
void printInorder(PNode node) {
    if (node != nullptr) {
        printInorder(node->left);
        cout << node->key << " ";
        printInorder(node->right);
    }
}
/*#endregion utilities functions*/

//------------------------helper function
// Funzione di utilità: verifica se un intero è nell'intervallo (minVal, maxVal)
bool inRange(int val, int minVal, int maxVal) {
  return (val > minVal) && (val < maxVal);
}

// Funzione per ricavare i vincoli min/max imposti dagli antenati di x
void computeAncestorBounds(PNode x, int &minKey, int &maxKey) {
  PNode curr = x;
  PNode parent = x->p;
  while (parent) {
      if (curr == parent->right) {
          // x è nel sottoalbero destro di parent => key > parent->key
          minKey = max(minKey, parent->key);
      } else {
          // x è nel sottoalbero sinistro di parent => key < parent->key
          maxKey = min(maxKey, parent->key);
      }
      curr = parent;
      parent = parent->p;
  }
}

// Ricerca del predecessore (massimo nel sottoalbero sinistro)
PNode findPredecessor(PNode x) {
  if (!x->left) return nullptr;
  PNode pred = x->left;
  while (pred->right)
      pred = pred->right;
  return pred;
}

// Ricerca del successore (minimo nel sottoalbero destro)
PNode findSuccessor(PNode x) {
  if (!x->right) return nullptr;
  PNode succ = x->right;
  while (succ->left)
      succ = succ->left;
  return succ;
}

//------------------------main function
// Funzione richiesta: modifica x->key in "newKey" se l'albero rimane un BST
PTree Modify_key(PTree t, PNode x, int newKey) {
  if (!t || !x) return nullptr;

  // 1) Calcola i limiti imposti dagli antenati
  int minKey = INT_MIN;
  int maxKey = INT_MAX;
  computeAncestorBounds(x, minKey, maxKey);
  // se newKey esce dai limiti dati dagli antenati, termina
  if (!inRange(newKey, minKey, maxKey))
      return nullptr;

  // 2) Verifica sottoalbero sinistro: newKey deve essere > max chiave di x->left
  PNode pred = findPredecessor(x);
  if (pred && !(pred->key < newKey))
      return nullptr;

  // 3) Verifica sottoalbero destro: newKey deve essere < min chiave di x->right
  PNode succ = findSuccessor(x);
  if (succ && !(newKey < succ->key))
      return nullptr;

  // Tutti i controlli sono passati: assegna e restituisci l'albero
  x->key = newKey;
  return t;
}

int main() {
  // Creazione albero
  PTree t = new Tree{nullptr};
  bstInsert(t, 20);
  bstInsert(t, 10);
  bstInsert(t, 30);
  bstInsert(t, 5);
  bstInsert(t, 15);

  cout << "Albero in-order prima della modifica:\n";
  printInorder(t->root);
  cout << "\n";

  // Prendiamo un nodo da modificare: ad esempio il nodo con key = 10
  PNode x = t->root->left; // dovrebbe essere il nodo con key 10

  cout << "Modifico chiave di x da 10 a 25\n";
  PTree modifiedTree = Modify_key(t, x, 25);

  if (modifiedTree == nullptr) {
      cout << "Modifica non valida: l'albero non è più un BST.\n";
  } else {
      cout << "Modifica valida: nuovo albero in-order:\n";
      printInorder(modifiedTree->root);
      cout << "\n";
  }

  // Secondo test: modifica NON valida
  // Reset albero
  t = new Tree{nullptr};
  bstInsert(t, 20);
  bstInsert(t, 10);
  bstInsert(t, 30);
  bstInsert(t, 5);
  bstInsert(t, 15);

  cout << "\nAlbero in-order prima della modifica NON valida:\n";
  printInorder(t->root);
  cout << "\n";

  // x è sempre il nodo con key 10
  x = t->root->left; // 10
  cout << "Provo a modificare x da 10 a 35 (non valido: 35 > 20)\n";

  modifiedTree = Modify_key(t, x, 35);

  if (modifiedTree == nullptr) {
      cout << "Modifica non valida: l'albero non è più un BST.\n";
  } else {
      cout << "Errore: la modifica avrebbe dovuto fallire!\n";
      cout << "Albero risultante:\n";
      printInorder(modifiedTree->root);
      cout << "\n";
  }

  return 0;
}
