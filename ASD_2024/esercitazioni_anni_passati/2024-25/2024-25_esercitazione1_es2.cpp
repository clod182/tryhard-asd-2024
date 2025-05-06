#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 2
Si scriva una funzione efficiente per stabilire se un albero binario è quasi completo, 
cioè tutti i livelli dell’albero sono completamente riempiti,tranne eventualmente l’ultimo che ha le foglie addossate a sinistra.
Calcolare la complessità al caso pessimo dell’algoritmo indicando, e risolvendo, la corrispondente relazione di ricorrenza.
 
La rappresentazione dell’albero binario utilizza esclusivamente i campi left, right e key. Il prototipo della funzione è:
 
bool isQuasiCompleto(PNode r)
 
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
 
Il tipo PNode è così definito:
 
struct Node{  
  int key;
  Node* left;
  Node* right;
};
 
typedef Node* PNode;
*/

/*#region utilities functions*/
struct Node{  
  int key;
  Node* left;
  Node* right;
};
 
typedef Node* PNode;

// Funzione helper per creare un nuovo nodo
PNode createNode(int key) {
  PNode newNode = new Node;
  newNode->key = key;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}

/*#endregion utilities functions*/

////------------------------helper function
// Funzione ausiliaria che restituisce:
// - 0 se l'albero è completo
// - 1 se è quasi completo
// - 2 se non è quasi completo
int auxquasicompleto(PNode u, int& h) {
  int hsx, hdx, risx, risdx;

  if (u == nullptr) {
      h = -1;
      return 0;
  }

  risx = auxquasicompleto(u->left, hsx);
  risdx = auxquasicompleto(u->right, hdx);

  // Calcolo dell'altezza dell'albero radicato in u
  h = (hsx < hdx ? hdx : hsx) + 1;

  // Verifica delle condizioni per quasi completezza
  if ((risx == 0 && risdx == 0 && hdx <= hsx && hsx <= hdx + 1) ||
      (risx == 0 && risdx == 1 && hsx == hdx) ||
      (risx == 1 && risdx == 0 && hsx == hdx + 1)) {
      // L'albero è quasi completo se il sottoalbero sinistro è più alto
      return (hdx < hsx ? 1 : risdx);
  }

  // Altrimenti, non è quasi completo
  return 2;
}

//------------------------main function
bool isQuasiCompleto(PNode r) {
  // Implementare la logica per verificare che:
  // Tutti i livelli, tranne eventualmente l’ultimo, siano completamente pieni.
  // L’ultimo livello abbia le foglie addossate a sinistra.

  int h;
  return auxquasicompleto(r, h) < 2;
}

// Funzione di utilità per stampare il risultato di un test
void printTestResult(PNode tree, const string &testCaseName) {
  cout << testCaseName << ": " << (isQuasiCompleto(tree) ? "Quasi completo" : "NON quasi completo") << endl;
}
int main() {
  // --- Test Case 1: Albero Completo ---
  // Costruzione di un albero binario completo:
  //           1
  //          / \
  //         2   3
  //        / \ / \
  //       4  5 6  7
  PNode completeTree = createNode(1);
  completeTree->left = createNode(2);
  completeTree->right = createNode(3);
  completeTree->left->left = createNode(4);
  completeTree->left->right = createNode(5);
  completeTree->right->left = createNode(6);
  completeTree->right->right = createNode(7);
  
  // --- Test Case 2: Albero Quasi Completo ---
  // Costruzione di un albero quasi completo:
  //           1
  //          / \
  //         2   3
  //        / \  / 
  //       4  5 6   
  // L'ultimo livello non è completamente pieno,
  // ma le foglie sono addossate a sinistra.
  PNode quasiCompleteTree = createNode(1);
  quasiCompleteTree->left = createNode(2);
  quasiCompleteTree->right = createNode(3);
  quasiCompleteTree->left->left = createNode(4);
  quasiCompleteTree->left->right = createNode(5);
  quasiCompleteTree->right->left = createNode(6);

  // --- Test Case 3: Albero NON Quasi Completo ---
  // Costruzione di un albero che NON rispetta la condizione di quasi completezza:
  //           1
  //          / \
  //         2   3
  //        /     \
  //       4       5
  // In questo caso l'ultimo livello non ha le foglie addossate a sinistra.
  PNode notQuasiCompleteTree = createNode(1);
  notQuasiCompleteTree->left = createNode(2);
  notQuasiCompleteTree->right = createNode(3);
  notQuasiCompleteTree->left->left = createNode(4);
  notQuasiCompleteTree->right->right = createNode(5);
  
  // Esecuzione dei test e stampa dei risultati
  printTestResult(completeTree, "Albero Completo");
  printTestResult(quasiCompleteTree, "Albero Quasi Completo");
  printTestResult(notQuasiCompleteTree, "Albero NON Quasi Completo");

  return 0;
}