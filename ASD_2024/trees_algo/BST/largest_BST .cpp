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
//dobbiano essere sicuri che quando siamo nel nodo corrente radice, il sottoaalbero destro e quello sinistro 
//siano gà stati computati. Quindi dobbiamo seguire una visita post-order
int largestBSTHelper(TreeNode* root, int& count, int& smallest, int& largest) {
    if(root == nullptr) return -1;

    int left = largestBSTHelper(root->left, largestLeft, largestRight);
    int right = largestBSTHelper(root->right, largestLeft, largestRight);
    
}

int largestBST(TreeNode* root) {
    int largestLeft = -1;
    int largestRight = -1;

    largestBSTHelper(root, largestLeft, largestRight);
}

int main() {
    // Test case 1
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(4);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(2);
    root1->left->right = new TreeNode(4);
    root1->right->left = new TreeNode(2);
    root1->right->right = new TreeNode(5);
    root1->right->right->left = new TreeNode(4);
    root1->right->right->right = new TreeNode(6);

    cout << "largest BST in tree 1: " << largestBST(root1) << endl; 

    // Test case 2
    TreeNode* root2 = new TreeNode(4);
    root2->left = new TreeNode(3);
    root2->left->left = new TreeNode(1);
    root2->left->right = new TreeNode(2);

    cout << "largest BST in tree 2: " << largestBST(root2) << endl; 

    // Test case 3
    TreeNode* root3 = new TreeNode(-4);
    root3->left = new TreeNode(-2);
    root3->right = new TreeNode(-5);

    cout << "largest BST in tree 3: " << largestBST(root3) << endl; 

    // Additional large test case
    TreeNode* root4 = new TreeNode(5);
    root4->left = new TreeNode(3);
    root4->right = new TreeNode(8);
    root4->left->left = new TreeNode(2);
    root4->left->right = new TreeNode(4);
    root4->right->left = new TreeNode(7);
    root4->right->right = new TreeNode(9);
    root4->left->left->left = new TreeNode(1);
    root4->right->left->left = new TreeNode(6);

    cout << "largest BST in tree 4: " << largestBST(root4) << endl; 

    return 0;
}