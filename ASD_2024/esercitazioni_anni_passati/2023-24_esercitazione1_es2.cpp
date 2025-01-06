#include <iostream>
#include <cmath>  // Per abs()
#include <algorithm>  // Per max()

using namespace std;
// <>

/* TESTO
Sia T un albero generale i cui nodi hanno campi: key, left-child e right-sib. 
Si scriva una funzione EFFICIENTE che verifichi la seguente proprietà: per ogni nodo u, 
le chiavi dei figli del nodo u devono avere valori non decrescenti considerando i figli 
di u da sinistra verso destra.

Il prototipo della funzione è:
bool isNonDec(PNodeG r)

Restituisce true se la proprietà è verificata altrimenti false.

Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/
struct NodeG {
    int key;
    NodeG* left_child;  // Primo figlio
    NodeG* right_sib;   // Fratello destro
    NodeG(int k) : key(k), left_child(nullptr), right_sib(nullptr) {}
};

typedef NodeG* PNodeG;

PNodeG newNodeG(int key) {
    return new NodeG(key);
}

// Funzione per stampare l'albero ruotato di 90°
void printTree(PNodeG root, int depth = 0) {
    if (root == nullptr) return;

    for (int i = 0; i < depth; i++) cout << "    ";
    cout << root->key << endl;

    printTree(root->left_child, depth + 1);  // Stampa i figli
    printTree(root->right_sib, depth);      // Stampa i fratelli
}

// Prototipo della funzione
bool isNonDec(PNodeG r);

/*#endregion utilities functions*/

// Funzione ausiliaria:


// Implementazione della funzione: da completare
bool isNonDec(PNodeG r) {
    if (r == nullptr) return true;
    
    // Controlla la proprietà per i figli del nodo corrente
    PNodeG child = r->left_child;
    while (child && child->right_sib) {
        if (child->key > child->right_sib->key) {
            return false;
        }
        child = child->right_sib;
    }
    
    // Ricorsione sui figli e fratelli
    return isNonDec(r->left_child) && isNonDec(r->right_sib);
}

int main() {
    // Test 1: Albero vuoto
    PNodeG root1 = nullptr;
    cout << "Test 1 (Albero vuoto):" << endl;
    printTree(root1);
    cout << "Proprietà rispettata? " << (isNonDec(root1) ? "true" : "false") << endl;

    // Test 2: Albero con un solo nodo
    PNodeG root2 = newNodeG(10);
    cout << "\nTest 2 (Un solo nodo):" << endl;
    printTree(root2);
    cout << "Proprietà rispettata? " << (isNonDec(root2) ? "true" : "false") << endl;

    // Test 3: Albero con figli ordinati
    PNodeG root3 = newNodeG(10);
    root3->left_child = newNodeG(5);
    root3->left_child->right_sib = newNodeG(7);
    root3->left_child->right_sib->right_sib = newNodeG(12);
    cout << "\nTest 3 (Figli ordinati):" << endl;
    printTree(root3);
    cout << "Proprietà rispettata? " << (isNonDec(root3) ? "true" : "false") << endl;

    // Test 4: Albero con figli non ordinati
    PNodeG root4 = newNodeG(10);
    root4->left_child = newNodeG(5);
    root4->left_child->right_sib = newNodeG(12);
    root4->left_child->right_sib->right_sib = newNodeG(7);
    cout << "\nTest 4 (Figli non ordinati):" << endl;
    printTree(root4);
    cout << "Proprietà rispettata? " << (isNonDec(root4) ? "true" : "false") << endl;

    // Test 5: Albero complesso
    PNodeG root5 = newNodeG(10);
    root5->left_child = newNodeG(5);
    root5->left_child->right_sib = newNodeG(7);
    root5->left_child->right_sib->right_sib = newNodeG(9);
    root5->left_child->left_child = newNodeG(2);
    root5->left_child->left_child->right_sib = newNodeG(4);
    root5->left_child->left_child->right_sib->right_sib = newNodeG(8);
    cout << "\nTest 5 (Albero complesso):" << endl;
    printTree(root5);
    cout << "Proprietà rispettata? " << (isNonDec(root5) ? "true" : "false") << endl;

    return 0;
}
