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