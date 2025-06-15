#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO2

Sia T un albero binario di ricerca contenente n chiavi intere distinte. Sia k una chiave di T. Si consideri il problema
di eliminare da T tutte le chiavi minori di k.

a) Si scriva una procedura in C++ efficiente per risolvere il problema proposto. I parametri della
procedura sono un albero t di tipo Tree e un intero k.
*/

/*#region utilities functions*/
struct Node{
    int key;
    Node* left;
    Node* right;

     Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

typedef Node* PTree;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------

PTree deleteNodesLessThanK(PTree r, int k){
    if(r == nullptr) return nullptr;
    
    if(r->key < k){// Nodo troppo piccolo: scartalo, ma tieni il sottoalbero destro
        return deleteNodesLessThanK(r->right, k);
    } 
    else{ // Nodo valido: tienilo e lavora sul sottoalbero sinistro
        r->left = deleteNodesLessThanK(r->left, k);
    }
    return r;
}


//---------------------------------------------------------------------------------------------------------------------------------------- 
// utils for TEST MAIN
// Stampa inorder (per verifica ordinamento)
void printInOrder(PTree root) {
    if (!root) return;
    printInOrder(root->left);
    cout << root->key << " ";
    printInOrder(root->right);
}

// Libera la memoria
void deleteTree(PTree root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void insert(PTree& root, int key) {
    if (!root) {
        root = new Node(key);
        return;
    }
    if (key < root->key)
        insert(root->left, key);
    else
        insert(root->right, key);
}

//--------------------- MAIN DI TEST -----------------------
int main() {
    PTree root = nullptr;

    // Inseriamo valori in modo da creare un BST con nodi < e >= k
    int values[] = {20, 10, 30, 5, 15, 25, 35, 2, 7, 13, 17};
    for (int v : values) {
        insert(root, v);
    }

    cout << "BST In-Order Prima della cancellazione:\n";
    printInOrder(root);  // Dovrebbe stampare BST ordinato
    cout << "\n";

    int k = 15;
    cout << "\nElimino i nodi con chiave < " << k << "...\n";

    root = deleteNodesLessThanK(root, k);

    cout << "BST In-Order Dopo la cancellazione:\n";
    printInOrder(root);  // Dovrebbero esserci solo chiavi >= 15
    cout << "\n";

    // Pulizia memoria
    deleteTree(root);

    return 0;
}
