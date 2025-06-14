#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO1
Sia T un albero binario. Si vogliono stampare le chiavi di T memorizzate in nodi il cui sottoalbero radicato nel
figlio sinistro contiene più chiavi del sottoalbero radicato nel figlio destro.

a) Si rappresenti un albero binario di ricerca la cui visita in preordine ha come risultato 30, 25, 21, 40,
35, 45. Si mostri quali chiavi verrebbero stampate in base alla condizione sopra descritta.


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
int leftNodesMoreThanRightHelper(PTree r, vector<int>& ret){
    if(r == nullptr) return 0;
    int left = leftNodesMoreThanRightHelper(r->left, ret);
    int right = leftNodesMoreThanRightHelper(r->right, ret);

    if(left > right){
        ret.push_back(r->key);
    }

    return 1+left+right;
}
vector<int> leftNodesMoreThanRight(PTree r){
    vector<int> ret;
    leftNodesMoreThanRightHelper(r, ret);

    return ret;
}

//---------------------------------------------------------------------------------------------------------------------------------------- 
//TEST MAIN

PTree insertBST(PTree root, int key) {
    if (root == nullptr) return new Node(key);
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else
        root->right = insertBST(root->right, key);
    return root;
}

void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

int main() {
    // Test 1 - Esercizio dell'appello
    int test1[] = {30, 25, 21, 40, 35, 45};
    int n1 = sizeof(test1) / sizeof(test1[0]);
    PTree root1 = nullptr;
    for (int i = 0; i < n1; ++i) root1 = insertBST(root1, test1[i]);
    cout << "Test 1: ";
    printVector(leftNodesMoreThanRight(root1));

    // Test 2 - Solo ramo sinistro
    int test2[] = {50, 40, 30, 20};
    int n2 = sizeof(test2) / sizeof(test2[0]);
    PTree root2 = nullptr;
    for (int i = 0; i < n2; ++i) root2 = insertBST(root2, test2[i]);
    cout << "Test 2: ";
    printVector(leftNodesMoreThanRight(root2));

    // Test 3 - Bilanciato perfettamente
    int test3[] = {4, 2, 6, 1, 3, 5, 7};
    int n3 = sizeof(test3) / sizeof(test3[0]);
    PTree root3 = nullptr;
    for (int i = 0; i < n3; ++i) root3 = insertBST(root3, test3[i]);
    cout << "Test 3: ";
    printVector(leftNodesMoreThanRight(root3));

    return 0;
}