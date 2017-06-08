//
// Binary Search Tree Implementation
//

#include <iostream>
#include <queue>
#include <limits>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* insert(Node* root, int data);
Node* makeNode(int data);
Node* remove(Node* root, int target);
bool search(Node* root, int data);
void inorderTraverse(Node* root);
void levelOrder(Node* root);
bool isBinarySearchTree(Node * root);
bool isGreaterValue(Node* root, int value);
bool isLesserValue(Node* root, int value);
bool isBSTutil(Node* root, int minVal, int maxVal);
bool isBalanced(Node* root);
int balancedHeight(Node* root);

int main()
{
    Node* root = NULL;
    int search_n;
 
    root = insert(root, 30);
    root = insert(root, 1);
    root = insert(root, 59);
    root = insert(root, 32);
    root = insert(root, 10);
    root = insert(root, 50);
    root = insert(root, 1);
    
    levelOrder(root);
    
    if (isBinarySearchTree(root)){
        cout << "This is a binary search tree";
    } else {
        cout << "This is not a binary search tree";
    }
    
    while (true) {
        cout << "\nEnter search term: ";
        cin >> search_n;
        
        if (search(root, search_n))
        {
            cout << "\nFound";
        }
        else {
            cout << "\nNot Found";
        }
    }
}

bool isBalanced(Node* root)
{
    if (balancedHeight(root) > -1) return true;
    
    return false;
}

int balancedHeight(Node* root)
{
    if (root == NULL) return 0;
    
    int heightLeft  = balancedHeight(root->left);
    int heightRight = balancedHeight(root->right);
    
    if (heightLeft == -1 || heightRight == -1) return -1;
    if (abs(heightLeft - heightRight) > 1) return -1;

    if (heightLeft > heightRight) return heightLeft + 1;
    
    return heightRight + 1;
}

Node* makeNode(int data)
{
    Node* newNode  = new Node();
    newNode->data  = data;
    newNode->right = newNode->left = NULL;
    
    return newNode;
}

Node* insert(Node* root, int data)
{
    if (root == NULL){
        cout << "null -> creating node\n";
        root = makeNode(data);
        return root;
    } else if (data <= root->data) {
        cout << "Moving left\n";
        root->left = insert(root->left, data);
    } else {
        cout << "Moving right\n";
        root->right = insert(root->right, data);
    }

    return root;
}

bool search(Node* root, int data)
{
    if (root == NULL) {
        cout << "NUll node\n";
        return false;
    } else if(root->data == data) {
        return true;
    } else if(data <= root->data){
        cout << "L Data is " << root->data << endl;
        return search(root->left, data);
    }
    
    cout << "R Data is " << root->data << endl;

    return search(root->right, data);
}

void inorderTraverse(Node* root)
{
    if (root == NULL) {
        return;
    }
    
    inorderTraverse(root->left);
    
    cout << root->data << endl;
    
    inorderTraverse(root->right);
}

void levelOrder(Node* root)
{
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty()){
        Node* current = q.front();
        cout << current->data << endl;
        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
        q.pop();
    }
}


void lOrder(Node* root)
{
    if (root == NULL) return;
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty())
    {
        Node* current = q.front();
        cout << current->data << endl;
        if (current->left != NULL) q.push(current->left);
        if (current->right != NULL) q.push(current->right);
        q.pop();
    }
}

void depthFirst(Node* root)
{
    if (root == NULL) return;
    
    depthFirst(root->left);
    cout << root->data;
    depthFirst(root->right);
    
}

bool isBSTutil(Node* root, int minVal, int maxVal)
{
    if (root == NULL) return true;
    
    cout << "Checking " << root->data << " -> Min: " << minVal << " | Max: " << maxVal << endl;
    
    if (root->data > minVal && root->data <= maxVal &&
        isBSTutil(root->left, minVal, root->data) && isBSTutil(root->right, root->data, maxVal)){
        return true;
    }
    
    return false;
}

bool isBinarySearchTree(Node* root)
{
    return isBSTutil(root, INT_MIN, INT_MAX);

    // This way costs more processing time.
//    if (root == NULL) return true;
//    
//    if (isLesserValue(root->left, root->data) && isGreaterValue(root->right, root->data) && isBinarySearchTree(root->left) && isBinarySearchTree(root->right)){
//        return true;
//    } else {
//        return false;
//    }
}

bool isBST(Node* root, int minVal, int maxVal)
{
    if (root == NULL) return true;
    
    if (root->data > minVal && root->data <= maxVal && isBST(root->left, minVal, root->data) && isBST(root->right, root->data, maxVal)){
        return true;
    }
    
    return false;
}

int balancedH(Node* root)
{
    if (root == NULL) return 0;
    
    int hLeft  = balancedH(root->left);
    int hRight = balancedH(root->right);
    
    if (hLeft == -1 || hRight == -1) return -1;
    if (abs(hLeft - hRight) > 1) return -1;
    
    if (hLeft > hRight) return hLeft + 1;
    
    return hRight + 1;
}

bool isGreaterValue(Node* root, int value)
{
    if (root == NULL) return true;
    
    if (root->data > value && isGreaterValue(root->left, value) && isGreaterValue(root->right, value)){
        return true;
    } else {
        return false;
    }
}

bool isLesserValue(Node* root, int value)
{
    if (root == NULL) return true;
    
    if (root->data <= value && isLesserValue(root->left, value) && isLesserValue(root->right, value)){
        return true;
    } else {
        return false;
    }
}

Node* remove(Node* root, int data)
{
    if (root == NULL) return root;
    
    if (data < root->data) {
        root->left = remove(root->left, data);
    }else if (data > root->data) {
        root->right = remove(root->right, data);
    }else {
        // Case 1: Node has no child
        if (root->left == NULL && root->right == NULL){
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            struct Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            struct Node* temp = root;
            root = root->left;
            delete temp;
        } else {
            
        }
    }
    
    return root;
}
//Node* printDepthFist(Node * root, int data)
//{
//    
//}
