#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

/* TESTO
ESERCIZIO 4
Progettare una realizzazione del tipo di dato Albero binario di ricerca. 
Si assuma che ciascun nodo x, anzichè includere l’attributo x->p, che punta al padre di x,
includa x->succ, che punta al successore di x. 
Verrà resa disponibile l’interfaccia della classe da completare assieme all’esercitazione su HackerRank. 
Discutere la complessità in tempo di ciascuna operazione.
*/

/*#region utilities functions*/

/*#endregion utilities functions*/

//------------------------helper function


//------------------------main function
#include "tree.hpp"

// Crea un nuovo nodo con chiave val
PNode createNode(int val) {
    return new Node{val, nullptr, nullptr, nullptr};
}

// Costruttore: inizializza l'albero vuoto
Tree::Tree() {
    root = nullptr;
}

// Funzione ausiliaria per distruggere l'albero (post-order)
void cancella(PNode u) {
    if (u) {
        cancella(u->left);
        cancella(u->right);
        delete u;
    }
}

// Distruttore dell'albero
Tree::~Tree() {
    cancella(root);
}

// Verifica se l'albero è vuoto
bool Tree::is_empty() const {
    return root == nullptr;
}

// Restituisce la radice dell'albero
PNode Tree::radice() const {
    return root;
}

// Restituisce la chiave del nodo u
int Tree::leggiInfo(PNode u) const {
    return u->key;
}

// Restituisce il figlio sinistro di u
PNode Tree::figlioSx(PNode u) const {
    return u->left;
}

// Restituisce il figlio destro di u
PNode Tree::figlioDx(PNode u) const {
    return u->right;
}

// Calcola e restituisce il padre di u (non è memorizzato)
// Restituisce il padre del nodo target (u), senza usare un puntatore al padre.
// Utilizza solo root, left, right e succ.
PNode Tree::padre(PNode target) const {
    // Step 1: Trova il massimo nodo nel sottoalbero radicato in target
    PNode maxInSubtree = target;
    while (maxInSubtree->right != nullptr)
        maxInSubtree = maxInSubtree->right;

    // Step 2: Trova il successore in-order del massimo del sottoalbero
    PNode successorOfMax = maxInSubtree->succ;

    // Step 3: Determina il punto di rientro nel sottoalbero
    // Se il successore non esiste (cioè target è il massimo dell'intero albero),
    // si parte dalla radice. Altrimenti, si parte dal ramo sinistro del successore.
    PNode potentialParent = (successorOfMax == nullptr) ? root : successorOfMax->left;

    // Caso particolare: se il figlio sinistro del successore è proprio target,
    // allora il successore stesso è il padre.
    if (potentialParent == target)
        return successorOfMax;

    // Step 4: Altrimenti, seguiamo il cammino a destra fino a trovare il nodo che ha target come figlio destro.
    while (potentialParent->right != target)
        potentialParent = potentialParent->right;

    return potentialParent;  // Trovato il padre vero
}

// Restituisce il successore in-order di u (memorizzato)
PNode Tree::treesucc(PNode u) const {
    return u->succ;
}

// Restituisce il predecessore in-order del nodo current
PNode Tree::treepred(PNode current) const {
    // Caso 1: se esiste un sottoalbero sinistro, il predecessore è il massimo di quel sottoalbero
    if (current->left != nullptr)
        return treemax(current->left);

    // Caso 2: non ha figlio sinistro → risaliamo verso il padre finché il nodo corrente è figlio sinistro
    PNode ancestor = padre(current); // troviamo il primo antenato
    while (ancestor != nullptr && ancestor->left == current) {
        current = ancestor;               // risaliamo l'albero
        ancestor = padre(ancestor);       // aggiorniamo l'antenato
    }

    // Se abbiamo trovato un nodo da cui siamo figli destri, è il predecessore
    return ancestor;
}


// Restituisce il minimo del sottoalbero radicato in u
PNode Tree::treemin(PNode u) const {
    while (u->left != nullptr)
        u = u->left;
    return u;
}

