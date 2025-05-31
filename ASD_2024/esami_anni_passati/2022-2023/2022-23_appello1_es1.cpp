#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO1
Sia T un BST di dimensione n e sia k una chiave di T tale che T-->root-->key < k. 
Si vuole costruire un nuovo BST T′ contenente tutte e sole le chiavi di T appartenenti all’intervallo [T-->root-->key, k].

a. Si scriva una funzione efficiente in C++ per risolvere il problema. Il prototipo della funzione è:
PTree creaBSTInterval(PTree t, int k)

b. Valutare e giustificare la complessità della funzione.


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
/*void insertIntoBst(PTree& t, int k){
    // Caso base: se l'albero è vuoto, crea un nuovo nodo
    if (t == nullptr) {
        t = new Node(k);
        return;
    }
    
    // Se la chiave è minore, inserisci nel sottoalbero sinistro
    if (k < t->key) {
        insertIntoBst(t->left, k);
    }
    // Se la chiave è maggiore, inserisci nel sottoalbero destro
    else if (k > t->key) {
        insertIntoBst(t->right, k);
    }
    // Se k == t->key, la chiave esiste già (non inseriamo duplicati)
}*/
PTree creaBSTIntervalHelper(PTree t, int minK, int maxK) {
    if (t == nullptr) return nullptr;

    if(t->key <= minK){ // troppo piccolo
        return creaBSTIntervalHelper(t->right, minK, maxK);
    }
    if(t->key >= maxK){ // troppo grande
        return creaBSTIntervalHelper(t->left, minK, maxK);
    }

    // t->key ∈ [minK, maxK] → includi
    PTree newNode = new Node(t->key);
    newNode->left = creaBSTIntervalHelper(t->left, minK, maxK);
    newNode->right = creaBSTIntervalHelper(t->right, minK, maxK);
    return newNode;
}
PTree creaBSTInterval(PTree t, int k){
    if (t == nullptr) return nullptr;
    return creaBSTIntervalHelper(t, t->key, k);
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN

/* --- Funzione per inserimento in BST --- */
PTree insert(PTree root, int key) {
    if (!root) return new Node(key);
    if (key < root->key) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

/* --- Funzione per stampa in-order (per verifica) --- */
void inOrder(PTree root) {
    if (!root) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

/* --- DA IMPLEMENTARE: creaBSTInterval --- */
PTree creaBSTInterval(PTree t, int k);  // implementa questa parte tu!

/* --- Funzione per liberare memoria --- */
void freeTree(PTree root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

/* --- MAIN --- */
int main() {
    /*
        Costruisco questo BST:
                    10
                   /  \
                  5    15
                 / \     \
                2   7     20
    */
    PTree T = nullptr;
    T = insert(T, 10);
    insert(T, 5);
    insert(T, 15);
    insert(T, 2);
    insert(T, 7);
    insert(T, 20);

    int k = 15;  // esempio: voglio i nodi con chiave ∈ [10, 15]

    cout << "In-order originale: ";
    inOrder(T);
    cout << endl;

    PTree Tprime = creaBSTInterval(T, k);

    cout << "In-order intervallo [10, 15]: ";
    inOrder(Tprime);
    cout << endl;

    // Libero memoria
    freeTree(T);
    freeTree(Tprime);

    // ===============================
    // TEST 2: Albero più complesso
    // ===============================

    /*
                  20
                /    \
              10      30
             /  \     / \
            5   15   25  35
           / \    \
          3   7   17

    */
    PTree T2 = nullptr;
    T2 = insert(T2, 20);
    insert(T2, 10);
    insert(T2, 30);
    insert(T2, 5);
    insert(T2, 15);
    insert(T2, 25);
    insert(T2, 35);
    insert(T2, 3);
    insert(T2, 7);
    insert(T2, 17);

    int k2 = 26;  // Intervallo: [20, 26]

    cout << "\n--- TEST 2: Albero complesso ---\n";
    cout << "In-order originale: ";
    inOrder(T2);
    cout << endl;

    PTree T2prime = creaBSTInterval(T2, k2);

    cout << "In-order intervallo [20, 26]: ";
    inOrder(T2prime);
    cout << endl;

    freeTree(T2);
    freeTree(T2prime);

    return 0;
}