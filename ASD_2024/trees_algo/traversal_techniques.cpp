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

/*#region DFS TRAVERSALS*/

// left-root-right
void inorderTraversal(Node* root) {
    if(root != NULL){
        inorderTraversal(root->left);
        cout << root->data << " ";        
        inorderTraversal(root->right);
    }    
}

// root-left-right
void preorderTraversal(Node* root) {
    if(root != NULL){
        cout << root->data << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }    
}

// left-right-root
void postorderTraversal(Node* root) {
    if(root != NULL){        
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->data << " ";
    }    
}

void iterativePreorderTraversal(Node* root) {
    if(root == NULL){
        return;
    }
    stack <Node*> s;
    s.push(root);

    while (!s.empty()) {    
        Node* cur_node = s.top();
        s.pop();
        cout << cur_node->data << " ";
        if(cur_node->right!= NULL) {
            s.push(cur_node->right);
        }
        if(cur_node->left!= NULL) {
            s.push(cur_node->left);
        }
    }
}

void iterativeInOrderTraversal(Node* root) {    
    stack <Node*> s;    

    while (true) {
        if(root!=NULL) {
            s.push(root);
            root = root->left;
        }
        else{
            if (s.empty()) break;
            root = s.top();
            s.pop();
            cout << root->data << " ";
            root = root->right;
        }      
    }  

}

void iterative2StackPostOrderTraversal(Node* root) {    

    if(root == NULL){
        return;
    }

    stack <Node*> s;    
    stack <Node*> s2;

    s.push(root);
    while (!s.empty()) {
        Node* cur_node = s.top();
        s.pop();
        s2.push(cur_node);
        if(cur_node->left!= NULL) {
            s.push(cur_node->left);
        }
        if(cur_node->right!= NULL) {
            s.push(cur_node->right);
        }
        
    }

    while(!s2.empty()) {
        Node* cur_node = s2.top();
        s2.pop();
        cout << cur_node->data << " ";
    }
    
}

//ok da vedere ma non ha senso usare questo approccio difficile
void iterative1StackPostOrderTraversal(Node* root) {    

    if (root == NULL) {
        return;
    }

    stack<Node*> s;
    Node* lastVisited = NULL;
    Node* current = root;

    while (!s.empty() || current != NULL) {
        // Reach the leftmost node of the current node
        if (current != NULL) {
            s.push(current);
            current = current->left;
        } else {
            // Peek the node on the top of the stack
            Node* peekNode = s.top();
            // If the right child exists and it hasn't been visited yet
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                // Visit the node
                cout << peekNode->data << " ";
                lastVisited = peekNode;
                s.pop();
            }
        }
    } 
    
    
}

/*#endregion DFS TRAVERSALS*/

/*#region BFS TRAVERSALS*/
void levelOrderTraversal(Node* root) {
    queue <Node*> q;
    vector <int> visit;
    if (root == NULL) {
        return;
    }
    q.push(root);

    while (!q.empty()) {    
        Node* cur_node = q.front();
        q.pop();
        visit.push_back(cur_node->data);

        if(cur_node->left!= NULL) {
            q.push(cur_node->left);
        }
        if(cur_node->right!= NULL) {
            q.push(cur_node->right);
        }
    }

    for(int i=0; i<visit.size(); i++) {
        cout << visit[i] << " ";
    }
    
}
/*#endregion BFS TRAVERSALS*/

int main() {
    
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    cout << "\n2D representation of the tree:\n";
    printPretty(root, 0);

    cout << "Inorder traversal: ";
    inorderTraversal(root);
    cout << endl;

    cout << "Preorder traversal: ";
    preorderTraversal(root);
    cout << endl;

    cout << "Postorder traversal: ";
    postorderTraversal(root);
    cout << endl;    

    cout << "BFS Level Order traversal: ";
    levelOrderTraversal(root);
    cout << endl;

    cout << "ITERATIVE PreOrder traversal: ";
    iterativePreorderTraversal(root);
    cout << endl;

    cout << "ITERATIVE InOrder traversal: ";
    iterativeInOrderTraversal(root);
    cout << endl;

    cout << "ITERATIVE PostOrder 2Stack traversal: ";
    iterative2StackPostOrderTraversal(root);
    cout << endl;

    cout << "ITERATIVE PostOrder 1Stack traversal: ";
    iterative1StackPostOrderTraversal(root);
    cout << endl;

    return 0;
}