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

//si potrebbe usare come prev_node semplicemente un int inizializzato a INT_MIN, ma nel caso in cui passano un valore 
//in input uguale a INT_MIN, non funzionerebbe
bool isValidBSTHelper(TreeNode* root, TreeNode*& prev_node) {
    if(root == nullptr) return true;

    bool left = isValidBSTHelper(root->left, prev_node);
    if(left == false) return false;

    if(prev_node != nullptr && root->val <= prev_node->val) return false;
    prev_node = root;

    bool right = isValidBSTHelper(root->right, prev_node);
    if(right == false) return false; 

    return true;
}

bool isValidBST(TreeNode* root) {
    if(root == nullptr) return true;

    TreeNode* prev_node = nullptr; // Initialize prev_nodeious node as nullptr
    return isValidBSTHelper(root, prev_node);
}

//---------------------------------------------------------------- different approach
bool isValidBSTHelperapproach2(TreeNode* node, long minVal, long maxVal) {
    if (node == nullptr) return true; // An empty tree is a valid BST

    if (node->val <= minVal || node->val >= maxVal) return false; // Current node must be within the valid range

    // Recursively validate the left and right subtrees with updated ranges
    return isValidBSTHelperapproach2(node->left, minVal, node->val) && 
           isValidBSTHelperapproach2(node->right, node->val, maxVal);
}

bool isValidBSTapproach2(TreeNode* root) {
    return isValidBSTHelperapproach2(root, LONG_MIN, LONG_MAX);
}

int main() {
    TreeNode* root2 = newNode(5);
    root2->left = newNode(3);
    root2->right = newNode(6);
    root2->left->left = newNode(2);
    root2->left->right = newNode(4);
    root2->left->left->left = newNode(1);

    printTree(root2);

    bool result = isValidBST(root2);
    if(result) {
        cout << "\nThe tree IS a valid BST" << endl;
    }
    else {
        cout << "\nThe tree IS NOT a valid BST" << endl;
    }

    result = isValidBSTapproach2(root2);
    if(result) {
        cout << "\nThe tree IS a valid BST approach2" << endl;
    }
    else {
        cout << "\nThe tree IS NOT a valid BST approach2" << endl;
    }

    return 0;
}