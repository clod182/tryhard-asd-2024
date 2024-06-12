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

PTree mixTree(PTree T1, PTree T2) {
    PTree returnTree = nullptr;
    return returnTree;
}

// Main function for testing mixTree
int main() {
    // Create first BST (T1)
    PTree T1 = newNode(5);
    T1->left = newNode(3);
    T1->right = newNode(7);
    T1->left->left = newNode(2);
    T1->left->right = newNode(4);
    T1->right->left = newNode(6);
    T1->right->right = newNode(8);

    // Create second BST (T2)
    PTree T2 = newNode(15);
    T2->left = newNode(13);
    T2->right = newNode(17);
    T2->left->left = newNode(12);
    T2->left->right = newNode(14);
    T2->right->left = newNode(16);
    T2->right->right = newNode(18);

    // Print T1
    cout << "Tree T1:\n";
    printTree(T1);
    cout << "\n";

    // Print T2
    cout << "Tree T2:\n";
    printTree(T2);
    cout << "\n";

    // Mix the two trees
    PTree mixedTree = mixTree(T1, T2);

    // Print the mixed tree
    cout << "Mixed Tree:\n";
    printTree(mixedTree);
    cout << "\n";

    return 0;
}