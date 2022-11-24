#pragma once

#include "Node.h"
#include "AVLInterface.h"

using namespace std;

class AVL : public AVLInterface {
private:
    Node* root;
	bool searchAdd(Node*& root, int newData);
	bool searchRemove(Node*& root, int oldData);
	void recursiveClear(Node*& _root);
	void rotateLeft(Node*& _root);
	void rotateRight(Node*& _root);
	int checkBalance(Node*& _root);
	void restoreBalance(Node*& _root);
public:
	AVL();
	~AVL();

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	Node * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
};
