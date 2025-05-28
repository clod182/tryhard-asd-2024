#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO3
1. Siano T1 e T2 due alberi binari completi aventi lo stesso numero di nodi che contengono interi e con i seguenti campi:
key, left e right.

a. Si scriva una procedura efficiente che vada a sottrarre ai nodi di T1 i valori dei nodi di T2.
    Il prototipo della procedura è:
    void sottrazione_alberi(PNode r1, PNode r2), dove r1 è la radice di T1 e r2 è la radice di T2.

b. Valutare e giustificare la complessità della procedura, indicando eventuali relazioni di ricorrenza e
    mostrando la loro risoluzione.

c. Specificare la definizione di PNode.

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
void sottrazione_alberi(PNode r1, PNode r2){
    if(r1 == nullptr) return;

    r1->key = r1->key - r2->key;
    sottrazione_alberi(r1->left, r2->left);
    sottrazione_alberi(r1->right, r2->right);
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
// Funzioni di utilità per testing
PNode crea_nodo(int valore) {
    return new Node(valore);
}

void stampa_preorder(PNode root) {
    if (root == nullptr) return;
    
    std::cout << root->key << " ";
    stampa_preorder(root->left);
    stampa_preorder(root->right);
}

int main() {
    // Creazione albero T1:    5
    //                       /   \
    //                      3     8
    //                     / \   / \
    //                    2   4 7   9
    PNode t1 = crea_nodo(5);
    t1->left = crea_nodo(3);
    t1->right = crea_nodo(8);
    t1->left->left = crea_nodo(2);
    t1->left->right = crea_nodo(4);
    t1->right->left = crea_nodo(7);
    t1->right->right = crea_nodo(9);
    
    // Creazione albero T2:    1
    //                       /   \
    //                      1     2
    //                     / \   / \
    //                    1   1 1   2
    PNode t2 = crea_nodo(1);
    t2->left = crea_nodo(1);
    t2->right = crea_nodo(2);
    t2->left->left = crea_nodo(1);
    t2->left->right = crea_nodo(1);
    t2->right->left = crea_nodo(1);
    t2->right->right = crea_nodo(2);
    
    std::cout << "T1 prima della sottrazione: ";
    stampa_preorder(t1);
    std::cout << std::endl;
    
    std::cout << "T2: ";
    stampa_preorder(t2);
    std::cout << std::endl;
    
    // Esecuzione della sottrazione
    sottrazione_alberi(t1, t2);
    
    std::cout << "T1 dopo la sottrazione: ";
    stampa_preorder(t1);
    std::cout << std::endl;
    
    return 0;
}

/*
 * OUTPUT ATTESO:
 * T1 prima della sottrazione: 5 3 2 4 8 7 9
 * T2: 1 1 1 1 2 1 2
 * T1 dopo la sottrazione: 4 2 1 3 6 6 7
 * 
 * (5-1=4, 3-1=2, 2-1=1, 4-1=3, 8-2=6, 7-1=6, 9-2=7)
 */
