#include "Node.h"

Node::Node(int _data){
    data = _data;
    left = NULL;
    right = NULL;
}

Node::~Node(){}

/*
* Returns the data that is stored in this node
*
* @return the data that is stored in this node.
*/
int Node::getData() const{
    return data;
}

/*
* Returns the left child of this node or null if it doesn't have one.
*
* @return the left child of this node or null if it doesn't have one.
*/
Node * Node::getLeftChild() const{
    return left;
}

/*
* Returns the right child of this node or null if it doesn't have one.
*
* @return the right child of this node or null if it doesn't have one.
*/
Node * Node::getRightChild() const{
    return right;
}

void Node::setLeftChild(Node* _left){
    left = _left;
}
void Node::setRightChild(Node* _right){
    right = _right;
}

int Node::getHeight(){
    int leftHeight = -1;
    int rightHeight = -1;
    if (left != NULL){
        //cout << "Left child of " << data << " is " << left->getData() << ". Getting height..." << endl;
        leftHeight = left->getHeight();
        //cout << "Got height of " << leftHeight << " for " << left->getData() << endl;
    }
    else{
        leftHeight = -1;
    }
    if (right != NULL){
        //cout << "Right child of " << data << " is " << right->getData() << ". Getting height..." << endl;
        rightHeight = right->getHeight();
        //cout << "Got height of " << rightHeight << " for " << right->getData() << endl;
    }
    else{
        rightHeight = -1;
    }
    int returnValue = 1 + max(leftHeight, rightHeight);
    //cout << "Got height of " << returnValue << " for " << data << endl;
    return returnValue;
}