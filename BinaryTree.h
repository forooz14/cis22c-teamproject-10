// Binary tree abstract base class
// Student: Johnny Nguyen
// IDE: Microsoft Visual Studio

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "CustomerNode.h"
#include "QueueADT.h"

#include <iostream>

#define COUNT 8 // Used to increase space for printTree function

class BinaryTree
{
protected:
	CustomerNode *rootPtr;	// Pointer to root node
	int count;				// Number of nodes in tree

public:
	// "admin" functions
	BinaryTree()
	{
		rootPtr = 0; count = 0;
	}

	BinaryTree(const BinaryTree &tree)
	{ }

	virtual ~BinaryTree()
	{ }

	// Common functions for all binary trees
	bool isEmpty() const
	{
		return count == 0;
	}

	int size() const
	{
		return count;
	}

	void clear()
	{
		destroyTree(rootPtr); rootPtr = 0;
	}

	void preOrder(void visit(std::string &)) const
	{
		_preorder(visit, rootPtr);
	}

	void inOrder(void visit(std::string &)) const
	{
		_inorder(visit, rootPtr);
	}

	void postOrder(void visit(std::string &)) const
	{
		_postorder(visit, rootPtr);
	}

	void breadthFirst() const
	{
		_breadthFirst(rootPtr);
	}

	void printTree() const
	{
		int space = 0; int level = 0; _printTree(rootPtr, space, level);
	}

	// abstract functions to be implemented by derived class
	virtual bool insert(const std::string &inputSsn, const std::string &inputName, const double &inputChecking, const double &inputSavings, const int &inputScore) = 0;
	virtual bool remove(const std::string &data) = 0;
	virtual bool getEntry(const std::string &inputSsn, std::string &returnedSsn) const = 0;
	virtual bool getSmallest(std::string &smallestSsn) const = 0;
	virtual bool getLargest(std::string &largestSsn) const = 0;

private:
	// delete all nodes from the tree
	void destroyTree(CustomerNode *nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	CustomerNode *copyTree(const CustomerNode *nodePtr);

	// internal traverse
	void _preorder(void visit(std::string &), CustomerNode *nodePtr) const;
	void _inorder(void visit(std::string &), CustomerNode *nodePtr) const;
	void _postorder(void visit(std::string &), CustomerNode *nodePtr) const;
	void _breadthFirst(CustomerNode *nodePtr) const;
	void _printTree(CustomerNode *nodePtr, int space, int level) const;
};

//////////////////////////////////////////////////////////////////////////

CustomerNode *BinaryTree::copyTree(const CustomerNode *nodePtr)
{
	CustomerNode *newNodePtr = 0;

	return newNodePtr;
}

void BinaryTree::destroyTree(CustomerNode *nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		std::cout << "Now deleting: " << nodePtr->getSsn() << " (" << nodePtr->getName() << ")\n";
		delete nodePtr;
		count--;
	}

	if (count == 0)
	{
		std::cout << "\nTree has been successfully deleted!\n";
	}
}

void BinaryTree::_preorder(void visit(std::string &), CustomerNode *nodePtr) const
{
	if (nodePtr)
	{
		std::string ssn = nodePtr->getSsn();
		visit(ssn);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

void BinaryTree::_inorder(void visit(std::string &), CustomerNode *nodePtr) const
{
	if (nodePtr)
	{
		_preorder(visit, nodePtr->getLeftPtr());
		std::string ssn = nodePtr->getSsn();
		visit(ssn);
		_preorder(visit, nodePtr->getRightPtr());
	}
}

void BinaryTree::_postorder(void visit(std::string &), CustomerNode *nodePtr) const
{
	if (nodePtr)
	{
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
		std::string ssn = nodePtr->getSsn();
		visit(ssn);
	}
}

void BinaryTree::_breadthFirst(CustomerNode *nodePtr) const
{
	if (nodePtr == 0) // Base case: End function if empty tree
		return;

	Queue<CustomerNode *> employeeQueue; 	// Initialize temporary queue with root node
	employeeQueue.enqueue(nodePtr);

	CustomerNode *pWalk = 0; // Node for traversing

	std::cout << "BFT: ";

	while (!employeeQueue.isEmpty()) // Loop
	{
		employeeQueue.dequeue(pWalk);

		std::cout << pWalk->getSsn() << " ";

		if (pWalk->getLeftPtr() != 0)
		{
			employeeQueue.enqueue(pWalk->getLeftPtr());
		}
		if (pWalk->getRightPtr() != 0)
		{
			employeeQueue.enqueue(pWalk->getRightPtr());
		}
	}

	std::cout << std::endl;
}

void BinaryTree::_printTree(CustomerNode *nodePtr, int space, int level) const
{
	if (!nodePtr) // Base case: end function if node is NULL
	{
		return;
	}

	level++;
	space += COUNT; // Increase distance between levels

	_printTree(nodePtr->getRightPtr(), space, level); // Process right child first

	// Print current node
	std::cout << std::endl;
	for (int i = COUNT; i < space; i++)
	{
		std::cout << " ";
	}

	std::cout << level << ". " << nodePtr->getSsn();

	_printTree(nodePtr->getLeftPtr(), space, level); // Process left child

};

#endif