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

/* Il boundary traversal (o percorrenza dei confini) di un albero binario è una tecnica di attraversamento che visita i nodi lungo il confine dell'albero. Questo include tre componenti principali:

Nodi del confine sinistro: tutti i nodi lungo il lato sinistro dell'albero, dall'alto verso il basso (esclusi i nodi foglia).
Nodi foglia: tutti i nodi foglia dell'albero, da sinistra a destra.
Nodi del confine destro: tutti i nodi lungo il lato destro dell'albero, dal basso verso l'alto (esclusi i nodi foglia). 

Quindi una specie di visita del perimetro in senso antiorario*/
bool isLeaf(Node* node) {
    if (node->left == NULL && node->right == NULL) {
        return true;
    }
    else return false;
}

//tutto il bordo sinistro senza foglie e root(la aggiungo nella main function)
void addLeftBoundary(Node* root, vector<int>& res) {
    Node* cur_node = root->left;
    while(cur_node != NULL){
        if(!isLeaf(cur_node)) {
            res.push_back(cur_node->data);
        }
        if (cur_node->left != NULL) {
            cur_node = cur_node->left;
        }
        else{
            cur_node = cur_node->right;
        }
    }
}

//inOrder traversal for this part
void addLeavesBoundary(Node* root, vector<int>& res) {    
    if (isLeaf(root)) {
        res.push_back(root->data);
        //return;
    }
    if(root->left!= NULL) {
        addLeavesBoundary(root->left, res);
    }
    if(root->right!= NULL) {
       addLeavesBoundary(root->right, res);
    }
}

void addRightBoundary(Node* root, vector<int>& res) {
    vector<int> tmp;
    Node* cur_node = root->right;
    while(cur_node != NULL){
        if(!isLeaf(cur_node)) {
            tmp.push_back(cur_node->data);
        }
        if (cur_node->right != NULL) {
            cur_node = cur_node->right;
        }
        else{
            cur_node = cur_node->left;
        }
    }
    for (int i = tmp.size() - 1; i >= 0; i--) {
        res.push_back(tmp[i]);
    }   
}

vector<int> boundaryTraversal(Node* root) {
    vector<int> res;
    if(root == NULL) return res;

    res.push_back(root->data);

    if(root->left != NULL || root->right!= NULL){
        addLeftBoundary(root, res);
        addLeavesBoundary(root, res);
        addRightBoundary(root, res);
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
    //Il boundary traversal per questo albero è: 1, 2, 4, 8, 5, 9, 7, 3.

    cout << "\n2D representation of the tree:\n";
    printPretty(root, 0);

    vector<int> res = boundaryTraversal(root);
    cout << "\nBoundary traversal: ";
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }    
    cout << endl;

    return 0;
}