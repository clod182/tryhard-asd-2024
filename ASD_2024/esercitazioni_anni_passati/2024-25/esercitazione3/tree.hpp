#ifndef TREE_HPP
#define TREE_HPP

// Definizione del nodo dell'albero
struct Node {
    int key;
    Node* succ;   // Successore in ordine simmetrico
    Node* left;   // Figlio sinistro
    Node* right;  // Figlio destro
};

// Alias per comodità
using PNode = Node*;

class Tree {
private:
    PNode root;

    // Funzioni ausiliarie
    void cancella(PNode u);
    PNode treesearchaux(PNode u, int k) const;

public:
    // Costruttore e distruttore
    Tree();
    ~Tree();

    // Funzioni base
    bool is_empty() const;
    PNode radice() const;

    // Accessori dei nodi
    int leggiInfo(PNode u) const;
    PNode figlioSx(PNode u) const;
    PNode figlioDx(PNode u) const;
    PNode padre(PNode u) const;
    PNode treesucc(PNode u) const;
    PNode treepred(PNode u) const;
    PNode treemin(PNode u) const;
    PNode treemax(PNode u) const;

    // Operazioni principali
    PNode treesearch(int k) const;
    void treeinsert(PNode z);
    void treedelete(PNode z);
    void transplant(PNode u, PNode v);
};

// Funzione helper esterna per creare un nuovo nodo
PNode createNode(int val);

#endif // TREE_HPP
