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

vector<int> leftView(Node *root) {
    vector<int> res;
    if (root == NULL) return res;
    // node, level
    queue<pair<Node*, int>> q;
    // level, node
    map<int, int> m;

    q.push({root, 0});
    
    while (!q.empty()) {
        Node* current = q.front().first;
        int cur_level = q.front().second;
        q.pop();
        
        if(m.find(cur_level) == m.end()){
            m[cur_level] = current->data;
            res.push_back(current->data); 
        }               

        if(current->left!= NULL){
            q.push({current->left, cur_level + 1});
        }
        if(current->right!= NULL){
            q.push({current->right, cur_level + 1});
        }
    }

    /*for(auto it : m){            
        res.push_back(it.second);            
    }*/
    return res;
}

vector<int> rightView(Node *root) {
    vector<int> res;
    if (root == NULL) return res;
    // node, level
    queue<pair<Node*, int>> q;
    // level, node
    map<int, int> m;

    q.push({root, 0});
    
    while (!q.empty()) {
        Node* current = q.front().first;
        int cur_level = q.front().second;
        q.pop();        
        
        m[cur_level] = current->data;         

        if(current->left!= NULL){
            q.push({current->left, cur_level + 1});
        }
        if(current->right!= NULL){
            q.push({current->right, cur_level + 1});
        }
    }
    for(auto it : m){            
        res.push_back(it.second);            
    }
    return res;
}

//with preorder traversal
void leftViewRecursiveHelper(Node * root, int level, vector<int>& res) {   
    if(root == NULL) return;

    if(level == res.size()){
        res.push_back(root->data);
    }

    if(root->left){
        leftViewRecursiveHelper(root->left, level + 1, res);
    } 
    if(root->right){
        leftViewRecursiveHelper(root->right, level + 1, res);
    }       
}
vector<int> leftViewRecursive(Node * root) {
    vector<int> res;
    leftViewRecursiveHelper(root, 0, res);
    return res;
}

void rightViewRecursiveHelper(Node * root, int level, vector<int>& res) {
    if(root == NULL) return;

    if(level == res.size()){
        res.push_back(root->data);
    }

    if(root->right){
        rightViewRecursiveHelper(root->right, level + 1, res);
    }
    if(root->left){
        rightViewRecursiveHelper(root->left, level + 1, res);
    }       
}
vector<int> rightViewRecursive(Node * root) {
    vector<int> res;
    rightViewRecursiveHelper(root, 0,res);
    return res;
}

int main() {
    
    Node* root = newNode(20);
    root->left = newNode(8);
    root->right = newNode(22);
    root->left->left = newNode(5);
    root->left->right = newNode(3);
    root->left->right->left = newNode(10);
    root->left->right->right = newNode(14);
    root->right->right = newNode(25);

    cout << "\n2D representation of the tree:\n";
    printPretty(root, 0);

    vector<int> res = leftView(root);
    cout << "\nleft View: \n";
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }

    vector<int> res2 = rightView(root);
    cout << "\nright View: \n";
    for(int i = 0; i < res2.size(); i++){
        cout << res2[i] << " ";
    }

    vector<int> res3 = leftViewRecursive(root);
    cout << "\nleft View RECURSIVE: \n";
    for(int i = 0; i < res3.size(); i++){
        cout << res3[i] << " ";
    }

    vector<int> res4 = rightViewRecursive(root);
    cout << "\nright View RECURSIVE: \n";
    for(int i = 0; i < res4.size(); i++){
        cout << res4[i] << " ";
    }

    return 0;
}