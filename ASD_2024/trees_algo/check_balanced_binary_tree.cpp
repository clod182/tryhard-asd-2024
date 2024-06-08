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

// Structure of a Binary Tree Node
struct Node {
    int data;
    struct Node *left, *right;
    Node(int v)
    {
        data = v;
        left = right = NULL;
    }
};

// Function to create a new Node
Node* newNode(int data) {
    Node* node = new Node(data);
    return node;
}

// Function to calculate the height of the tree
int calculateHeight(Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Utility function to print branches
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const vector<Node*>& nodesQueue) {
    vector<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        cout << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
        cout << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
    }
    cout << endl;
}

// Utility function to print nodes
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const vector<Node*>& nodesQueue) {
    vector<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        cout << setw(branchLen + 2) << ((*iter) ? to_string((*iter)->data) : "");
        cout << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
    }
    cout << endl;
}

// Utility function to print leaves
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const vector<Node*>& nodesQueue) {
    vector<Node*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? to_string((*iter)->data) : "");
    }
    cout << endl;
}

// Function to display a binary tree
void printPretty(Node* root, int indentSpace) {
    int h = calculateHeight(root);
    int nodesInThisLevel = 1;

    int branchLen = 2 * ((1 << h) - 1) - (3) * (1 << (h - 1));
    int nodeSpaceLen = 2 + (1 + 1) * (1 << h);
    int startLen = branchLen + (3) + indentSpace;

    vector<Node*> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
        branchLen = branchLen / 2 - 1;
        nodeSpaceLen = nodeSpaceLen / 2 + 1;
        startLen = branchLen + (3) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);

        vector<Node*> newNodesQueue;
        for (Node* node : nodesQueue) {
            if (node) {
                newNodesQueue.push_back(node->left);
                newNodesQueue.push_back(node->right);
            } else {
                newNodesQueue.push_back(NULL);
                newNodesQueue.push_back(NULL);
            }
        }
        nodesQueue = newNodesQueue;
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
    printLeaves(indentSpace, 1, nodesInThisLevel, nodesQueue);
}

/*#endregion utilities functions*/

int findMaxDepthRecursive(Node* root) {
    if(root == NULL) return 0;

    return 1 + max(findMaxDepthRecursive(root->left), findMaxDepthRecursive(root->right));
}

// l'altezza dei suoi sottoalberi sinistro e destro differisce al massimo di uno
bool checkBalancedBinTree(Node* root) {
    if(root == NULL) return true;
    int height_left = findMaxDepthRecursive(root->left);
    int height_right = findMaxDepthRecursive(root->right);
    return abs(height_left - height_right) <= 1 && checkBalancedBinTree(root->left) && checkBalancedBinTree(root->right);    
}

//con questa funzione ottimizzata si ottiene un O(n) contro O(nlogn) di quella sopra non ottimizzata
int checkBalancedBinTreeOptimized(Node* root) {
    if(root == NULL) return 0;

    int height_left = checkBalancedBinTreeOptimized(root->left);
    if(height_left == -1 ) return -1;
    int height_right = checkBalancedBinTreeOptimized(root->right);
    if(height_right == -1) return -1;

    if(abs(height_left - height_right) > 1) return -1;
    return 1 + max(height_left, height_right);

}

int main() {
    // Tree 1
    Node* root1 = newNode(1);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);
    root1->right->left = newNode(6);
    root1->right->right = newNode(7);

    cout << "2D representation of Tree 1:\n";
    printPretty(root1, 0);

    if (checkBalancedBinTree(root1)) {
        cout << "Tree 1 is balanced.\n";
    } else {
        cout << "Tree 1 is not balanced.\n";
    }

    // Tree 2
    Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->left->left = newNode(3);
    root2->left->left->left = newNode(4);

    cout << "2D representation of Tree 2:\n";
    printPretty(root2, 0);

    if (checkBalancedBinTree(root2)) {
        cout << "Tree 2 is balanced.\n";
    } else {
        cout << "Tree 2 is not balanced.\n";
    }

    if (checkBalancedBinTreeOptimized(root1)>=0) {
        cout << "OPTIMIZED Tree 1 is balanced.\n";
    } else {
        cout << "OPTIMIZED Tree 1 is not balanced.\n";
    }

    if (checkBalancedBinTreeOptimized(root2)>=0) {
        cout << "OPTIMIZED Tree 2 is balanced.\n";
    } else {
        cout << "OPTIMIZED Tree 2 is not balanced.\n";
    }

    return 0;
}