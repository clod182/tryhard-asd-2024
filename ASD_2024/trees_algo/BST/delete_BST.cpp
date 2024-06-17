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

TreeNode* findLastRight(TreeNode* root) {    
    if(root->right == nullptr) return root;
    return findLastRight(root->right);
}
//decido di operare andando a collegare al "padre" del nodo da eliminare il sottoalbero SX e di collegare al suo ultimo
//figlio destro il sottoalbero DX
TreeNode* deleteNodeHelper(TreeNode* root) {
    if(root->left == nullptr) return root->right; //caso 1
    else if(root->right == nullptr) return root->left; //caso 2
    //caso 3
    TreeNode* right_child = root->right;
    TreeNode* last_right = findLastRight(root->left);
    last_right->right = right_child;
    return root->left;
}

TreeNode* deleteNode(TreeNode* root, int val) {
        if(root == nullptr) return root;
        if(root->val == val) return deleteNodeHelper(root);
        TreeNode* ogRoot = root;
        while(root != nullptr) {
            //val < nodo
            if(val < root->val ) {
                if(root->left != nullptr && root->left->val == val) {
                    root->left = deleteNodeHelper(root->left);
                    break;
                }
                else{ //altrimenti continuo a cercare nella parte sinistra
                    root = root->left;
                }
            }
            // val > nodo
            else{
                if(root->right != nullptr && root->right->val == val) {
                    root->right = deleteNodeHelper(root->left);
                    break;
                }
                else{ //altrimenti continuo a cercare nella parte destra
                    root = root->right;
                }
            }     
        }
        return ogRoot;
}

int main() {
    PTree root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->right = newNode(18);

    cout << "Original Tree:" << endl;
    printTree(root);

    int newValue = 7;
    root = deleteNode(root, newValue);

    cout << "\nTree after deleting " << newValue << ":" << endl;
    printTree(root);

    return 0;
}