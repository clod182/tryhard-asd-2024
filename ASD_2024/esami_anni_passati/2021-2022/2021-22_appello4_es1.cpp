#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO4
Sia T un albero binario i cui nodi x hanno i campi left, right e key, dove key è un numero intero.
L’albero si dice k-compreso, per un certo numero naturale k, se per ogni nodo x la somma delle chiavi
dei nodi dell’albero radicato in x è compresa tra -k e k.

a. Scrivere una funzione efficiente in C++ k_compreso(u,k) che dato in input la radice
u di un albero T e un valore k verifica se T è k-compreso e ritorna 1 se T è k-compreso, 0
altrimenti.

b. Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza e la loro
risoluzione tramite il metodo di sostituzione.

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
int k_compresoHelp(PTree r, int k, bool& violated){
    if(r == nullptr) return 0;
    int left = k_compresoHelp(r->left, k, violated);
    int right = k_compresoHelp(r->right, k, violated);
    int curSum = r->key+left+right;
    if(curSum < -k || curSum > k){
        violated = true;
        return -1;
    }

    return curSum;
}

int k_compreso(PTree r, int k){
    if(r == nullptr) return 0;
    bool violated = false;
    k_compresoHelp(r, k, violated);
    if(violated) return 0;
    else return 1; // albero ok
}


//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
// COSTRUTTORE DI ALBERI DI TEST
PTree buildTestTree1() {
    //       3
    //      / \
    //     1   -2
    PTree root = new Node(3);
    root->left = new Node(1);
    root->right = new Node(-2);
    return root; // Somma = 3 + 1 - 2 = 2 → OK per k >= 2
}

PTree buildTestTree2() {
    //       5
    //      / \
    //    -3   4
    //   /
    // -2
    PTree root = new Node(5);
    root->left = new Node(-3);
    root->left->left = new Node(-2);
    root->right = new Node(4);
    return root; // Somma = 5 - 3 - 2 + 4 = 4 → OK per k >= 4
}

PTree buildTestTree3() {
    //       10
    //      /  \
    //    20    30
    PTree root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    return root; // Somma = 60 → OK solo se k >= 60
}

PTree buildTestTree4() {
    //        0
    //      /   \
    //    -1     1
    //          /
    //        -1
    PTree root = new Node(0);
    root->left = new Node(-1);
    root->right = new Node(1);
    root->right->left = new Node(-1);
    return root; // Somme parziali tutte tra -1 e 0 → OK per k >= 1
}

PTree buildLargeTestTree() {
    // Costruisce un albero completo di altezza 3 (4 livelli, 15 nodi)
    //
    //                 1
    //              /     \
    //            2         3
    //          /  \      /   \
    //         4    5    6     7
    //        / \  / \  / \   / \
    //       8  9 10 11 12 13 14 15
    //
    // Somma dei nodi: 1 + 2 + ... + 15 = 120

    PTree nodes[16]; // indice 0 non usato
    for (int i = 1; i <= 15; ++i)
        nodes[i] = new Node(i);

    for (int i = 1; i <= 7; ++i) {
        nodes[i]->left = nodes[2 * i];
        nodes[i]->right = nodes[2 * i + 1];
    }

    return nodes[1];
}

int main() {
    cout << boolalpha;

    cout << "Test 1 (k = 2): " << (k_compreso(buildTestTree1(), 2) == 1) << endl;
    cout << "Test 2 (k = 4): " << (k_compreso(buildTestTree2(), 4) == 1) << endl;
    cout << "Test 2 (k = 3): " << (k_compreso(buildTestTree2(), 3) == 0) << endl;
    cout << "Test 3 (k = 60): " << (k_compreso(buildTestTree3(), 60) == 1) << endl;
    cout << "Test 3 (k = 59): " << (k_compreso(buildTestTree3(), 59) == 0) << endl;
    cout << "Test 4 (k = 1): " << (k_compreso(buildTestTree4(), 1) == 1) << endl;
    cout << "Test 4 (k = 0): " << (k_compreso(buildTestTree4(), 0) == 0) << endl;
    cout << "Test 5 (albero grande, k = 120): " << (k_compreso(buildLargeTestTree(), 120) == 1) << endl;
    cout << "Test 5 (albero grande, k = 119): " << (k_compreso(buildLargeTestTree(), 119) == 0) << endl;


    return 0;
}