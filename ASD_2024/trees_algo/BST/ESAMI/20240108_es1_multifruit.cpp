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
#include <unordered_map>

using namespace std;

/*#region utilities functions*/

struct TreeNode {
    int val;
    bool fruitful;
    TreeNode *left;
    TreeNode *center;
    TreeNode *right;

    // Default constructor
    TreeNode() : val(0), fruitful(false), left(nullptr), center(nullptr), right(nullptr) {}

    // Constructor with a value
    TreeNode(int x, bool f) : val(x), fruitful(f), left(nullptr), center(nullptr), right(nullptr) {}

    // Constructor with a value and child nodes
    TreeNode(int x, bool f, TreeNode *left, TreeNode *center, TreeNode *right) 
        : val(x), fruitful(f), left(left), center(center), right(right) {}
};

// Typedef for pointer to a TreeNode
typedef TreeNode* PTNode;

// Function to create a new node
PTNode newNode(int data, bool fruitful) {
    return new TreeNode(data, fruitful);
}

int getHeight(PTNode root) {
    if (!root) return 0;
    return max({getHeight(root->left), getHeight(root->center), getHeight(root->right)}) + 1;
}

void printTree(PTNode root) {
    if (!root) return;

    int height = getHeight(root);
    int maxWidth = (1 << height) - 1;

    vector<vector<string>> lines(height, vector<string>(maxWidth, " "));

    queue<pair<PTNode, pair<int, int>>> q;
    q.push({root, {0, (maxWidth - 1) / 2}});

    while (!q.empty()) {
        auto node = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();

        lines[row][col] = to_string(node->val) + (node->fruitful ? "T" : "F");

        int offset = (1 << (height - row - 2));
        if (node->left) {
            q.push({node->left, {row + 1, col - offset}});
        }
        if (node->center) {
            q.push({node->center, {row + 1, col}});
        }
        if (node->right) {
            q.push({node->right, {row + 1, col + offset}});
        }
    }

    for (const auto& line : lines) {
        for (const auto& node : line) {
            cout << node << " ";
        }
        cout << endl;
    }
}
/*#endregion utilities functions*/

/*  Si consideri un albero ternario completo in cui ogni nodo ha i seguenti campi: (i) key chiave intera, (ii)
    fruitful valore booleano, (iii) left puntatore al figlio sinistro, (iv) center puntatore al figlio centrale, (v)
    right puntatore al figlio destro.

    a. Si scriva una procedura efficiente in C o C++ che assegni True al campo fruitful del nodo se e
    solo se la somma delle chiavi dei nodi di ciascuno dei sottoalberi radicati nei figli è maggiore di una
    costante k fornita in input. Il prototipo della procedura è:
    void set_fruitful(PTNode r, int k)
    
    b. Valutare la complessità della procedura, indicando eventuali relazioni di ricorrenza e mostrando la
    loro risoluzione.

    c. Specificare il linguaggio di programmazione scelto. */

void set_fruitfulHelper(PTNode r, int k, std::unordered_map<PTNode, int>& map){
    if(r == nullptr) return;    

    set_fruitfulHelper(r->left, k, map);
    set_fruitfulHelper(r->center, k, map);
    set_fruitfulHelper(r->right, k, map);

    int check_for_sum = 0;
    if(r->left) check_for_sum += (map[r->left]);
    if(r->center) check_for_sum += (map[r->center]);
    if(r->right) check_for_sum += (map[r->right]);

    map[r] = check_for_sum + r->val;

    if(check_for_sum > k){
        r->fruitful = true;
    }
    else{
        r->fruitful = false;
    }
}

//withou suing a map
int set_fruitfulHelperSmarter(PTNode r, int k) {
    if (r == nullptr) return 0;    

    int left_sum = set_fruitfulHelperSmarter(r->left, k);
    int center_sum = set_fruitfulHelperSmarter(r->center, k);
    int right_sum = set_fruitfulHelperSmarter(r->right, k);

    int total_sum = left_sum + center_sum + right_sum + r->val;

    if (left_sum + center_sum + right_sum > k) {
        r->fruitful = true;
    } else {
        r->fruitful = false;
    }

    return total_sum;
}

void set_fruitful(PTNode r, int k){
     //std::unordered_map<PTNode, int> map;
     //set_fruitfulHelper(r, k, map);
    
     set_fruitfulHelperSmarter(r, k);
}

int main() {
    // Create a sample ternary tree
    PTNode root = newNode(1, false);
    root->left = newNode(2, false);
    root->center = newNode(3, false);
    root->right = newNode(4, false);
    root->left->left = newNode(5, false);
    root->left->center = newNode(6, false);
    root->left->right = newNode(7, false);

    // Print the ternary tree
    printTree(root);
    set_fruitful(root, 17);

    cout << "\n tree after set_fruitful(): \n\n";
    printTree(root);

    return 0;
}
