#include <iostream>
#include <vector>
using namespace std;
// <>

/* TESTO
Esercizio 4
Dato un albero binario, scrivere una funzione che costruisce un array bidimensionale mat tale che, 
per ogni coppia di nodi u e v, l’elemento mat[u][v] sia il minimo antenato comune di u e v. 
La funzione deve richiedere tempo O(n^2) e il suo prototipo è:

void minAntCom(PNode r, vector<vector<int>>& mat)
Per semplicità si assuma che i nodi abbiano chiavi numerate da 0 a n-1 e che queste chiavi identifichino il nodo. 
Di conseguenza gli indici della matrice rappresentano i nodi e in posizione mat[u][v] c'è la chiave del nodo 
che è il minimo antenato comune di u e v.

[Il minimo antenato comune di due nodi u e v è  l’antenato comune  di u e v che si trova più lontano dalla radice dell’albero.]
Analizzare e motivare in modo chiaro, preciso ed approfondito la complessità della funzione.
*/

/*#region utilities functions*/
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

typedef Node* PNode;


// Funzione per creare un nuovo nodo
PNode newNode(int key) {
    return new Node(key);
}

// Funzione per stampare la matrice
void printMatrix(const vector<vector<int>>& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

/*#endregion utilities functions*/

//Puoi sfruttare una visita DFS per calcolare le informazioni sugli antenati di ciascun nodo, 
//mantenendo una struttura che registra il percorso dalla radice a ciascun nodo.
//Grazie a questo possiamo poi confrontare il percorso dei due nodi da confrontare e trovare 
//l'antenato fino a dove i percorsi non divergono.
void dfs(PNode node, vector<int>& path, vector<vector<int>>& paths) {
    if (!node) return;

    // Aggiungi il nodo corrente al percorso
    path.push_back(node->key);

    // Salva il percorso per il nodo corrente
    paths[node->key] = path;

    // Esplora il sottoalbero sinistro e destro
    dfs(node->left, path, paths);
    dfs(node->right, path, paths);

    // Rimuovi il nodo corrente dal percorso (backtracking)
    path.pop_back();
}

void minAntCom(PNode r, vector<vector<int>>& mat) {
    int n = mat.size();
    // Inizializzo i percorsi
    vector<int> path;
    vector<vector<int>> paths(n); // Inizializza con `n` vettori vuoti

    // Costruisco i percorsi con DFS
    dfs(r, path, paths);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                mat[i][j] = i;  // Il minimo antenato comune di un nodo con se stesso è il nodo stesso
            } else {
                vector<int>& path1 = paths[i];
                vector<int>& path2 = paths[j];
                int k = 0, l = 0;
                int lastCommonAncestor = -1;  // Variabile per memorizzare l'ultimo antenato comune

                // Confronta i percorsi
                while (k < path1.size() && l < path2.size() && path1[k] == path2[l]) {
                    lastCommonAncestor = path1[k];  // Aggiorna l'antenato comune
                    k++;
                    l++;
                }

                // Assegna l'ultimo antenato comune alla matrice
                mat[i][j] = lastCommonAncestor;
            }
        }
    }
}

int main() {
    // Esempio di albero:
    //         0
    //        / \
    //       1   2
    //      / \    \
    //     3   4    5

    PNode root = newNode(0);
    root->left = newNode(1);
    root->right = newNode(2);
    root->left->left = newNode(3);
    root->left->right = newNode(4);
    root->right->right = newNode(5);

    int n = 6; // Numero di nodi
    vector<vector<int>> mat(n, vector<int>(n, -1)); // Inizializza matrice con -1

    minAntCom(root, mat); // Popola la matrice

    cout << "Matrice dei minimi antenati comuni:" << endl;
    printMatrix(mat);

    return 0;
}
