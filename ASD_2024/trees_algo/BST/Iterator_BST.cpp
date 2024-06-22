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
        while(root->left != nullptr){
            st.push(root);
            root = root->left;
        }
    }
    
    int next() {
        TreeNode* cur = st.top();
        int ret = cur->val;
        st.pop();

        if(st.size() == 1){
            TreeNode* cur_only_node = st.top();
            BSTIterator(cur_only_node);
        }
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

int main() {
    // Manually create the BST
    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(70);
    root->left->left = new TreeNode(20);
    root->left->right = new TreeNode(40);
    root->right->left = new TreeNode(60);
    root->right->left->left = new TreeNode(59);
    root->right->right = new TreeNode(80);

    // Test BSTIterator
    BSTIterator bSTIterator(root);
    cout << bSTIterator.next() << endl;    // return 20
    cout << bSTIterator.next() << endl;    // return 30
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 40
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 50
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 59
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 60
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 70
    cout << bSTIterator.hasNext() << endl; // return true
    cout << bSTIterator.next() << endl;    // return 80
    cout << bSTIterator.hasNext() << endl; // return false

    return 0;
}