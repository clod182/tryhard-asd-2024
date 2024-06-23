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

//come soluzione di "brute force" potrei creare un array con la visita in-order
//e mantenere 2 puntatori, uno a inizio e uno a fine array. Vedo che somma danno,
//se la somma è più grande di K sposto il puntatore a inizio array. Se la somma è
//più piccola sposto il puntatore a fine array. Se una coppia da la somma abbiamo 
//quindi trovato il nodo che ha la somma uguale a K.
void makeArrayInOrderOfBst(TreeNode* root, vector<int>& inorder_input_tree) {
    if(root == nullptr) return;
    makeArrayInOrderOfBst(root->left, inorder_input_tree);
    inorder_input_tree.push_back(root->val);
    makeArrayInOrderOfBst(root->right, inorder_input_tree);
}

bool findTargetBruteForce(TreeNode* root, int k) {
    if(root == nullptr) return false;
    vector<int> inorder_input_tree;
    makeArrayInOrderOfBst(root, inorder_input_tree);
    int start = 0;
    int end = inorder_input_tree.size() - 1;
    //basta anche solo     while (start < end)
    while(root!= nullptr && start < inorder_input_tree.size() && end >= 0 && start < end) {
        if(inorder_input_tree[start] + inorder_input_tree[end] == k) return true;
        else if(inorder_input_tree[start] + inorder_input_tree[end] < k) start++;
        else end--;
    }
    return false;
}

//Con i BST possiamo usare una soluzione più elegante.
//Entambi gli approcci richiedono TC = O(n) ma possiamo migliorare la SC = O(n)
//del primo approccio.
class BSTIterator {
private:
    stack<TreeNode*> st;
    stack<TreeNode*> st_before;
public:
    BSTIterator(TreeNode* root) {
        TreeNode* ogRoot = root;
        while(root != nullptr){
            st.push(root);
            root = root->left;          
        }

        while(ogRoot != nullptr){
            st_before.push(ogRoot);
            ogRoot = root->right;          
        }
    }
    
    int next() {
        if(st.empty()){
            return -1;
        }
        TreeNode* cur = st.top();
        int ret = cur->val;
        st.pop();

        if(cur->right != nullptr){
            cur= cur->right;
            while(cur != nullptr){
                st.push(cur);
                cur = cur->left;          
            }
        }
        return ret;
    }

    int before() {
        if(st_before.empty()){
            return -1;
        }
        TreeNode* cur = st_before.top();
        int ret = cur->val;
        st_before.pop();

        if(cur->left != nullptr){
            cur= cur->left;
            while(cur != nullptr){
                st_before.push(cur);
                cur = cur->right;          
            }
        }
        return ret;
    }
    
    bool hasNext() {
        return !st.empty();
    }

    bool hasBefore() {
        return !st_before.empty();
    }
};

bool findTarget(TreeNode* root, int k) {

}

int main() {
    // Create the binary search tree for the first example
    TreeNode* root1 = new TreeNode(5);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(6);
    root1->left->left = new TreeNode(2);
    root1->left->right = new TreeNode(4);
    root1->right->right = new TreeNode(7);

    int k1 = 9;
    cout << "Example 1: " << (findTargetBruteForce(root1, k1) ? "true" : "false") << endl; // Output: true

    // Create the binary search tree for the second example
    TreeNode* root2 = new TreeNode(5);
    root2->left = new TreeNode(3);
    root2->right = new TreeNode(6);
    root2->left->left = new TreeNode(2);
    root2->left->right = new TreeNode(4);
    root2->right->right = new TreeNode(7);

    int k2 = 28;
    cout << "Example 2: " << (findTargetBruteForce(root2, k2) ? "true" : "false") << endl; // Output: false

    return 0;
}