#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO
ESERCIZIO 1
Sia t un BST di dimensione n e sia k una chiave di t tale che t->root->key < k. 
Si vuole costruire un nuovo BST t' contenente tutte e sole le chiavi di t appartenenti all'intervallo [T->root->key, k].

Si scriva una funzione EFFICENTE per risolvere il problema.
Valutare e giustificare la complessità della funzione.
Il prototipo della funzione è:

PTree creaBSTInterval(PTree t, int k))
Dove il tipo PTree è definito nel seguente modo:

struct Node{ 
    int key; Node* p; 
    Node* left; 
    Node* right; 
}; 
typedef Node* PNode; 
struct Tree{ 
    PNode root; 
};
typedef Tree* PTree; 

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
/*#region utilities functions*/

// Struttura del nodo
struct Node {
    int key;
    Node* p;    // Parent
    Node* left; // Left child
    Node* right; // Right child

    Node(int k) : key(k), p(nullptr), left(nullptr), right(nullptr) {}
};

typedef Node* PNode;

struct Tree {
    PNode root;
};

typedef Tree* PTree;

// Funzione per creare un nuovo nodo
PNode newNode(int key) {
    return new Node(key);
}

// Funzione di inserimento in un BST
PNode insert(PNode root, int key) {
    if (!root) return newNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
        root->left->p = root;  // Imposto il parent
    } else if (key > root->key) {
        root->right = insert(root->right, key);
        root->right->p = root;  // Imposto il parent
    }
    return root;
}

// Funzione che costruisce un albero binario di ricerca (BST) da un array di chiavi
PTree createBST(int keys[], int n) {
    PTree tree = new Tree;
    tree->root = nullptr;
    for (int i = 0; i < n; i++) {
        tree->root = insert(tree->root, keys[i]);
    }
    return tree;
}

// Funzione di in-order traversal per stampare l'albero
void inorderTraversal(PNode root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->key << " ";
        inorderTraversal(root->right);
    }
}

/*#endregion utilities functions*/

// Funzione per creare il nuovo BST con chiavi nell'intervallo [root->key, k]
PTree creaBSTInterval(PTree t, int k) {
    PTree newTree = new Tree;
    newTree->root = nullptr;

    // Da implementare: Funzione ricorsiva che esplora l'albero e inserisce le chiavi
    // che sono nell'intervallo [t->root->key, k] nel nuovo albero binario di ricerca.
    
    // Placeholder per la funzione che esplora l'albero.
    
    return newTree;
}

int main() {
    // Esempio di albero
    int keys[] = {5, 3, 7, 2, 4, 6, 8};
    int n = sizeof(keys) / sizeof(keys[0]);

    PTree tree = createBST(keys, n);

    cout << "Albero originale (in-order): ";
    inorderTraversal(tree->root);
    cout << endl;

    int k = 6; // Chiave di intervallo
    PTree newTree = creaBSTInterval(tree, k);

    cout << "Nuovo albero con chiavi nell'intervallo [root->key, k] (in-order): ";
    inorderTraversal(newTree->root);
    cout << endl;

    return 0;
}