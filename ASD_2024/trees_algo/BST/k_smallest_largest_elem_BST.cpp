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

//uso una visita in-order così da dare priorità agli elementi più piccoli, come quando converto l'albero in un array
//e ho gli elementi in ordine crescente. A questo punto mi basta ritorna il k-esimo elemento.
int kthSmallestHelper(TreeNode* root, int k, int& counter) {
    if(root == nullptr) return -1;    
    
    int left = kthSmallestHelper(root->left, k, counter);
    if(left != -1) return left;

    counter++;
    if(counter == k) return root->val;    

    int right = kthSmallestHelper(root->right, k, counter);
    return right;
}

int kthSmallest(TreeNode* root, int k) {
    if(root == nullptr) return 0;
    int counter = 0;
    return kthSmallestHelper(root, k, counter);
}

//uso una visita post-order così da dare priorità agli elementi più grandi, come quando converto l'albero in un array
//e ho gli elementi in ordine crescente. A questo punto mi basta ritorna il k-esimo elemento.
int kthLargestHelper(TreeNode* root, int k, int& counter) {
    if(root == nullptr) return -1;

    int right = kthLargestHelper(root->right, k, counter);
    if(right != -1) return right;

    counter++;
    if(counter == k) return root->val;    

    int left = kthLargestHelper(root->left, k, counter);
    return left;    
}

int kthLargest(TreeNode* root, int k) {    
    if(root == nullptr) return 0;
    int counter = 0;
    return kthLargestHelper(root, k, counter);
}

int main() {
    // Example 1:
    TreeNode* root1 = newNode(3);
    root1->left = newNode(1);
    root1->right = newNode(4);
    root1->left->right = newNode(2);

    int k1 = 1;
    std::cout << "Tree 1:" << std::endl;
    printTree(root1);
    std::cout << "The " << k1 << "th smallest element is " << kthSmallest(root1, k1) << std::endl;
    std::cout << "The " << k1 << "th largest element is " << kthLargest(root1, k1) << std::endl;

    // Example 2:
    TreeNode* root2 = newNode(5);
    root2->left = newNode(3);
    root2->right = newNode(6);
    root2->left->left = newNode(2);
    root2->left->right = newNode(4);
    root2->left->left->left = newNode(1);

    int k2 = 3;
    std::cout << "Tree 2:" << std::endl;
    printTree(root2);
    std::cout << "The " << k2 << "th smallest element is " << kthSmallest(root2, k2) << std::endl;
    std::cout << "The " << k2 << "th largest element is " << kthLargest(root2, k2) << std::endl;

    return 0;
}