// Restituisce il massimo del sottoalbero radicato in u
PNode Tree::treemax(PNode u) const {
    while (u->right != nullptr)
        u = u->right;
    return u;
}

// Ricerca ricorsiva di un nodo con chiave k nel sottoalbero radicato in u
PNode Tree::treesearchaux(PNode u, int k) const {
    if (u == nullptr || u->key == k)
        return u;
    if (k < u->key)
        return treesearchaux(u->left, k);
    return treesearchaux(u->right, k);
}

// Ricerca di un nodo con chiave k nell'intero albero
PNode Tree::treesearch(int k) const {
    return treesearchaux(root, k);
}

// Inserisce il nodo z nell'albero e aggiorna i puntatori succ
void Tree::treeinsert(PNode z) {
    PNode iter = root;
    PNode y = nullptr;
    PNode ant = nullptr; // Antenato immediatamente minore

    while (iter != nullptr) {
        y = iter;
        if (z->key < iter->key)
            iter = iter->left;
        else {
            iter = iter->right;
            ant = y;
        }
    }

    if (y == nullptr)
        root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    // Aggiorna i puntatori succ
    if (ant != nullptr) {
        z->succ = ant->succ;
        ant->succ = z;
    } else {
        z->succ = y;
    }
}

// Sostituisce il sottoalbero radicato in u con quello radicato in v
void Tree::transplant(PNode u, PNode v) {
    PNode p = padre(u);
    if (p == nullptr)
        root = v;
    else if (u == p->left)
        p->left = v;
    else
        p->right = v;
}

// Elimina il nodo z dall'albero, aggiornando anche i puntatori succ
void Tree::treedelete(PNode z) {
    PNode prec = treepred(z);
    PNode succ = z->succ;

    if (z->left == nullptr) {
        transplant(z, z->right);
    } else if (z->right == nullptr) {
        transplant(z, z->left);
    } else {
        if (succ != z->right) {
            transplant(succ, succ->right);
            succ->right = z->right;
        }
        transplant(z, succ);
        succ->left = z->left;
    }

    if (prec != nullptr)
        prec->succ = succ;

    delete z;
}


// Funzione per stampare l'albero in ordine crescente usando i successori
void stampaInOrder(PNode root) {
    if (!root) {
        cout << "Albero vuoto." << endl;
        return;
    }

    PNode corrente = root;
    // Trova il minimo
    while (corrente->left) {
        corrente = corrente->left;
    }

    // Stampa tramite catena dei successori
    while (corrente) {
        cout << corrente->key << " ";
        corrente = corrente->succ;
    }
    cout << endl;
}

int main() {
    Tree t;

    // Inserisci nodi nell'albero
    int valori[] = {50, 30, 70, 20, 40, 60, 80};
    const int n = sizeof(valori) / sizeof(valori[0]);

    for (int i = 0; i < n; ++i) {
        PNode nuovo = createNode(valori[i]);
        t.treeinsert(nuovo);
    }

    cout << "Stampa dell'albero in ordine simmetrico tramite i successori:" << endl;
    stampaInOrder(t.radice());

    // Verifica ricerca
    int chiave = 40;
    PNode trovato = t.treesearch(chiave);
    if (trovato) {
        cout << "Nodo con chiave " << chiave << " trovato." << endl;
    } else {
        cout << "Nodo con chiave " << chiave << " NON trovato." << endl;
    }

    // Verifica minimo e massimo
    PNode min = t.treemin(t.radice());
    PNode max = t.treemax(t.radice());
    cout << "Minimo: " << min->key << ", Massimo: " << max->key << endl;

    // Elimina alcuni nodi e ristampa
    cout << "Eliminazione di 70 e 30..." << endl;
    t.treedelete(t.treesearch(70));
    t.treedelete(t.treesearch(30));

    cout << "Stampa dell'albero aggiornata (in-order):" << endl;
    stampaInOrder(t.radice());

    return 0;
}