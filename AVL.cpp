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
            bool status = searchAdd(temp, newData);
            current->setLeftChild(temp);
            if (status) {
                restoreBalance(current);
            }
            return status;
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
            bool status = searchAdd(temp, newData);
            current->setRightChild(temp);
            if (status) {
                restoreBalance(current);
            }
            return status;
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
            bool status = searchRemove(newSearchRoot, oldData);
            current->setLeftChild(newSearchRoot);
            if (status) restoreBalance(current);
            return status;
        }
        else{
            Node* newSearchRoot = current->getRightChild();
            bool status = searchRemove(newSearchRoot, oldData);
            current->setRightChild(newSearchRoot);
            if (status) restoreBalance(current);
            return status;
        }
    }
    
    if(deleteMe->getLeftChild() == NULL && deleteMe -> getRightChild() == NULL){
        if (deleteLeft){
            current->setLeftChild(NULL);
            restoreBalance(current);
        }
        else if (deleteRight){
            current->setRightChild(NULL);
            restoreBalance(current);
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
            restoreBalance(current);
        }
        else if (deleteRight){
            current->setRightChild(deleteMe->getLeftChild());
            restoreBalance(current);
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
        restoreBalance(current);
        if (deleteMe == root) root = newRoot;
        if (replacementParent->getData() == deleteMe -> getData()) fixReplacement(root, replacement->getData());
        else fixReplacement(root, replacementParent->getData());
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

bool AVL::fixReplacement(Node*& _root, int parentValue){
    if (_root == NULL){
        return false;
    }
    int currentData = _root->getData();
    if (currentData == parentValue){
        restoreBalance(_root);
        return true;
    }
    else if (currentData > parentValue){
        Node* newRoot = _root->getLeftChild();
        bool status = fixReplacement(newRoot, parentValue);
        _root->setLeftChild(newRoot);
        if (status) restoreBalance(_root);
        return status;
    }
    else{
        Node* newRoot = _root->getRightChild();
        bool status = fixReplacement(newRoot, parentValue);
        _root->setRightChild(newRoot);
        if (status) restoreBalance(_root);
        return status;
    }
}

void AVL::rotateLeft(Node*& _root){
    Node* newAp = _root->getRightChild();
    Node* transfer = newAp->getLeftChild();
    newAp->setLeftChild(_root);
    _root->setRightChild(transfer);
    _root = newAp;
}

void AVL::rotateRight(Node*& _root){
    Node* newAp = _root->getLeftChild();
    Node* transfer = newAp->getRightChild();
    newAp->setRightChild(_root);
    _root->setLeftChild(transfer);
    _root = newAp;
}

/*
Check Ballance:
    0 = balanced
    1 = left left
    2 = left right
    3 = right left
    4 = right right
*/
int AVL::checkBalance(Node*& _root){
    if(_root == NULL){
        return 0;
    }
    int leftHeight = -1;
    int rightHeight = -1;
    int leftLeftHeight = -1;
    int leftRightHeight = -1;
    int rightLeftHeight = -1;
    int rightRightHeight = -1;

    if(_root->getLeftChild() != NULL){
        leftHeight = _root->getLeftChild()->getHeight();
        if(_root->getLeftChild()->getLeftChild() != NULL) leftLeftHeight = _root->getLeftChild()->getLeftChild()->getHeight();
        if(_root->getLeftChild()->getRightChild() != NULL) leftRightHeight = _root->getLeftChild()->getRightChild()->getHeight();
    }
    if(_root->getRightChild()!= NULL){
        rightHeight = _root->getRightChild()->getHeight();
        if(_root->getRightChild()->getLeftChild() != NULL) rightLeftHeight = _root->getRightChild()->getLeftChild()->getHeight();
        if(_root->getRightChild()->getRightChild() != NULL) rightRightHeight = _root->getRightChild()->getRightChild()->getHeight();
    }

    if(leftHeight - rightHeight > 1){
        if(leftLeftHeight >= leftRightHeight){
            return 1;
        }
        else{
            return 2;
        }
    }
    else if(rightHeight - leftHeight > 1){
        if(rightRightHeight >= rightLeftHeight){
            return 4;
        }
        else{
            return 3;
        }
    }
    else{
        return 0;
    }
}

void AVL::restoreBalance(Node*& _root){
    int balance = checkBalance(_root);
    cout << "Balance of " << _root->getData() << ": " << balance << endl;
    Node* leftChild = _root->getLeftChild();
    Node* rightChild = _root->getRightChild();
    switch (balance){
        case 0:
            break;
        case 1:
            rotateRight(_root);
            break;
        case 2:
            rotateLeft(leftChild);
            _root->setLeftChild(leftChild);
            rotateRight(_root);
            break;
        case 3:
            rotateRight(rightChild);
            _root->setRightChild(rightChild);
            rotateLeft(_root);
            break;
        case 4:
            rotateLeft(_root);
            break;
    }
}