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

// Helper function to check symmetry between two subtrees
vector<int> rootToNodePath(Node* root, Node* dest){
    vector<int> path;
    map<Node* , Node*> parent;
    queue<Node*> q;
    if(root == NULL || dest == NULL) return path;

    q.push(root);
    parent[root] = NULL;
    while (!q.empty()){
        Node* cur_node = q.front();
        q.pop();

        if(cur_node == dest){
            path.push_back(cur_node->data);
            while(parent[cur_node] != NULL){
                path.push_back(parent[cur_node]->data);
                cur_node = parent[cur_node];
            }
            reverse(path.begin(), path.end());
            return path;
        }
        if(cur_node->left!= NULL){
            parent[cur_node->left] = cur_node;
            q.push(cur_node->left);
        }
        if(cur_node->right!= NULL){
            parent[cur_node->right] = cur_node;
            q.push(cur_node->right);
        }
    }   

    return path;
}

bool rootToNodePathRecursiveHelper(Node* root, Node* dest, vector<int>& path){
    if(root == NULL || dest == NULL) return false; 

    path.push_back(root->data);
    if(root == dest){
        return true;
    }

    bool ris1 = rootToNodePathRecursiveHelper(root->left, dest, path);
    if(ris1 == true) return true;
    bool ris2 = rootToNodePathRecursiveHelper(root->right, dest, path);
    if(ris2 == true) return true;

    //if this path is not found, remove the last element of the path
    path.pop_back();
    return false;    
}

vector<int> rootToNodePathRecursive(Node* root, Node* dest){
    vector<int> path;
    bool ris = rootToNodePathRecursiveHelper(root, dest, path);
    if(ris == true) return path;
    else return path;
}

//-------------------------------------- leetcode problem --------------------------------------
bool rootToNodePathRecursiveHelperLC(Node* root, Node* dest, vector<int>& path){
    if(root == NULL || dest == NULL) return false; 

    path.push_back(root->data);
    if(root == dest){          
        return true;
    }

    bool ris1 = rootToNodePathRecursiveHelperLC(root->left, dest, path);
    if(ris1 == true) return true;
    bool ris2 = rootToNodePathRecursiveHelperLC(root->right, dest, path);
    if(ris2 == true) return true;

    //if this path is not found, remove the last element of the path
    path.pop_back();
    return false;
}

string rootToNodePathRecursiveLC(Node* root, Node* dest){
    string pathString = "";
    vector<int> path;
    bool ris = rootToNodePathRecursiveHelperLC(root, dest, path);
    if(ris == true){
        for(int i = 0; i < path.size(); i++){
            pathString += to_string(path[i]);
            if(i!= path.size() - 1) pathString += "->";
        }
        return pathString;
    } 
    else return pathString;
}

void findLeaves(Node* root, vector<Node*>& leaves) {    
    if(root == NULL) return;
    if(root->left == NULL && root->right == NULL){
        leaves.push_back(root);
        return;
    }
    findLeaves(root->left, leaves);
    findLeaves(root->right, leaves);
}

vector<string> binaryTreePaths_notOptimized(Node* root) {
    vector<string> path;
    if(root == NULL) return path;
    vector<Node*> leaves;
    findLeaves(root, leaves);
    for(int i = 0; i < leaves.size(); i++){
        string s = rootToNodePathRecursiveLC(root, leaves[i]);
        path.push_back(s);
    }
    return path;
}

//-------------------------------------- leetcode problem OPTIMIZED, O(N) instead of O(N^2) --------------------------------------
void dfs_binaryTreePaths(Node* root, vector<string>& paths, string path){
    if(root == NULL) return;
    path += to_string(root->data);
    if(root->left == NULL && root->right == NULL){
        paths.push_back(path);
        return;
    }

    path += "->";
    dfs_binaryTreePaths(root->left, paths, path);
    dfs_binaryTreePaths(root->right, paths, path);
    //qui non serbe rimuovere l'ultimo "elemento" se non troviamo il path, la stringa path non è passata per referenza e quindi ogni ramo di ricorsione la "resetta"
    //path.pop_back();
    //path.pop_back();
    return;
}

vector<string> binaryTreePaths(Node* root) {
    vector<string> paths;
    dfs_binaryTreePaths(root, paths, "");
    return paths;
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

    Node* root2 = newNode(1);
    root2->left = newNode(2);
    root2->right = newNode(22);
    root2->left->left = newNode(33);
    root2->left->right = newNode(44);
    root2->right->left = newNode(84);
    root2->right->right = newNode(3);
    root2->left->left->left = newNode(5);
    root2->left->left->left->right = newNode(55);
    root2->right->right->right = newNode(15);

    cout << "\n2D representation of the tree 2:\n";
    /*
        1
       / \
      2   22
     / \  / \
   33  44 84  3
   /          \
  5            15
    */
    printPretty(root2, 0);

    vector<int> path = rootToNodePath(root2, root2->left->left->left);
    cout << "\nPath from" << root->data << " to " << root2->left->left->left->data << ": \n";
    for(int i = 0; i < path.size(); i++){
        cout << path[i] << " ";
    }

    vector<int> path2 = rootToNodePathRecursive(root2, root2->right->right->right);
    cout << "\nPath RECURSIVE from" << root2->data << " to " << root2->right->right->right->data << ": \n";
    for(int i = 0; i < path2.size(); i++){
        cout << path2[i] << " ";
    }

    vector<string> path3 = binaryTreePaths(root2);
    cout << "\nPath LEET CODE from" << root2->data << " to " << root2->right->right->right->data << ": \n";
    for(int i = 0; i < path3.size(); i++){
        cout << path3[i] << " ";
    }
    
    cout << endl;

    return 0;
}