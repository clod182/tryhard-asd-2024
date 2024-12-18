#include <iostream>
#include <vector>
using namespace std;
// <>

/* TESTO
Esercizio 3
Dati due vettori contenenti rispettivamente i valori dei nodi tutti DISTINTI ottenuti 
da una visita in ordine anticipato e da una visita in ordine simmetrico di un albero binario, 
si ricostruisca l’albero binario.

Il prototipo della funzione è:

PNode ricostruisci(const vector<int>& va, const vector<int>& vs)
*/

// Struttura del nodo
struct Node {
    int key;
    Node* left;
    Node* right;
};

typedef Node* PNode;

// Dichiarazione della funzione
PNode ricostruisci(const vector<int>& va, const vector<int>& vs);

// Funzione per stampare l'albero in ordine simmetrico (inorder) per verifica
void stampaInOrder(PNode root) {
    if (root == nullptr) return;
    stampaInOrder(root->left);
    cout << root->key << " ";
    stampaInOrder(root->right);
}

// Funzione per stampare l'albero in ordine anticipato (preorder) per verifica
void stampaPreOrder(PNode root) {
    if (root == nullptr) return;
    cout << root->key << " ";
    stampaPreOrder(root->left);
    stampaPreOrder(root->right);
}

/*
Il primo elemento di va (preorder) è sempre la radice.
In vs (inorder), i valori a sinistra della radice appartengono al sottoalbero sinistro, 
mentre quelli a destra appartengono al sottoalbero destro.
*/

PNode ricostruisciAux(const vector<int>& va, int infVa, int supVa, const vector<int>& vs, int infVs, int supVs){

    if(infVa > supVa || infVs > supVs){
        return nullptr;
    }    
    //radice
    PNode newNode = new Node();
    newNode->key = va[infVa];
    newNode->left = nullptr;
    newNode->right = nullptr;

    int i = infVs;
    /*trova la posizione della chiave della radice nel vettore vs */
    while (vs[i] != va[infVa]){
        i++;
    }
    int numsLeft = i - infVs; // Numero di nodi nel sottoalbero sinistro


    newNode->left = ricostruisciAux(va, infVa+1, infVa+numsLeft, vs, infVs, i-1);
    newNode->right = ricostruisciAux(va, infVa+numsLeft+1, supVa, vs, i+1, supVs);

    return newNode;
}

PNode ricostruisci(const vector<int>& va, const vector<int>& vs){
    return ricostruisciAux(va, 0, va.size()-1, vs, 0, vs.size()-1);
}

int main() {
    // Test 1
    vector<int> preorder1 = {3, 9, 20, 15, 7}; // Va
    vector<int> inorder1 = {9, 3, 15, 20, 7};  // Vs

    PNode albero1 = ricostruisci(preorder1, inorder1);

    cout << "Test 1 - Albero ricostruito:" << endl;
    cout << "InOrder: ";
    stampaInOrder(albero1); // Dovrebbe stampare: 9 3 15 20 7
    cout << endl;
    cout << "PreOrder: ";
    stampaPreOrder(albero1); // Dovrebbe stampare: 3 9 20 15 7
    cout << endl;

    // Test 2
    vector<int> preorder2 = {1, 2, 4, 5, 3}; // Va
    vector<int> inorder2 = {4, 2, 5, 1, 3};  // Vs

    PNode albero2 = ricostruisci(preorder2, inorder2);

    cout << "Test 2 - Albero ricostruito:" << endl;
    cout << "InOrder: ";
    stampaInOrder(albero2); // Dovrebbe stampare: 4 2 5 1 3
    cout << endl;
    cout << "PreOrder: ";
    stampaPreOrder(albero2); // Dovrebbe stampare: 1 2 4 5 3
    cout << endl;

    return 0;
}
