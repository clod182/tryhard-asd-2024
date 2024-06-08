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
#include <climits>

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


int findMaxPathSumHelper(Node* root, int& cur_max) {
    if(root == NULL) return 0;

    int leftSum = max(0,findMaxPathSumHelper(root->left, cur_max)); //in questa parte aggiungo il max con 0 per escludere tutti i paths che avrebbero un valore di somma negativo
    int rightSum = max(0,findMaxPathSumHelper(root->right, cur_max));
    cur_max = max(cur_max, leftSum + rightSum + root->data); //aggiungo root->data qui perchè devo tenere conto anche del valore del nodo corrente
    return root->data + max(leftSum, rightSum);
}

int findMaxPathSum(Node* root) {
    int cur_max = INT_MIN;
    findMaxPathSumHelper(root, cur_max);
    return cur_max;
}

int main() {
    // Tree 1
    Node* root1 = newNode(-10);
    root1->left = newNode(-2);
    root1->right = newNode(-3);
    root1->left->left = newNode(-4);
    root1->left->right = newNode(-5);
    root1->right->left = newNode(-6);
    root1->right->right = newNode(-7);

    cout << "2D representation of Tree 1:\n";
    printPretty(root1, 0);    

    // Tree 2
    Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->left->left = newNode(3);
    root2->left->left->left = newNode(4);

    cout << "2D representation of Tree 2:\n";
    printPretty(root2, 0);

    int diam = findMaxPathSum(root1);
    cout << "Max PAth Sum of Tree 1: " << diam << endl;
    diam = findMaxPathSum(root2);
    cout << "Max PAth Sum of Tree 2: " << diam << endl;

    return 0;
}