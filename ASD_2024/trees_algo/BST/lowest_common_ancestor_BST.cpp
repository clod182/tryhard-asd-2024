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

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr || root == p || root == q) return root;
    while(root != nullptr) {
        if(root->val > p->val && root->val > q->val) {
            root = root->left;
        } else if(root->val < p->val && root->val < q->val) {
            root = root->right;
        } else {
            break;
        }
    }
    return root;
}

TreeNode* lowestCommonAncestorRecursive(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root == nullptr || root == p || root == q) return root;
    if(root->val > p->val && root->val > q->val) {
        return lowestCommonAncestorRecursive(root->left, p, q);
    }
    if(root->val < p->val && root->val < q->val) {
        return lowestCommonAncestorRecursive(root->right, p, q);
    }
    return root;
}

int main() {
    TreeNode* root2 = newNode(5);
    root2->left = newNode(3);
    root2->right = newNode(6);
    root2->left->left = newNode(2);
    root2->left->right = newNode(4);
    root2->left->left->left = newNode(1);

    printTree(root2);
    
    TreeNode* node1 = root2->left->left;
    TreeNode* node2 = root2->left->right;
    TreeNode *res = lowestCommonAncestor(root2, node1, node2);
    TreeNode *res2 = lowestCommonAncestor(root2, node1, node2);

    cout << "\nLowestCommonAncestor of " << node1->val << " and " << node2->val << " is " << res->val << endl;
    cout << "\nLowestCommonAncestor RECURSIVE of " << node1->val << " and " << node2->val << " is " << res2->val << endl;

    return 0;
}