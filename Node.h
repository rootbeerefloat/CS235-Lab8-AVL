#pragma once

#include <iostream>
#include "NodeInterface.h"

using namespace std;

class Node: public NodeInterface {
private:
    int data;
    Node* left;
    Node* right;
public:
	Node(int _data);
	~Node();

	/*
	* Returns the data that is stored in this node
	*
	* @return the data that is stored in this node.
	*/
	int getData() const;

	/*
	* Returns the left child of this node or null if it doesn't have one.
	*
	* @return the left child of this node or null if it doesn't have one.
	*/
	Node * getLeftChild() const;

	/*
	* Returns the right child of this node or null if it doesn't have one.
	*
	* @return the right child of this node or null if it doesn't have one.
	*/
	Node * getRightChild() const;

	void setLeftChild(Node* _left);
	void setRightChild(Node* _right);
};