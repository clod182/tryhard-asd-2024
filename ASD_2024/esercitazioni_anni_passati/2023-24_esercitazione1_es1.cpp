#include <iostream>
#include <cmath>  // Per abs()
#include <algorithm>  // Per max()

using namespace std;
// <>

/*
Un albero binario si dice t-bilanciato se per ogni suo nodo vale la proprietà: 
le altezze dei sottoalberi radicati nei suoi figli differiscono per al più t unità.

Dato un albero binario, scrivere una funzione EFFICIENTE che restituisca il minimo valore t per cui l'albero risulti t-bilanciato.
Discutere la complessità della soluzione trovata.
*/

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

typedef Node* PNode;

// Prototipo della funzione
int tBil(PNode u);

// Funzione per stampare l'albero ruotato di 90°
void printTree(PNode root, int space = 0, int height = 10) {
    if (root == nullptr) return;

    space += height;  // Incrementa lo spazio per il prossimo livello
    printTree(root->right, space);  // Stampa il sottoalbero destro
    
    cout << endl;
    for (int i = height; i < space; i++) cout << " ";  // Spazi per allineare i nodi
    cout << root->key << "\n";

    printTree(root->left, space);  // Stampa il sottoalbero sinistro
}

// Funzione ausiliaria: calcola altezza e aggiorna il massimo sbilanciamento t
int altezzaENodo(PNode u, int &t) {
    if(u == nullptr) return 0; 

    int hLeft = altezzaENodo(u ->left, t);
    int hRight = altezzaENodo(u ->right, t);

    // Aggiorna il valore massimo di sbilanciamento (t)
    t = max(t, abs(hLeft - hRight));

    // Restituisce l'altezza del nodo corrente
    return 1 + max(hLeft, hRight);
}

// Implementazione della funzione: da completare
int tBil(PNode u) {
    int ret = 0; 
    altezzaENodo(u, ret);

    return ret;
}

// Funzione di supporto per creare un nuovo nodo
PNode newNode(int key) {
    return new Node(key);
}


int main() {
    // Test 1: Albero vuoto
    PNode root1 = nullptr;
    cout << "Test 1 (Albero vuoto):" << endl;
    printTree(root1);
    cout << "t = " << tBil(root1) << endl;

    // Test 2: Albero con un solo nodo
    PNode root2 = newNode(10);
    cout << "\nTest 2 (Un solo nodo):" << endl;
    printTree(root2);
    cout << "t = " << tBil(root2) << endl;

    // Test 3: Albero bilanciato con 3 livelli
    PNode root3 = newNode(1);
    root3->left = newNode(2);
    root3->right = newNode(3);
    root3->left->left = newNode(4);
    root3->left->right = newNode(5);
    root3->right->left = newNode(6);
    root3->right->right = newNode(7);
    cout << "\nTest 3 (Albero bilanciato):" << endl;
    printTree(root3);
    cout << "t = " << tBil(root3) << endl;

    // Test 4: Albero sbilanciato
    PNode root4 = newNode(1);
    root4->left = newNode(2);
    root4->left->left = newNode(3);
    root4->left->left->left = newNode(4);
    cout << "\nTest 4 (Albero sbilanciato):" << endl;
    printTree(root4);
    cout << "t = " << tBil(root4) << endl;

    // Test 5: Albero con differenze di altezza nei figli
    PNode root5 = newNode(1);
    root5->left = newNode(2);
    root5->right = newNode(3);
    root5->left->left = newNode(4);
    root5->left->right = newNode(5);
    root5->left->left->left = newNode(6);
    cout << "\nTest 5 (Albero con sbilanciamento moderato):" << endl;
    printTree(root5);
    cout << "t = " << tBil(root5) << endl;

    return 0;
}
