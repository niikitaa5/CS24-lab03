// intbst.cpp
// Implements class IntBST
// Nikita Sharma
// October 29, 2023

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n){
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    else
        return (insert(value, root));
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (contains(value) == true)
        return false;
    if (n->info > value) {
        if (n->left != nullptr) 
            return(insert(value, n->left));
        else {
            Node *insertedNode = new Node(value);
            insertedNode->parent = n;
            n->left = insertedNode;
            return true;
        }
    }
    else if (n->info < value) {
        if (n->right != nullptr) 
            return(insert(value, n->right));
        else {
            Node *insertedNode = new Node(value);
            insertedNode->parent = n;
            n->right = insertedNode;
            return true;
        }
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const { 
    printPreOrder(root); 
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if(n == nullptr) 
        return;
    cout<< n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if(n == nullptr) 
        return;
    printInOrder(n->left);
    cout << n->info << " "; 
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root); 
}

void IntBST::printPostOrder(Node *n) const {
    if(n == nullptr) 
        return;
    printPostOrder(n->left);
    printPostOrder(n->right);
    cout<< n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (!n)
        return 0;
    else 
        return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (!n) 
        return 0;
    else 
        return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr)
        return NULL;
    else if (n->info == value) 
        return n;
    else {
        if (n->info > value)
            return(getNodeFor(value, n->left));
        else 
            return(getNodeFor(value, n->right));
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    if (getNodeFor(value, root))
        return true;
    return false;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node *n = getNodeFor(value, root);
    if (n == nullptr)
        return 0;
    else if (n->left == nullptr) {
        while (n->parent) {
            if (n->info > n->parent->info)
                return n->parent;
            n = n->parent;
            if (n == root) {
                Node *minPredecessor = new Node(0);
                return minPredecessor;
            }
        }
    }
    else {
        n = n->left;                                                                                                                                                                                                                                            
        while (n->right)
            n = n->right;
        return n;
    }
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    return (getPredecessorNode(value)->info);
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node *n = getNodeFor(value, root);
    if (n == nullptr)
        return 0;
    else if (n->right == nullptr) {
        while (n->parent) {
            if (n->info < n->parent->info)
                return n->parent;
            n = n->parent;
            if (n == root) {
                Node *maxSuccessor = new Node(0);
                return maxSuccessor;
            }
        }
        return 0;
    }
    else {
        n = n->right;                                                                                                                                                                                                                                            
        while (n->left)
            n = n->left;
        return n;
    }
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    return (getSuccessorNode(value)->info);
}

// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    if (contains(value) == false)
        return false;
    else {
        Node *n = getNodeFor(value, root);
        if ((n->left == nullptr) && (n->right == nullptr)) {
            if (n->parent) {
                if ((n->info) > (n->parent->info)) {
                    n->parent->right = nullptr;
                }
                else 
                    n->parent->left = nullptr;
            }
            //delete n;
            return true;
        }
        else if ((n->left == nullptr) && !(n->right == nullptr)) {
            n->info = n->right->info;
            n->right = nullptr;
            //delete n;
        }
        else if ((n->right == nullptr) && !(n->left == nullptr)) {
            n->info = n->left->info;
            n->left = nullptr;
            //delete n;
        }
        else {
            int val = getSuccessor(n->info);
            if ((getSuccessorNode(n->info)->left == nullptr) && (getSuccessorNode(n->info)->right == nullptr)) 
                n->right = nullptr;    
            else if ((getSuccessorNode(n->info)->left == nullptr) && !(getSuccessorNode(n->info)->right == nullptr)) 
                n->right = getSuccessorNode(n->info)->right;
            else 
                getSuccessorNode(n->info)->parent->left = nullptr;
            n->info = val;
        }
        return true;
    }
}

