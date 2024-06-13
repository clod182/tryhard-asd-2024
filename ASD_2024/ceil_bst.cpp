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
void findCeilHelper(TreeNode* root, int input, int& ceil) {
    if (root == NULL) return;
    if(root->val == input){
        ceil = root->val;
        return;
    } 
    if (root->val > input) {
        if (root->val < ceil) {
            ceil = root->val;
        }
        findCeilHelper(root->left, input, ceil);
    } else {
        findCeilHelper(root->right, input, ceil);
    }  
}
int findCeil(TreeNode* root, int input) {
    if (root == NULL) return -1;
    int ret = INT_MAX;
    findCeilHelper(root, input, ret);
    if(ret == INT_MAX) return -1;
    return ret;    
}

int findCeilIterative(TreeNode* root, int input) {
    if (root == NULL) return -1;
    int ret = -1;

    while(root != NULL) {
        if(root->val == input) return root->val;
        if (root->val > input) {      
            ret = root->val;      
            root = root->left;
        } 
        else {
            root = root->right;
        }
    }
    return ret;
}

// Main function for testing mixTree
int main() {

    // Create BST (T2)
    PTree T2 = newNode(15);
    T2->left = newNode(13);
    T2->right = newNode(17);
    T2->left->left = newNode(12);
    T2->left->right = newNode(14);
    T2->right->left = newNode(16);
    T2->right->right = newNode(18);  

    // Print T2
    cout << "Tree T2:\n";
    printTree(T2);
    cout << "\n";

    int res = findCeil(T2, 10);
    cout << "findCeil: " << res << "\n";

    res = findCeilIterative(T2, 10);
    cout << "findCeil ITERATIVE: " << res << "\n";
    return 0;
}