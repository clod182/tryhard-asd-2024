#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
// <>

/* TESTO
ESERCIZIO 2
Sia dato un albero binario di ricerca t con n nodi e chiavi naturali. Si scriva una funzione EFFICENTE che modifichi t in modo che 
contenga tutte e sole le chiavi pari di t. La soluzione deve essere in loco.
 
Il prototipo della funzione è: 
void BSTpari(PTree t)
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
typedef PTree* PTree;
 
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

// Funzione per rimuovere un nodo dall'albero
PNode removeNode(PNode root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->left = removeNode(root->left, key);
    } else if (key > root->key) {
        root->right = removeNode(root->right, key);
    } else {
        // Nodo trovato
        if (!root->left) {
            PNode temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            PNode temp = root->left;
            delete root;
            return temp;
        } else {
            // Nodo con due figli: trovo il successore in-order
            PNode temp = root->right;
            while (temp->left) temp = temp->left;

            root->key = temp->key;
            root->right = removeNode(root->right, temp->key);
        }
    }
    return root;
}

PNode BSTpariHelper(PNode node) {
    if (!node) return nullptr;

    // Processa i figli ricorsivamente
    node->left = BSTpariHelper(node->left);
    node->right = BSTpariHelper(node->right);

    // Rimuovi nodo dispari
    if (node->key % 2 != 0) {
        PNode temp = removeNode(node, node->key);
        return temp;  // Restituisce il nodo aggiornato
    }

    return node;
}

// Funzione per modificare l'albero, lasciando solo i nodi con chiavi pari
void BSTpari(PTree t) {
    if(t == nullptr || t->root == nullptr) return;
    t->root = BSTpariHelper(t->root);
}

int main() {
    // Esempio di albero
    int keys[] = {10, 15, 5, 2, 8, 12, 18};
    int n = sizeof(keys) / sizeof(keys[0]);

    PTree tree = createBST(keys, n);

    cout << "Albero originale (in-order): ";
    inorderTraversal(tree->root);
    cout << endl;

    // Modifico l'albero per contenere solo chiavi pari
    BSTpari(tree);

    cout << "Albero modificato (in-order, solo chiavi pari): ";
    inorderTraversal(tree->root);
    cout << endl;

    return 0;
}