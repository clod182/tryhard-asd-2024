#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO3

Sia T un albero generale i cui nodi hanno campi: key, left-child e right-sib. Scrivere una funzione efficiente in
C o C++ che calcoli il numero di foglie di T e analizzarne la complessità.

*/

/*#region utilities functions*/
struct Node{
    int key;
    Node* left_child;
    Node* right_sib;

     Node(int k) : key(k), left_child(nullptr), right_sib(nullptr) {}
};

typedef Node* PTree;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------

int countNodeInTree(PTree r){
    if(r == nullptr) return 0;
    int leavesInChildren = countNodeInTree(r->left_child);
    int leavesInSiblings = countNodeInTree(r->right_sib);

    if(r->left_child == nullptr)   return 1 + leavesInSiblings;
    else return leavesInChildren + leavesInSiblings;
}


//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN
// Funzione di supporto per creare nodi (per leggibilità)
PTree newNode(int key) {
    return new Node(key);
}

int main() {
    // Test 1: Albero vuoto
    PTree t1 = nullptr;
    cout << "Test 1 (albero vuoto): " << countNodeInTree(t1) << " (atteso: 0)" << endl;

    // Test 2: Un solo nodo
    PTree t2 = newNode(1);
    cout << "Test 2 (un solo nodo): " << countNodeInTree(t2) << " (atteso: 1)" << endl;

    // Test 3: Albero con un figlio e un fratello
    PTree t3 = newNode(1);
    t3->left_child = newNode(2);
    t3->left_child->right_sib = newNode(3);
    cout << "Test 3 (1 nodo con 2 figli): " << countNodeInTree(t3) << " (atteso: 2)" << endl;

    // Test 4: Albero con figli annidati
    PTree t4 = newNode(1);
    t4->left_child = newNode(2);
    t4->left_child->left_child = newNode(4);
    t4->left_child->left_child->right_sib = newNode(5);
    t4->left_child->right_sib = newNode(3);
    cout << "Test 4 (albero più profondo): " << countNodeInTree(t4) << " (atteso: 3)" << endl;

    // Test 5: Albero in cui ogni nodo ha solo fratelli (nessun figlio)
    PTree t5 = newNode(1);
    t5->right_sib = newNode(2);
    t5->right_sib->right_sib = newNode(3);
    cout << "Test 5 (solo fratelli): " << countNodeInTree(t5) << " (atteso: 3)" << endl;

    return 0;
}