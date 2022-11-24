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
        leftHeight = left->getHeight();
    }
    else{
        leftHeight = -1;
    }
    if (right != NULL){
        rightHeight = right->getHeight();
    }
    else{
        rightHeight = -1;
    }
    int returnValue = 1 + max(leftHeight, rightHeight);
    return returnValue;
}