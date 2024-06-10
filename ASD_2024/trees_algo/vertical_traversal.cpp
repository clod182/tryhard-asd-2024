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

vector<vector<int>> verticalTraversal(Node* root) {
    //nodo, vertical, level
    queue<pair<Node*, pair<int, int>>> q; 
    //multiset perchè nello stesso vertical/level possono esserci più nodi con lo stesso value (ed due 9)
    //vertical, level, value
    map<int, map<int, multiset<int>>> nodes;   
    vector<vector<int>> res;
    if(root == NULL) return res;

    q.push({root, {0, 0}});
    while(!q.empty()){
        Node* cur_node = q.front().first;
        int vertical = q.front().second.first;
        int level= q.front().second.second;
        q.pop();

        nodes[vertical][level].insert(cur_node->data);
        if(cur_node->left!= NULL){
            q.push({cur_node->left, {vertical-1, level+1}});
        }
        if(cur_node->right!= NULL){
            q.push({cur_node->right, {vertical+1, level+1}});
        }
    }    
    
    
    for(auto p : nodes){
        vector<int> temp;
        for(auto p2 : p.second){
            //inserisco in code al vettore tutto il multiset completo di questo livello
            temp.insert(temp.end(), p2.second.begin(), p2.second.end());                
        }
        res.push_back(temp);
    }
    return res;
}

vector<int> verticalTraversal_GeeksForGeeks(Node* root) {
    queue<pair<Node*, pair<int, int>>> q; 
    map<int, map<int, vector<int>>> nodes;   
    vector<int> res;
    if (root == NULL) return res;

    q.push({root, {0, 0}});
    while (!q.empty()) {
        Node* cur_node = q.front().first;
        int vertical = q.front().second.first;
        int level = q.front().second.second;
        q.pop();

        nodes[vertical][level].push_back(cur_node->data);
        if (cur_node->left != NULL) {
            q.push({cur_node->left, {vertical - 1, level + 1}});
        }
        if (cur_node->right != NULL) {
            q.push({cur_node->right, {vertical + 1, level + 1}});
        }
    }

    for (auto& p : nodes) {
        for (auto& p2 : p.second) {
            //Do not Sort, for the GFG problem we have to print the nodes in the same order as they appear in the tree.            
            res.insert(res.end(), p2.second.begin(), p2.second.end());
        }
    }
    return res;
}

int main() {
    
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    root->left->left->left = newNode(8);
    root->right->left->right = newNode(9);

    cout << "\n2D representation of the tree:\n";
    printPretty(root, 0);

    vector<vector<int>> res = verticalTraversal(root);
    cout << "\nVertical traversal: \n";
    for(int i = 0; i < res.size(); i++){
        for(int j = 0; j < res[i].size(); j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }    
    cout << endl;

    vector<int> resGfG = verticalTraversal_GeeksForGeeks(root);
    cout << "\nVertical traversal Geek For Geeks: \n";
    for(int i = 0; i < resGfG.size(); i++){
        cout << resGfG[i] << " ";
    }

    return 0;
}