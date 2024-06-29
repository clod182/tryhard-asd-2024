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

//we have two binary trees, T1 and T2. All the elements in T1 are < than elements in T2.
//we have to merge these two BSTs into a single BST.
PTree MergeBST(PTree T1, PTree T2) {
    PTree ret = T2;

    if(T2 == nullptr) return T1;

    else if(T2->left == nullptr){
        T2->left = T1;
        return ret;
    }

    else{
        PTree cur_node = T2->left;
        while(cur_node->left != nullptr) {
            cur_node = cur_node->left;
        }
        cur_node->left = T1;
    }    

    return ret;
}

/*#region--------------------------------------------------------------------------- BALANCED VERSION*/
//if we want to have a balanced BST, we have to change the strategy

// Helper function to perform an in-order traversal of the BST and store the elements in a vector
void inorderTraversal(PTree root, std::vector<int>& elems) {
    if (!root) return;
    inorderTraversal(root->left, elems);
    elems.push_back(root->val);
    inorderTraversal(root->right, elems);
}

// Helper function to build a balanced BST from a sorted array
PTree sortedArrayToBST(const std::vector<int>& elems, int start, int end) {
    if (start > end) return NULL;
    int mid = start + (end - start) / 2;
    PTree node = new TreeNode(elems[mid]);
    node->left = sortedArrayToBST(elems, start, mid - 1);
    node->right = sortedArrayToBST(elems, mid + 1, end);
    return node;
}

// Function to merge two BSTs into one
PTree MergeBST(PTree T1, PTree T2) {
    std::vector<int> elems1, elems2;
    inorderTraversal(T1, elems1);
    inorderTraversal(T2, elems2);
    
    // Merge the two sorted arrays
    std::vector<int> mergedElems;
    mergedElems.reserve(elems1.size() + elems2.size());
    mergedElems.insert(mergedElems.end(), elems1.begin(), elems1.end());
    mergedElems.insert(mergedElems.end(), elems2.begin(), elems2.end());
    
    // Build a balanced BST from the merged sorted array
    return sortedArrayToBST(mergedElems, 0, mergedElems.size() - 1);
}
/*#endregion*/

int main() {
    // Create first BST with all elements < elements in the second BST
    PTree root1 = newNode(1);
    root1->left = newNode(0);
    root1->right = newNode(3);
    root1->right->left = newNode(2);

    cout << "BST 1: " << endl;
    printTree(root1);

    // Create second BST with all elements > elements in the first BST
    PTree root2 = newNode(6);
    root2->left = newNode(5);
    root2->right = newNode(8);
    root2->right->left = newNode(7);

    cout << "BST 2: " << endl;
    printTree(root2);

    // Merge the BSTs
    PTree mergedRoot = MergeBST(root1, root2);

    // Print the merged BST
    cout << "BST merged: " << endl;
    printTree(mergedRoot);

    return 0;
}