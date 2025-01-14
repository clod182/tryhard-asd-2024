#include <iostream>
using namespace std;

/* TESTO ESERCIZIO1  APPELLO2

Siano T1 e T2 due alberi binari di ricerca tali che tutte le chiavi memorizzate in T1 sono minori delle chiavi
memorizzate in T2.

a. Scrivere una funzione in C o in C++ PTree MergeBST(PTree T1, PTree T2) che presi in
input T1 e T2 restituisca un albero binario di ricerca T le cui chiavi sono tutte e sole le chiavi contenute
in T1 e T2.

b. Determinare la complessità della funzione proposta nel caso migliore e nel caso peggiore.

La rappresentazione dell’albero binario di ricerca è tramite puntatori e utilizza i tipi PTree e PNode.
*/

/*#region utilities functions*/
// Nodo dell'albero binario di ricerca
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

typedef Node* PTree;

// Firma della funzione richiesta
PTree MergeBST(PTree T1, PTree T2);

// Funzione per stampare un BST in ordine (utilizzata per il test)
void InOrderTraversal(PTree root) {
    if (root) {
        InOrderTraversal(root->left);
        cout << root->key << " ";
        InOrderTraversal(root->right);
    }
}
/*#endregion utilities functions*/

// ---------------------------------------------------------------------   Funzione richiesta all'esame
PTree MergeBST(PTree T1, PTree T2){
    if(T1 == nullptr && T2 == nullptr) return nullptr;
    else if(T1 == nullptr) return T2;
    else if(T2 == nullptr) return T1;

    PTree nodeBridge = T2;
    while(nodeBridge != nullptr && nodeBridge->left != nullptr) {
        nodeBridge = nodeBridge->left;
    }
    nodeBridge->left = T1;

    return T2;   
}//caso peggior O(n), n nodi dell'albero

// ---------------------------------------------------------------------   Funzione modificato per studio
// Approfondimento, se non avessimo la condizione favorevole T1<T2

// Funzione per inserire una chiave in un BST
PTree Insert(PTree root, int key) {
    if (root == nullptr) {
        return new Node(key);
    }
    if (key < root->key) {
        root->left = Insert(root->left, key);
    } else if (key > root->key) {
        root->right = Insert(root->right, key);
    }
    return root;
}

void traverseAndInsert(PTree rootT, PTree& ret){
    //visita in-order per i BST
    if(rootT!= nullptr) return;

    traverseAndInsert(rootT->left, ret);
    ret = Insert(ret, rootT->key);
    traverseAndInsert(rootT->right, ret);
}

PTree MergeBSTNoCondition(PTree T1, PTree T2){
    if(T1 == nullptr && T2 == nullptr) return nullptr;
    else if(T1 == nullptr) return T2;
    else if(T2 == nullptr) return T1;

    // Creiamo un nuovo albero vuoto
    PTree mergedTree = nullptr;
    
    // Inseriamo tutti i nodi di T1
    traverseAndInsert(T1, mergedTree);
    
    // Inseriamo tutti i nodi di T2
    traverseAndInsert(T2, mergedTree);
    
    return mergedTree;
}//caso peggior O(n^2), n nodi dell'albero

// Main di test
int main() {
    // Costruzione dell'albero T1
    PTree T1 = nullptr;
    T1 = Insert(T1, 10);
    T1 = Insert(T1, 5);
    T1 = Insert(T1, 15);

    // Costruzione dell'albero T2
    PTree T2 = nullptr;
    T2 = Insert(T2, 20);
    T2 = Insert(T2, 25);
    T2 = Insert(T2, 30);

    // Merge dei due alberi
    PTree mergedTree = MergeBST(T1, T2);

    // Stampa dell'albero risultante in ordine
    cout << "Albero risultante dopo il merge (in ordine): ";
    InOrderTraversal(mergedTree);
    cout << endl;

    return 0;
}