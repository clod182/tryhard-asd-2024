#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 5
Dato un albero di ricerca T, scrivere una funzione efficiente che restituisca il numero di elementi che occorrono una sola volta e analizzarne la complessità.
Il prototipo della funzione è:
int elementiDistinti(const Tree& t))

N.B. Non si possono usare strutture ausiliarie di dimensione O(n) dove n è il numero dei nodi dell’albero e si devono utilizzare le funzioni della classe Tree.
*/

/*#region utilities functions*/
struct Node {
    int key;
    Node* p;
    Node* left;
    Node* right;
};

typedef Node* PNode;
struct Tree {
    PNode root;
};
typedef Tree* PTree;
/*#endregion utilities functions*/

//------------------------helper function
void elementiDistintiHelper(PNode node, int& lastValue, int& runLength, int& distinctCount, bool& firstNode){
    if(node == nullptr) return;

    // Visita sinistro
    elementiDistintiHelper(node->left, lastValue, runLength, distinctCount, firstNode);

    if (firstNode) {
         // Primo nodo visitato in assoluto, non abbiamo lastValue
        lastValue = node->key;
        runLength = 1;
        firstNode = false;
    } else if (node->key == lastValue) {
        // Stessa run (valore ripetuto)
        runLength++;
    } else {
        // Cambio valore → chiudo run precedente
        if (runLength == 1) {
            distinctCount++;
        }
        // Inizio nuova run
        lastValue = node->key;
        runLength = 1;
    }

     // Visita destro
     elementiDistintiHelper(node->right, lastValue, runLength, distinctCount, firstNode);
}


//------------------------main function
int elementiDistinti(PTree t) {
    if (!t || !t->root) return 0;

    int lastValue     = 0;    // valore dell’ultimo nodo in in-order
    int runLength     = 0;    // lunghezza della run corrente
    int distinctCount = 0;    // quante run di lunghezza 1
    bool firstNode    = true; // indica se siamo al primo nodo

    // Scorro tutta la radice in in-order
    elementiDistintiHelper(t->root, lastValue, runLength, distinctCount, firstNode);

    // Al termine, chiudo l’ultima run
    if (runLength == 1)
        distinctCount++;

    return distinctCount;
}

PNode newNode(int key) {
    PNode n = new Node;
    n->key = key;
    n->p = n->left = n->right = nullptr;
    return n;
}

PTree buildExampleTree() {
    // Costruisci manualmente un albero binario di ricerca con alcuni duplicati
    //           5
    //         /   \
    //        3     7
    //       / \     \
    //      2   3     7
    PTree t = new Tree;
    t->root = newNode(5);
    t->root->left = newNode(3);   t->root->left->p = t->root;
    t->root->right = newNode(7);  t->root->right->p = t->root;

    t->root->left->left = newNode(2);   t->root->left->left->p = t->root->left;
    t->root->left->right = newNode(3);  t->root->left->right->p = t->root->left;

    t->root->right->right = newNode(7); t->root->right->right->p = t->root->right;

    return t;
}

int main() {
    PTree t = buildExampleTree();
    int unici = elementiDistinti(t);
    cout << "Numero di elementi distinti che appaiono una sola volta: " << unici << endl;
    return 0;
}
