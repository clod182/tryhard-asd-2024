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
struct PNode {
    int data;
    PNode* left;
    PNode* right;

    PNode(int k) : data(k), left(nullptr), right(nullptr) {}
};

// Function to create a new Node
PNode* newNode(int data) {
    return new PNode(data);
}

// Function to calculate the height of the tree
int calculateHeight(PNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Utility function to print branches
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const vector<PNode*>& nodesQueue) {
    vector<PNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        cout << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
        cout << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
    }
    cout << endl;
}

// Utility function to print nodes
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const vector<PNode*>& nodesQueue) {
    vector<PNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        cout << setw(branchLen + 2) << ((*iter) ? to_string((*iter)->data) : "");
        cout << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
    }
    cout << endl;
}

// Utility function to print leaves
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const vector<PNode*>& nodesQueue) {
    vector<PNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? to_string((*iter)->data) : "");
    }
    cout << endl;
}

// Function to display a binary tree
void printPretty(PNode* root, int indentSpace) {
    int h = calculateHeight(root);
    int nodesInThisLevel = 1;

    int branchLen = 2 * ((1 << h) - 1) - (3) * (1 << (h - 1));
    int nodeSpaceLen = 2 + (1 + 1) * (1 << h);
    int startLen = branchLen + (3) + indentSpace;

    vector<PNode*> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
        branchLen = branchLen / 2 - 1;
        nodeSpaceLen = nodeSpaceLen / 2 + 1;
        startLen = branchLen + (3) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);

        vector<PNode*> newNodesQueue;
        for (PNode* node : nodesQueue) {
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

// Helper function to check symmetry between two subtrees

// Main function to check if the tree is symmetric
void sottrazione_alberi(PNode* r1, PNode* r2){
    if(r1 == nullptr || r2 == nullptr) return;

    r1->data = r1->data - r2->data;
    sottrazione_alberi(r1->left, r2->left);
    sottrazione_alberi(r1->right, r2->right);
}

int main() {
    // Creazione di due alberi binari completi di esempio
    PNode* T1 = newNode(1);
    T1->left = newNode(3);
    T1->right = newNode(5);
    T1->left->left = newNode(7);
    T1->left->right = newNode(10);
    T1->right->left = newNode(2);
    T1->right->right = newNode(3);

    PNode* T2 = newNode(0);
    T2->left = newNode(4);
    T2->right = newNode(6);
    T2->left->left = newNode(8);
    T2->left->right = newNode(2);
    T2->right->left = newNode(3);
    T2->right->right = newNode(5);

    cout << "Albero T1 iniziale:" << endl;
    printPretty(T1, 2);

    cout << "Albero T2 iniziale:" << endl;
    printPretty(T2, 2);

    // Applicazione della sottrazione
    sottrazione_alberi(T1, T2);

    cout << "Albero T1 dopo la sottrazione:" << endl;
    printPretty(T1, 2);

    return 0;
}