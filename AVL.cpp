#include "AVL.h"

AVL::AVL() {
    root = NULL;
}
AVL::~AVL() {
    clear();
}

Node * AVL::getRootNode() const {
    return root;
}

bool AVL::add(int data) {
    return searchAdd(root, data);
}

/*
* Attempts to remove the given int from the BST tree
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data) {
    return searchRemove(root, data);
}

/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear() {
    recursiveClear(root);
}

void AVL::recursiveClear(Node*& _root) {
    if (_root == NULL) {
        return;
    }
    Node* leftChild = _root->getLeftChild();
    Node* rightChild = _root->getRightChild();
    recursiveClear(leftChild);
    recursiveClear(rightChild);
    delete _root;
    _root = NULL;
}

bool AVL::searchAdd(Node *&current, int newData) {
    if (root == NULL) {
        root = new Node(newData);
        return true;
    }
    if (current->getData() == newData) {
        return false;
    }
    else if (current->getData() > newData) {
        if (current->getLeftChild() == NULL) {
            current->setLeftChild(new Node(newData));
            return true;
        }
        else {
            Node *temp = current->getLeftChild();
            return searchAdd(temp, newData);
        }
    }
    else {
        if 
        (current->getRightChild() == NULL) 
        {
            current->setRightChild(new Node(newData));
            return true;
        }
        else {
            Node *temp = current->getRightChild();
            return searchAdd(temp, newData);
        }
    }
}

bool AVL::searchRemove(Node *&current, int oldData){
    if (current == NULL) {
        return false;
    }
    Node* deleteMe = NULL;
    bool deleteLeft = false;
    bool deleteRight = false;
    Node* newRoot = NULL;

    if (current == root && current->getData() == oldData) {
        deleteMe = current;
    }
    else if (current->getLeftChild() != NULL && current->getLeftChild()->getData() == oldData){
        deleteMe = current->getLeftChild();
        deleteLeft = true;
    }
    else if (current->getRightChild() != NULL && current->getRightChild()->getData() == oldData){
        deleteMe = current->getRightChild();
        deleteRight = true;
    }
    else{
        if (current->getData() > oldData){
            Node* newSearchRoot = current->getLeftChild();
            return searchRemove(newSearchRoot, oldData);
        }
        else{
            Node* newSearchRoot = current->getRightChild();
            return searchRemove(newSearchRoot, oldData);
        }
    }
    
    if(deleteMe->getLeftChild() == NULL && deleteMe -> getRightChild() == NULL){
        if (deleteLeft){
            current->setLeftChild(NULL);
        }
        else if (deleteRight){
            current->setRightChild(NULL);
        }
    }
    else if(deleteMe->getLeftChild() == NULL && deleteMe -> getRightChild() != NULL){
        if (deleteLeft){
            current->setLeftChild(deleteMe->getRightChild());
        }
        else if (deleteRight){
            current->setRightChild(deleteMe->getRightChild());
        }
        else if (deleteMe == root){
            newRoot = deleteMe->getRightChild();
        }
    }
    else if(deleteMe->getLeftChild() != NULL && deleteMe -> getRightChild() == NULL){
        if (deleteLeft){
            current->setLeftChild(deleteMe->getLeftChild());
        }
        else if (deleteRight){
            current->setRightChild(deleteMe->getLeftChild());
        }
        else if (deleteMe == root){
            newRoot = deleteMe->getLeftChild();
        }
    }
    else{
        Node* replacement = deleteMe->getLeftChild();
        while(replacement->getRightChild() != NULL){
            replacement = replacement->getRightChild();
        }
        Node* replacementParent = deleteMe;
        if(deleteMe->getLeftChild() != replacement){
            replacementParent = deleteMe->getLeftChild();
            while (replacementParent->getRightChild() != replacement){
                replacementParent = replacementParent->getRightChild();
            }
        }
        if (replacementParent == deleteMe){
            replacementParent->setLeftChild(replacement->getLeftChild());
        }
        else{
            replacementParent->setRightChild(replacement->getLeftChild());
        }
        if (deleteLeft){
            current->setLeftChild(replacement);
        }
        else if (deleteRight){
            current->setRightChild(replacement);
        }
        else if (deleteMe == root){
            newRoot = replacement;
        }
        replacement->setLeftChild(deleteMe->getLeftChild());
        replacement->setRightChild(deleteMe->getRightChild());
    }
    if (deleteMe == root){
        delete deleteMe;
        root = newRoot;
    }
    else{
        delete deleteMe;
    }
    return true;
}