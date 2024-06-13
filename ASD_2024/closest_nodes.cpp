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

vector<int> closestNodesHelper(TreeNode* root, int elem) {
    vector<int> res(2, -1); 
    int floor = -1, ceil = -1;

    TreeNode* current = root;

    // Find floor and ceil in a single traversal
    while (current != nullptr) {
        if (current->val == elem) {
            floor = current->val;
            ceil = current->val;
            res[0] = floor;
            res[1] = ceil;
            return res;
        }
        if (elem > current->val) {
            floor = current->val;
            current = current->right;
        } else {
            ceil = current->val;
            current = current->left;
        }
    }

    res[0] = floor;
    res[1] = ceil;
    return res;   
}

vector<vector<int>> closestNodes(TreeNode* root, vector<int>& queries) {
    vector<vector<int>> results;
    if(root == nullptr) return results;

    for(auto elem : queries) {
        vector<int> temp_vect = closestNodesHelper(root, elem);
        results.push_back(temp_vect);
    }

    return results;
}

// Main function for testing mixTree

int main() {
    // Create a BST (root)
    TreeNode* root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(15);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(12);
    root->right->right = newNode(18);

    // Print the BST
    cout << "Tree:\n";
    printTree(root);
    cout << "\n";

    // Queries
    vector<int> queries = {4, 9, 10};

    // Call closestNodes function
    vector<vector<int>> results = closestNodes(root, queries);

    // Print the results
    cout << "Closest Nodes Results:\n";
    for (const auto& result : results) {
        cout << "[" << result[0] << ", " << result[1] << "]\n";
    }

    return 0;
}