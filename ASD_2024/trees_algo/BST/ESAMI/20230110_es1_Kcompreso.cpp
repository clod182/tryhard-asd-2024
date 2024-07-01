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

/*#region utilities functions*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    // Default constructor
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor with a value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Constructor with a value and child nodes
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Typedef for pointer to a TreeNode
typedef TreeNode* PTree;

// Function to create a new node
PTree newNode(int data) {
    return new TreeNode(data);
}

int getHeight(PTree root) {
    if (!root) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

void printTree(PTree root) {
    if (!root) return;

    int height = getHeight(root);
    int maxWidth = (1 << height) - 1;

    vector<vector<string>> lines(height, vector<string>(maxWidth, " "));

    queue<pair<PTree, pair<int, int>>> q;
    q.push({root, {0, (maxWidth - 1) / 2}});

    while (!q.empty()) {
        auto node = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();

        lines[row][col] = to_string(node->val);

        int offset = (1 << (height - row - 2));
        if (node->left) {
            q.push({node->left, {row + 1, col - offset}});
        }
        if (node->right) {
            q.push({node->right, {row + 1, col + offset}});
        }
    }

    for (const auto& line : lines) {
        for (const auto& node : line) {
            cout << node;
        }
        cout << endl;
    }
}
/*#endregion utilities functions*/

/*
Sia T un albero binario i cui nodi x hanno i campi left, right e key, dove key è un numero
intero. L’albero si dice k-compreso, per un certo numero naturale k, se per ogni nodo x la
somma delle chiavi dei nodi dell’albero radicato in x è compresa tra -k e k.

a. Scrivere una funzione efficiente in C o C++ k_compreso(u,k) che dato in input
la radice u di un albero T e un valore k verifica se T è k-compreso e ritorna 1 se T è
k-compreso, 0 altrimenti.

b. Valutare la complessità della funzione, indicando eventuali relazioni di ricorrenza
e la loro risoluzione tramite il metodo di sostituzione.

c. Specificare il linguaggio di programmazione scelto.
*/

int k_compreso_helper(TreeNode* u, int k, bool& isKCompreso) {
    if (u == nullptr) return 0;

    int left = k_compreso_helper(u->left, k, isKCompreso);
    int right = k_compreso_helper(u->right, k, isKCompreso);
    int sum_Atm = left + right + u->val;

    if (sum_Atm < -k || sum_Atm > k) {
        isKCompreso = false;
    }

    return sum_Atm;
}

bool k_compreso(TreeNode* u, int k) {
    if (u == nullptr) return true;

    bool isKCompreso = true;
    int res = k_compreso_helper(u, k, isKCompreso);
    return isKCompreso;
}


int main() {
    // Creazione di un albero binario che è k-compreso
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(-2);
    root1->right = new TreeNode(7);
    root1->left->left = new TreeNode(1);
    root1->left->right = new TreeNode(-4);
    root1->right->left = new TreeNode(-1);
    root1->right->right = new TreeNode(3);

    // Valore di k per il test
    int k1 = 10;

    // Stampa l'albero per la visualizzazione
    cout << "Albero binario 1 (dovrebbe essere k-compreso):" << endl;
    printTree(root1);

    // Test della funzione k_compreso
    bool result1 = k_compreso(root1, k1);
    if (result1) {
        cout << "\nL'albero E' " << k1 << "-compreso." << endl;
    } else {
        cout << "\nL'albero NON E' " << k1 << "-compreso." << endl;
    }

    // Creazione di un albero binario che non è k-compreso
    TreeNode* root2 = new TreeNode(8);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(10);
    root2->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(6);
    root2->right->left = new TreeNode(-4);
    root2->right->right = new TreeNode(14);

    // Valore di k per il test
    int k2 = 15;

    // Stampa l'albero per la visualizzazione
    cout << "\nAlbero binario 2 (non dovrebbe essere k-compreso):" << endl;
    printTree(root2);

    // Test della funzione k_compreso
    bool result2 = k_compreso(root2, k2);
    if (result2) {
        cout << "\nL'albero E' " << k2 << "-compreso." << endl;
    } else {
        cout << "\nL'albero NON E' " << k2 << "-compreso." << endl;
    }

    // Pulizia della memoria
    // ... (codice per deallocare la memoria come nel tuo esempio originale)

    return 0;
}