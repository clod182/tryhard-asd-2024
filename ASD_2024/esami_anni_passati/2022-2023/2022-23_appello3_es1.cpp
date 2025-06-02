#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO3
Sia T un albero generale i cui nodi contengono interi e hanno campi: key, left-child e right-sib.

a. Si scriva una funzione efficiente in C o C++ che verifichi la seguente proprietà: per ogni nodo u, le chiavi
dei figli del nodo u devono avere valori non decrescenti considerando i figli di u da sinistra verso destra. Il
prototipo della funzione è
bool isNonDec(PNodeG r)
Restituisce true se la proprietà è verificata altrimenti false.

b. Valutare e giustificare la complessità della funzione

c. Specificare il linguaggio di programmazione scelto e la definizione di PNodeG.

*/

/*#region utilities functions*/

struct NodeG {
    int key;
    NodeG* left_child;
    NodeG* right_sib;

    NodeG(int k) : key(k), left_child(nullptr), right_sib(nullptr) {}
};

typedef NodeG* PNodeG;

/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
// NB!!: PER LA ESERCITAZIONE ERA STATA DATA UNA SOL "DIVERSA" CHE Gpt e Claude danno come incompleta
/*
//restituisce se u e’ non-decrescente o meno
bool isNonDec(PNodeG r){
    //caso base
    if (r == nullptr)
        return true;
    //c’e’ solo il figlio sinistro: verifica la proprieta’ sul figlio.
    if (r->right_sib == nullptr)
        return isNonDec(r->left_child);
    //verifica la proprieta’ sul figlio e verifica che la chiave rispetti la
    proprieta’.
    return (r->key <= r->right_sib->key) && isNonDec(r->right_sib) && isNonDec(r->left_child);
}
*/


bool isNonDec(PNodeG r) {
    // Caso base: albero vuoto o raggiunta una foglia -> proprietà vacuamente verificata
    if (r == nullptr) return true;

    // --- PRIMO CONTROLLO ---
    // Verifica che i figli diretti del nodo corrente (r) abbiano chiavi in ordine non decrescente
    PNodeG curNode = r->left_child;
    int prevVal = INT_MIN;
    while (curNode) {        
        if (curNode->key < prevVal)
            return false;

        prevVal = curNode->key;
        curNode = curNode->right_sib; // Passa al fratello successivo
    }

    // --- SECONDO CONTROLLO ---
    // Verifica ricorsiva: per ogni figlio, controlla che la proprietà valga nel suo sottoalbero
    curNode = r->left_child;
    while (curNode) {
        if (!isNonDec(curNode))
            return false; // Appena troviamo una violazione in un sottoalbero, terminiamo

        curNode = curNode->right_sib; // Passa al fratello successivo
    }

    // Se tutte le verifiche sono passate, la proprietà è soddisfatta in tutto l'albero
    return true;
}


//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
void addChild(PNodeG parent, PNodeG child) {
    if (!parent->left_child) {
        parent->left_child = child;
    } else {
        PNodeG curr = parent->left_child;
        while (curr->right_sib) {
            curr = curr->right_sib;
        }
        curr->right_sib = child;
    }
}
void printTree(PNodeG r, int depth = 0) {
    if (!r) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << r->key << "\n";
    printTree(r->left_child, depth + 1);
    printTree(r->right_sib, depth);
}
int main() {
    cout << "==== Tree 1 ====\n";
    /*
        10
        ├── 5
        │   ├── 1
        │   ├── 2
        │   └── 2
        ├── 8
        └── 12
    */
    PNodeG root1 = new NodeG(10);
    addChild(root1, new NodeG(5));
    addChild(root1, new NodeG(8));
    addChild(root1, new NodeG(12));

    addChild(root1->left_child, new NodeG(1));
    addChild(root1->left_child, new NodeG(2));
    addChild(root1->left_child, new NodeG(2));

    printTree(root1);
    cout << "Expected: true → Result: " << (isNonDec(root1) ? "true" : "false") << "\n\n";

    cout << "==== Tree 2 ====\n";
    /*
        20
        ├── 10
        └── 5   (violazione: 5 < 10)
    */
    PNodeG root2 = new NodeG(20);
    addChild(root2, new NodeG(10));
    addChild(root2, new NodeG(5));  // violazione

    printTree(root2);
    cout << "Expected: false → Result: " << (isNonDec(root2) ? "true" : "false") << "\n\n";

    cout << "==== Tree 3 (più grande) ====\n";
    /*
        30
        ├── 5
        │   ├── 1
        │   └── 5
        ├── 10
        └── 40
            ├── 41
            └── 50
    */
    PNodeG root3 = new NodeG(30);
    PNodeG c1 = new NodeG(5);
    PNodeG c2 = new NodeG(10);
    PNodeG c3 = new NodeG(40);
    addChild(root3, c1);
    addChild(root3, c2);
    addChild(root3, c3);

    addChild(c1, new NodeG(1));
    addChild(c1, new NodeG(5));

    addChild(c3, new NodeG(41));
    addChild(c3, new NodeG(50));

    printTree(root3);
    cout << "Expected: true → Result: " << (isNonDec(root3) ? "true" : "false") << "\n";

    return 0;
}
