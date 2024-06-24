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

//Possiamo risolvere il problema con TC = SC = O(N) con una semplice visita in-order del BST
//Se vogliamo usare spazio SC = O(1) invece va usate la visita "Morris Traversal"
void recoverTreeHelper(TreeNode* root, TreeNode*& firstElem, TreeNode*& secondElem, TreeNode*& prevElem) {
    if(root == nullptr) return;

    recoverTreeHelper(root->left, firstElem, secondElem, prevElem);

    if(firstElem == nullptr && prevElem->val > root->val) {
        firstElem = prevElem;
    }
    if(firstElem != nullptr && prevElem->val > root->val) {
        secondElem = root;
        //return; The early return can miss cases where violations are adjacent or where there are 
        //multiple misplaced nodes in close succession, leading to wrong results.
    }
    prevElem = root;

    recoverTreeHelper(root->right, firstElem, secondElem, prevElem);
}

void recoverTree(TreeNode* root) {
    TreeNode* firstElement = nullptr;
    TreeNode* secondElement = nullptr;
    TreeNode* prevElement = new TreeNode(INT_MIN);

    recoverTreeHelper(root, firstElement, secondElement, prevElement);

    int temp = firstElement->val;
    firstElement->val = secondElement->val;
    secondElement->val = temp;
}

int main() {
    // Example 1
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(1);
    cout << "Before recovery (Example 1): \n";
    printTree(root1);
    cout << endl;
    recoverTree(root1);
    cout << "After recovery (Example 1): \n";
    printTree(root1);
    cout << endl;

    // Example 2
    TreeNode* root2 = new TreeNode(3);
    root2->left = new TreeNode(1);
    root2->right = new TreeNode(4);
    root2->right->left = new TreeNode(2);
    cout << "Before recovery (Example 2): \n";
    printTree(root2);
    cout << endl;
    recoverTree(root2);
    cout << "After recovery (Example 2): \n";
    printTree(root2);
    cout << endl;

    // Example 3 - Large Tree
    TreeNode* root3 = new TreeNode(10);
    root3->left = new TreeNode(5);
    root3->right = new TreeNode(15);
    root3->left->left = new TreeNode(2);
    root3->left->right = new TreeNode(7);
    root3->right->left = new TreeNode(12);
    root3->right->right = new TreeNode(20);
    root3->left->left->left = new TreeNode(1);
    root3->left->left->right = new TreeNode(3);
    root3->right->left->left = new TreeNode(11);
    root3->right->left->right = new TreeNode(13);
    // Swap two nodes to create an incorrect BST
    swap(root3->left->left->right->val, root3->right->left->left->val);  // Swap nodes with values 3 and 11

    cout << "Before recovery (Example 3): \n";
    printTree(root3);
    cout << endl;
    recoverTree(root3);
    cout << "After recovery (Example 3): \n";
    printTree(root3);
    cout << endl;

    return 0;
}
