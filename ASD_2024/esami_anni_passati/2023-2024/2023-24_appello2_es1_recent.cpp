#include <iostream>
#include <vector>
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
PTree MergeBSTSmart(PTree T1, PTree T2){
    if(T1 == nullptr && T2 == nullptr) return nullptr;
    if(T1 == nullptr && T2 != nullptr) return T2;
    if(T1 != nullptr && T2 == nullptr) return T1;

    PTree bridgeNode = T2;
    while(bridgeNode->left != nullptr){
        bridgeNode = bridgeNode->left;
    }
    bridgeNode->left = T1;

    return T2;
}
// ---------------------------------------------------------------------   Funzione modificato per studio
PTree Insert(PTree root, int val){
    if(root == nullptr){
        return new Node(val);
    } 

    if(val < root->key){
        root->left = Insert(root->left, val);
    }
    else{
        root->right = Insert(root->right, val);
    }

    return root;
}

// Approfondimento, se non avessimo la condizione favorevole T1<T2
void giveMeOrderedVect(PTree T, vector<int>& vect){
    if(T == nullptr) return;

    giveMeOrderedVect(T->left, vect);
    vect.push_back(T->key);
    giveMeOrderedVect(T->right, vect);
}

PTree buildBalancedBST(vector<int> orderedVect, int i, int j){ // comunque dal testo dell'es non deve per forza essere bilanciato
    if (i > j) return nullptr;

    int mid = i + (j - i) / 2;
    PTree node = new Node(orderedVect[mid]);

    node->left = buildBalancedBST(orderedVect, i, mid - 1);
    node->right = buildBalancedBST(orderedVect, mid + 1, j);

    return node;
}

PTree MergeBST(PTree T1, PTree T2){
    if(T1 == nullptr && T2 == nullptr) return nullptr;
    if(T1 == nullptr && T2 != nullptr) return T2;
    if(T1 != nullptr && T2 == nullptr) return T1;

    vector<int> v1;
    vector<int> v2;
    giveMeOrderedVect(T1, v1);
    giveMeOrderedVect(T2, v2);

    int i1 = 0, i2 = 0;
    vector<int> orderedVect;
    while(i1 < v1.size() && i2 < v2.size()){
        if(v1[i1] < v2[i2]){
            orderedVect.push_back(v1[i1]);
            i1 +=1;
        }
        else{
            orderedVect.push_back(v2[i2]);
            i2 +=1;
        }
    }
    while(i1 < v1.size()){
        orderedVect.push_back(v1[i1]);
        i1 +=1;
    }
    while(i2 < v2.size()){
        orderedVect.push_back(v2[i2]);
        i2 +=1;
    }     

    return buildBalancedBST(orderedVect, 0, orderedVect.size()-1);
}


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