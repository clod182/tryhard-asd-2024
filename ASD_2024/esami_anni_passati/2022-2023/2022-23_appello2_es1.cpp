#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO2
Sia T un albero binario di ricerca (BST) avente n nodi.

a. Si scriva una funzione efficiente inC++ PTree Modify_key(PTree t, PNode x, int key) che modifica x->key con key e
ritorna t se t è ancora un BST, nullptr altrimenti.

b. Valutare e giustificare la complessità della funzione.

c. Specificare il linguaggio di programmazione scelto e la definizione di PTree e PNode.

*/

/*#region utilities functions*/
struct Node{
    int key;
    Node* left;
    Node* right;
};

typedef Node* PNode;
typedef PNode PTree;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// Funzione ausiliaria: controlla se un albero è BST usando min/max range
bool isBST(PTree t, int minVal, int maxVal) {
    if (!t) return true;
    if (t->key <= minVal || t->key >= maxVal) return false;

    return isBST(t->left, minVal, t->key) &&
           isBST(t->right, t->key, maxVal);
}

// Funzione principale richiesta
PTree Modify_key(PTree t, PNode x, int key) {
    if (!t || !x) return t;

    int originalKey = x->key;  // Salva il valore originale
    x->key = key;              // Modifica temporanea

    if (isBST(t, INT_MIN, INT_MAX)) {
        return t;              // È ancora un BST → ok
    } else {
        x->key = originalKey;  // Ripristina la chiave originale
        return nullptr;        // Violazione BST
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
// Funzione per creare un nuovo nodo
PNode newNode(int key) {
    PNode node = new Node;
    node->key = key;
    node->left = node->right = nullptr;
    return node;
}

// Funzione per stampare l'albero in-order
void printInOrder(PTree root) {
    if (root) {
        printInOrder(root->left);
        std::cout << root->key << " ";
        printInOrder(root->right);
    }
}

int main() {
    // Costruzione dell'albero BST
    /*
            50
           /  \
         30    70
        / \    / \
      20  40  60  80
    */
    PTree root = newNode(50);
    root->left = newNode(30);
    root->right = newNode(70);
    root->left->left = newNode(20);
    root->left->right = newNode(40);
    root->right->left = newNode(60);
    root->right->right = newNode(80);

    std::cout << "Albero BST originale (in-order): ";
    printInOrder(root);
    std::cout << "\n";

    // Test Case 1: Modifica valida (40 -> 35)
    std::cout << "\nTest Case 1: Modifica 40 -> 35\n";
    if (Modify_key(root, root->left->right, 35)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    // Test Case 2: Modifica non valida (35 -> 65)
    std::cout << "\nTest Case 2: Modifica 35 -> 65\n";
    if (Modify_key(root, root->left->right, 65)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    // Test Case 3: Modifica valida (20 -> 25)
    std::cout << "\nTest Case 3: Modifica 20 -> 25\n";
    if (Modify_key(root, root->left->left, 25)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    // Test Case 4: Modifica non valida (25 -> 75)
    std::cout << "\nTest Case 4: Modifica 25 -> 75\n";
    if (Modify_key(root, root->left->left, 75)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    // Test Case 5: Modifica valida (60 -> 65)
    std::cout << "\nTest Case 5: Modifica 60 -> 65\n";
    if (Modify_key(root, root->right->left, 65)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    // Test Case 6: Modifica non valida (65 -> 45)
    std::cout << "\nTest Case 6: Modifica 65 -> 45\n";
    if (Modify_key(root, root->right->left, 45)) {
        std::cout << "Modifica riuscita. Albero in-order: ";
        printInOrder(root);
        std::cout << "\n";
    } else {
        std::cout << "Modifica non valida. Albero non modificato.\n";
    }

    return 0;
}