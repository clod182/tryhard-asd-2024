#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO4
Dato un albero binario i cui nodi x hanno i campi left, right e key, dove key è un numero intero:

a. definire l’altezza di un nodo x;

b. scrivere una funzione efficiente in C o C++ che ritorna il numero di nodi per i quali la chiave
x->key è minore o uguale dell’altezza del nodo. Il prototipo della funzione è:
int lessHeight(PNode r)

c. valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza e
mostrando la loro risoluzione;
*/

/*#region utilities functions*/
struct Node{
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

typedef Node* PNode;

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
int lessHeightHelper(PNode r, int& count){
    if (r == nullptr) return -1;  // Altezza di un nodo nullo = -1

    int lh = lessHeightHelper(r->left, count);
    int rh = lessHeightHelper(r->right, count);

    int height = 1+max(lh, rh);
    if(r->key <= height) count += 1;
    return height;    
}

int lessHeight(PNode r){
    int count = 0;
    return lessHeightHelper(r, count);
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

// --------- FUNZIONE DI SUPPORTO PER STAMPARE L'ALBERO (per debug) ----------
void printTree(PNode root, string indent = "", bool isLeft = true) {
    if (root != nullptr) {
        cout << indent;
        if (isLeft)
            cout << "├──";
        else
            cout << "└──";
        cout << root->key << endl;
        printTree(root->left, indent + (isLeft ? "│   " : "    "), true);
        printTree(root->right, indent + (isLeft ? "│   " : "    "), false);
    }
}

// --------- TEST CASE -----------
int main() {
    // Albero 1: completo
    PNode t1 = new Node(2);
    t1->left = new Node(1);
    t1->right = new Node(3);
    t1->left->left = new Node(0);
    t1->left->right = new Node(1);
    t1->right->right = new Node(1);

    cout << "Albero 1:\n";
    printTree(t1);
    cout << "Nodi con key <= altezza: " << lessHeight(t1) << endl;
    cout << "-------------------------\n";

    // Albero 2: sbilanciato a sinistra
    PNode t2 = new Node(3);
    t2->left = new Node(2);
    t2->left->left = new Node(1);
    t2->left->left->left = new Node(0);

    cout << "Albero 2 (sbilanciato a sinistra):\n";
    printTree(t2);
    cout << "Nodi con key <= altezza: " << lessHeight(t2) << endl;
    cout << "-------------------------\n";

    // Albero 3: chiavi negative
    PNode t3 = new Node(-1);
    t3->left = new Node(-2);
    t3->right = new Node(-3);
    t3->right->right = new Node(-4);

    cout << "Albero 3 (chiavi negative):\n";
    printTree(t3);
    cout << "Nodi con key <= altezza: " << lessHeight(t3) << endl;
    cout << "-------------------------\n";

    // Albero 4: singolo nodo
    PNode t4 = new Node(0);
    cout << "Albero 4 (singolo nodo):\n";
    printTree(t4);
    cout << "Nodi con key <= altezza: " << lessHeight(t4) << endl;
    cout << "-------------------------\n";

    // Albero 5: vuoto
    PNode t5 = nullptr;
    cout << "Albero 5 (vuoto):\n";
    cout << "Nodi con key <= altezza: " << lessHeight(t5) << endl;
    cout << "-------------------------\n";

    return 0;
}