#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace std;

/*
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

// Struttura del nodo per un albero generale
struct TreeNodeG {
    int key;
    TreeNodeG *leftChild;
    TreeNodeG *rightSib;

    // Default constructor
    TreeNodeG() : key(0), leftChild(nullptr), rightSib(nullptr) {}

    // Constructor with a key
    TreeNodeG(int x) : key(x), leftChild(nullptr), rightSib(nullptr) {}

    // Constructor with a key and children
    TreeNodeG(int x, TreeNodeG *leftChild, TreeNodeG *rightSib) 
        : key(x), leftChild(leftChild), rightSib(rightSib) {}
};

// Typedef per puntatore a TreeNodeG
typedef TreeNodeG* PNodeG;

// Funzione per creare un nuovo nodo
PNodeG newNode(int data) {
    return new TreeNodeG(data);
}

// Funzione per calcolare l'altezza dell'albero (per calcolare correttamente la profondità del nodo)
int getHeight(PNodeG root) {
    if (!root) return 0;
    int maxHeight = 0;
    for (PNodeG child = root->leftChild; child != nullptr; child = child->rightSib) {
        maxHeight = max(maxHeight, getHeight(child));
    }
    return maxHeight + 1;
}

// Funzione per stampare l'albero in modo strutturato
void printTree(PNodeG root) {
    if (!root) return;

    int height = getHeight(root);
    queue<pair<PNodeG, int>> q;  // La coda contiene coppie di (nodo, livello)

    q.push({root, 0});
    vector<vector<string>> levels(height);  // Memorizza i valori per ciascun livello

    while (!q.empty()) {
        PNodeG node = q.front().first;
        int level = q.front().second;
        q.pop();

        // Aggiungi il valore del nodo al livello corrispondente
        levels[level].push_back(to_string(node->key));

        // Aggiungi tutti i figli alla coda, incrementando il livello
        for (PNodeG child = node->leftChild; child != nullptr; child = child->rightSib) {
            q.push({child, level + 1});
        }
    }

    // Stampa tutti i livelli
    for (int i = 0; i < height; ++i) {
        for (const string& val : levels[i]) {
            cout << val << " ";
        }
        cout << endl;
    }
}

/*#endregion utilities functions*/

bool isNonDec(PNodeG r){
    
}

int main() {
    // Creiamo manualmente un albero generale
    PNodeG root = newNode(10);                 // Radice dell'albero
    root->leftChild = newNode(5);              // Primo figlio della radice
    root->leftChild->rightSib = newNode(15);   // Secondo figlio della radice
    root->leftChild->rightSib->rightSib = newNode(20); // Terzo figlio della radice

    // Aggiungiamo figli al primo figlio della radice
    root->leftChild->leftChild = newNode(3);   // Figlio del nodo 5
    root->leftChild->leftChild->rightSib = newNode(8); // Fratello del nodo 3

    // Aggiungiamo figli al secondo figlio della radice (nodo 15)
    root->leftChild->rightSib->leftChild = newNode(12); // Figlio del nodo 15

    // Stampiamo l'albero
    cout << "Stampa dell'albero generale:" << endl;
    printTree(root);

    // Test della funzione isNonDec
    if (isNonDec(root)) {
        cout << "La proprietà è verificata: i figli di ogni nodo sono in ordine non decrescente." << endl;
    } else {
        cout << "La proprietà NON è verificata: esistono figli di un nodo che non sono in ordine non decrescente." << endl;
    }

    return 0;
}
