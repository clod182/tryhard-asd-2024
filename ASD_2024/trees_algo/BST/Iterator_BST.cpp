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

//non possiamo usare un vettore della visita inorder perchè in questo modo avremmo spazio O(N)
//e possiamo fare di meglio con spazio O(H)=O(log N) per BST bilanciati
//entambe le soluzioni hanno comunque TC = O(1)
class BSTIterator {
private:
    stack<TreeNode*> st;
public:
    BSTIterator(TreeNode* root) {
        while(root != nullptr){
            st.push(root);
            root = root->left;          
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
    
    bool hasNext() {
        return !st.empty();
    }
};

int main() {
    // Manually create the BST
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    // Instantiate the BSTIterator
    BSTIterator bSTIterator(root);
    
    // Perform the sequence of operations and print the results
    cout << bSTIterator.next() << endl;    // return 3
    cout << bSTIterator.next() << endl;    // return 7
    
    bool next = bSTIterator.hasNext(); // return true
    if(next) cout << "True" << endl;
    else cout << "False" << endl;

    cout << bSTIterator.next() << endl;    // return 9
    
    next = bSTIterator.hasNext(); // return true
    if(next) cout << "True" << endl;
    else cout << "False" << endl;

    cout << bSTIterator.next() << endl;    // return 15
    
    next = bSTIterator.hasNext(); // return true
    if(next) cout << "True" << endl;
    else cout << "False" << endl;

    cout << bSTIterator.next() << endl;    // return 20
    
    next = bSTIterator.hasNext(); // return false
    if(next) cout << "True" << endl;
    else cout << "False" << endl;

    return 0;
}