#include <iostream>
#include <vector>
#include <climits>
using namespace std;
// <>

/* TESTO ESERCIZIO1 APPELLO1

Sia T un albero generale i cui nodi contengono interi e hanno campi: key, left-child e right-sib. 
Un nodo u di T è detto intermedio se la somma delle chiavi contenute nei nodi del sottoalbero di cui u è radice 
è uguale alla somma delle chiavi contenute nei nodi sul percorso che collega u alla radice dell'albero (u escluso).

a.Si scriva una funzione efficiente in C o C++ che restituisca il numero di nodi intermedi.

b. Valutare e giustificare la complessità della funzione. 

c. Specificare il linguaggio di programmazione scelto e la definizione di PNodeG.
Il prototipo della funzione è int intermedi (PNodeG u)
*/

/*#region utilities functions*/
struct NodeG {
    int key;
    NodeG* left_child;
    NodeG* right_sibling;
};
typedef NodeG* PNodeG;
/*#endregion utilities functions*/

//----------------------------------------------------------------------------------------------------------------------------------------
int intermedi_helper(PNodeG u, int pathSum, int& count) {
    if (!u) return 0;
    
    int newPathSum = pathSum + u->key;
    int sum1 = intermedi_helper(u->left_child, newPathSum, count);
    int sum2 = intermedi_helper(u->right_sibling, newPathSum, count); // WIP ERRORE CONCETTUALE, PROBABILMENTE deve essere intermedi_helper(u->right_sibling, pathSum, count); 
                                                                      //  perchè i fratelli ereditano solo dai genitori, non anche dai loro fratelli
    int tot = sum1+sum2+u->key;
    // Verifica condizione di "intermedio"
    if (tot == pathSum)
        count++;

    return tot;
}

int intermedi(PNodeG root) {
    int count = 0;
    intermedi_helper(root, 0, count);
    return count;
}

//---------------------------------------------------------------------------------------------------------------------------------------- TEST MAIN
PNodeG createNode(int key) {
    PNodeG newNode = new NodeG;
    newNode->key = key;
    newNode->left_child = nullptr;
    newNode->right_sibling = nullptr;
    return newNode;
}


int main() {
    // Test 1: Albero con un solo nodo (non può essere intermedio)
    {
        PNodeG root = createNode(10);
        std::cout << "Test 1 (1 nodo): " << intermedi(root) << " (atteso: 0)\n";
    }

    // Test 2: Albero semplice con root e un figlio
    {
        PNodeG root = createNode(5);
        root->left_child = createNode(5);
        std::cout << "Test 2 (root 5 -> figlio 5): " << intermedi(root) << " (atteso: 1)\n";
        // nodo figlio ha sottoalbero 5, e somma percorso verso radice = 5 -> OK
    }

    // Test 3: Albero più complesso
    {
        /*
            Struttura:
                     5
                   / | \
                 3  2  4
                /      \
               1        2

            Percorsi:
            - Nodo 3: subtree=4, path=5 → no
            - Nodo 1: subtree=1, path=5+3=8 → no
            - Nodo 2: subtree=2, path=5 → no
            - Nodo 4: subtree=6, path=5 → no
            - Nodo 2 (figlio di 4): subtree=2, path=5+4=9 → no
        */
        PNodeG root = createNode(5);
        PNodeG n3 = createNode(3);
        PNodeG n2a = createNode(2);
        PNodeG n4 = createNode(4);
        root->left_child = n3;
        n3->right_sibling = n2a;
        n2a->right_sibling = n4;

        n3->left_child = createNode(1);
        n4->left_child = createNode(2);

        std::cout << "Test 3 (albero più grande): " << intermedi(root) << " (atteso: 0)\n";
    }

    // Test 4: Nodo intermedio profondo
    {
        /*
            Struttura:
                  10
                 /
               5
              /
             3
            /
           2

           Nodo 2: subtree=2, path=10+5+3=18 → no
           Nodo 3: subtree=5, path=10+5=15 → no
           Nodo 5: subtree=10, path=10 → sì!
        */
        PNodeG root = createNode(10);
        root->left_child = createNode(5);
        root->left_child->left_child = createNode(3);
        root->left_child->left_child->left_child = createNode(2);
        std::cout << "Test 4 (cammino singolo): " << intermedi(root) << " (atteso: 1)\n";
    }

    return 0;
}
