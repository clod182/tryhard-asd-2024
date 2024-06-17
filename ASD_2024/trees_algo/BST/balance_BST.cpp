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

void makeArrayInOrderOfBst(TreeNode* root, vector<int>& inorder_input_tree) {
    if(root == nullptr) return;
    makeArrayInOrderOfBst(root->left, inorder_input_tree);
    inorder_input_tree.push_back(root->val);
    makeArrayInOrderOfBst(root->right, inorder_input_tree);
}
TreeNode* balanceBSTHelper(vector<int>& arr, int start, int end) {
    if (start > end) return nullptr;    

    int mid = start + (end - start) / 2;
    TreeNode* root = new TreeNode(arr[mid]);
    root->left = balanceBSTHelper(arr, start, mid - 1);
    root->right = balanceBSTHelper(arr, mid + 1, end);

    return root;    
}

TreeNode* balanceBST(TreeNode* root) {
    
    //creo un array visitando il bst input con visita inorder
    vector<int> inorder_input_tree;
    makeArrayInOrderOfBst(root, inorder_input_tree);
    /*for(int i = 0; i < inorder_input_tree.size(); i++){
        cout << inorder_input_tree[i] << " ";
    }*/
    int arr_size = inorder_input_tree.size();    
    TreeNode* retTree = balanceBSTHelper(inorder_input_tree, 0, arr_size - 1);

    return retTree;
}

int main() {
    // Create an unbalanced BST
    PTree root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(20);
    root->left->left = newNode(3);
    root->left->right = newNode(8);
    root->left->left->left = newNode(2);
    root->left->left->right = newNode(4);
    root->left->right->left = newNode(7);
    root->left->right->right = newNode(9);
    root->right->left = newNode(15);
    root->right->right = newNode(25);
    root->right->left->left = newNode(12);
    root->right->left->right = newNode(18);
    root->right->right->left = newNode(22);
    root->right->right->right = newNode(30);
    root->right->right->right->right = newNode(35);
    root->right->right->right->right->right = newNode(40);

    // Print the original unbalanced BST
    cout << "Original Unbalanced Tree:\n";
    printTree(root);
    cout << "\n";

    // Balance the BST
    PTree balancedRoot = balanceBST(root);

    // Print the balanced BST
    cout << "Balanced Tree:\n";
    printTree(balancedRoot);
    cout << "\n";

    return 0;
}
