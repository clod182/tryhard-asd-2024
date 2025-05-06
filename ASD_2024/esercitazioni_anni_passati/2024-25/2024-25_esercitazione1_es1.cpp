#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

/* TESTO
ESERCIZIO 1
Si consideri un albero ternario completo in cui ogni nodo ha i seguenti campi: (i) key chiave intera, (ii) fruitful valore booleano, 
(iii) left puntatore al figlio sinistro, (iv) center puntatore al figlio centrale, (v) right puntatore al figlio destro.
 
---1) Si scriva una procedura efficiente in C++ che assegni True al campo fruitful del nodo se e solo se la somma delle chiavi dei nodi 
  di ciascuno dei sottoalberi radicati nei figli è maggiore di una costante k fornita in input.
  Il prototipo della procedura è: 
  void set_fruitful(PTNode r, int k)

---2)Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della procedura, 
  indicando eventuali relazioni di ricorrenza e mostrando la loro risoluzione.
  Il tipo PTNode è così definito:
 
struct TNode{
  int key;
  bool fruitful;
  TNode* left;
  TNode* center;
  TNode* right;
};
*/

/*#region utilities functions*/
struct TNode {
    int key;
    bool fruitful;
    TNode* left;
    TNode* center;
    TNode* right;
};

typedef TNode* PTNode;

// Funzione helper per creare un nuovo nodo
PTNode createNode(int key) {
    PTNode newNode = new TNode;
    newNode->key = key;
    newNode->fruitful = false; // di default false
    newNode->left = nullptr;
    newNode->center = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Funzione helper per stampare l'albero in pre-ordine
void printPreOrder(PTNode root) {
    if (!root) return;
    cout << "Nodo key: " << root->key 
         << " - fruitful: " << (root->fruitful ? "true" : "false") << endl;
    printPreOrder(root->left);
    printPreOrder(root->center);
    printPreOrder(root->right);
}

// Funzione helper per liberare la memoria occupata dall'albero
void freeTree(PTNode root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->center);
    freeTree(root->right);
    delete root;
}
/*#endregion utilities functions*/

////------------------------helper function
int processSubtree(PTNode r, int k) {
  if(r == nullptr) return 0;
  
  // Calcola la somma per ciascun sottoalbero figlio
  int leftSum = processSubtree(r->left, k);
  int centerSum = processSubtree(r->center, k);
  int rightSum = processSubtree(r->right, k);
  
  r->fruitful = (leftSum > k) && (centerSum > k) && (rightSum > k);
  
  // Ritorna la somma totale includendo il nodo corrente
  return r->key + leftSum + centerSum + rightSum;
}

//------------------------main function
void set_fruitful(PTNode r, int k) {
  processSubtree(r, k);
}

int main() {    
    // Albero completo con 3 livelli.
    PTNode root = createNode(10);
    root->left = createNode(5);
    root->center = createNode(7);
    root->right = createNode(3);
     
    // Secondo livello: figli dei nodi del primo livello.
    root->left->left = createNode(2);
    root->left->center = createNode(3);
    root->left->right = createNode(4);
    
    root->center->left = createNode(1);
    root->center->center = createNode(2);
    root->center->right = createNode(3);
    
    root->right->left = createNode(6);
    root->right->center = createNode(5);
    root->right->right = createNode(4);
    
    int k = 10;
    cout << "Chiamo la procedura set_fruitful con k = " << k << endl;
    set_fruitful(root, k);
    
    cout << "\nStampa dell'albero in pre-ordine dopo l'elaborazione:\n";
    printPreOrder(root);    
    freeTree(root);

    return 0;
}