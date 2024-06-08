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


vector<int> zigzagLevelOrder(Node* root) {
    vector<int> result;
    if (root == NULL) return result;
    
    queue<Node*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        vector<int> array_temp;
        for (int i = 0; i < size; i++) {    
            Node* cur_node = q.front();
            array_temp.push_back(cur_node->data);
            q.pop();

            if(cur_node->left!= NULL) {
            q.push(cur_node->left);
            }     
            if(cur_node->right!= NULL) {
                q.push(cur_node->right);
            } 
        }

        if (level % 2 == 0) {
            for (int i = 0; i < array_temp.size(); i++) {
                result.push_back(array_temp[i]);
            }
        } 
        else {
            for (int i = array_temp.size() - 1; i >= 0; i--) {
                result.push_back(array_temp[i]);
            }
        }    
        level++;      
    }
    return result;
}

vector<vector<int>> zigzagLevelOrderLeetCode(Node* root) {
    vector<vector<int>> result;
    queue<Node*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int size = q.size();
        vector<int> array_temp;
        for (int i = 0; i < size; i++) {    
            Node* cur_node = q.front();
            array_temp.push_back(cur_node->data);
            q.pop();

            if(cur_node->left!= NULL) {
            q.push(cur_node->left);
            }     
            if(cur_node->right!= NULL) {
                q.push(cur_node->right);
            } 
        }

        if (level % 2 == 0) {            
            result.push_back(array_temp);            
        } 
        else {
            vector<int> array_reverse;
            for (int i = array_temp.size() - 1; i >= 0; i--) {
                array_reverse.push_back(array_temp[i]);
            }
            result.push_back(array_reverse);
        }    
        level++;      
    }
    return result;
}

int main() {
    // Tree 1
    Node* root1 = newNode(10);
    root1->left = newNode(2);
    root1->right = newNode(3);
    root1->left->left = newNode(4);
    root1->left->right = newNode(5);
    root1->right->left = newNode(6);
    root1->right->right = newNode(-7);

    cout << "2D representation of Tree 1:\n";
    printPretty(root1, 0);    

    // Tree 2
    Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->right = newNode(3);
    root2->left->left = newNode(4);
    root2->left->right = newNode(5);
    root2->right->left = newNode(6);
    root2->right->right = newNode(7);
    root2->left->left->left = newNode(8);
    root2->left->left->right = newNode(9);
    root2->left->right->left = newNode(10);
    root2->left->right->right = newNode(11);
    root2->right->left->left = newNode(12);
    root2->right->left->right = newNode(13);
    root2->right->right->left = newNode(14);
    root2->right->right->right = newNode(15);

    cout << "2D representation of Tree 2:\n";
    printPretty(root2, 0);

    cout << "\nZig Zag Traversal of Tree 1:\n";
    vector<int> vect1 =  zigzagLevelOrder(root1);
    for(int i = 0; i < vect1.size(); i++){
        cout << vect1[i] << " ";
    }
    
    cout << "\nZig Zag Traversal of Tree 2:\n";
    vector<int> vect2 = zigzagLevelOrder(root2);
    for(int i = 0; i < vect2.size(); i++){
        cout << vect2[i] << " ";
    }

    // Tree 3
    Node* root3 = newNode(10);
    root3->left = newNode(2);

    return 0;
}