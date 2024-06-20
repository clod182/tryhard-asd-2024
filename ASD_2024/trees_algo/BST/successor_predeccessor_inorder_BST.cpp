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

//brute force --> creo un array con la visita in-order (che quindi è già ordinato), cerco key e ritorno il valore precedente 
//e successivo ad esso


//in-order visit, qundi il primo valore che trovo maggiore di key è il mio successor, l'ultimo valore più
//piccolo che trovo rispetto a key è il mio predecessor

TreeNode* findNextInOrder(TreeNode* root) {
    if(root == nullptr) return nullptr;
    
    if(root->left != nullptr) return findNextInOrder (root->left);    

    else if(root != nullptr) return root;    

    else return findNextInOrder (root->right);
}

void findPreSuc(TreeNode* root, TreeNode*& pre, TreeNode*& suc, int key) {
    if(root == nullptr) return;

    // Traverse the left subtree
    findPreSuc(root->left, pre, suc, key);

    // Update predecessor if needed
    if (root->val < key) {
        pre = root;
    }

    // If current node's value is equal to the key
    if (root->val == key) {
        // For successor, we need to look at the smallest value node in the right subtree
        if (root->right != nullptr) {
            TreeNode* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            suc = temp;
        }
    }

    // Update successor if needed
    if (root->val > key && (suc == nullptr || root->val < suc->val)) {
        suc = root;
    }

    // Traverse the right subtree
    findPreSuc(root->right, pre, suc, key);
}

int main() {
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->left = new TreeNode(60);
    root->right->right = new TreeNode(80);

    int key = 60;

    TreeNode* pre = nullptr;
    TreeNode* suc = nullptr;

    findPreSuc(root, pre, suc, key);

    if (pre != nullptr) {
        cout << "Predecessor: " << pre->val << endl;
    } else {
        cout << "Predecessor: None" << endl;
    }

    if (suc != nullptr) {
        cout << "Successor: " << suc->val << endl;
    } else {
        cout << "Successor: None" << endl;
    }

    cout << "BST Structure:" << endl;
    printTree(root);

    return 0;
}
