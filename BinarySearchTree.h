// Binary Search Tree ADT
// Student: Johnny Nguyen
// IDE: Microsoft Visual Studio

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

class BinarySearchTree : public BinaryTree
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	CustomerNode * _insert(CustomerNode *&nodePtr, CustomerNode *newNode);

	// internal remove node: locate and delete target node under nodePtr subtree
	CustomerNode *_remove(CustomerNode *nodePtr, const std::string target, bool &success);

	// delete target node from tree, called by internal remove node
	CustomerNode *deleteNode(CustomerNode *targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	CustomerNode *removeLeftmostNode(CustomerNode *nodePtr, std::string &successor);

	// search for target node
	CustomerNode *findNode(CustomerNode *treePtr, const std::string targetSsn, std::string &name, bool &result) const;

	// find the smallest (leftmost) node in nodePtr tree
	CustomerNode *_getSmallest(CustomerNode *nodePtr, std::string &foundSsn) const;

	// find the largest (rightmost) node in nodePtr tree
	CustomerNode *_getLargest(CustomerNode *nodePtr, std::string &foundSsn) const;

public:
	// insert a node at the correct location
	bool insert(const std::string &inputSsn, const std::string &inputName, const double &inputChecking, const double &inputSavings, const int &inputScore);

	// remove a node if found
	bool remove(const std::string &inputSsn);

	// find a target node
	bool getEntry(const std::string &target, std::string &returnedSsn) const;

	// find the smallest node
	bool getSmallest(std::string &smallestSsn) const;

	// find the smallest node
	bool getLargest(std::string &largestSsn) const;
};

///////////////////////// public function definitions ///////////////////////////

bool BinarySearchTree::insert(const std::string &inputSsn, const std::string &inputName, const double &inputChecking, const double &inputSavings, const int &inputScore)
{
	CustomerNode *newNodePtr = new CustomerNode(inputSsn, inputName, inputChecking, inputSavings, inputScore);

	_insert(this->rootPtr, newNodePtr);

	return true;
}

bool BinarySearchTree::remove(const std::string & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful;
}

bool BinarySearchTree::getEntry(const std::string &inputSsn, std::string &returnedSsn) const
{
	bool result = false;

	findNode(this->rootPtr, inputSsn, returnedSsn, result);

	return result;
}

bool BinarySearchTree::getSmallest(std::string &smallestSsn) const
{
	return _getSmallest(this->rootPtr, smallestSsn);
}

bool BinarySearchTree::getLargest(std::string &largestSsn) const
{
	return _getLargest(this->rootPtr, largestSsn);
}

//////////////////////////// private functions ////////////////////////////////////////////

CustomerNode* BinarySearchTree::_insert(CustomerNode *&nodePtr, CustomerNode *newNodePtr)
{
	if (nodePtr == 0) // Initialize root node with new node if empty tree
	{
		nodePtr = newNodePtr;
		count++;
	}
	else // Traverse through BST
	{
		CustomerNode *pWalk = nodePtr; // Initialize walker with root node

		while (pWalk != 0)
		{
			if (newNodePtr->getSsn() < pWalk->getSsn()) // Compare walker with new node
			{
				if (pWalk->getLeftPtr() == 0)  // If walker's left child is empty, insert new node
				{
					pWalk->setLeftPtr(newNodePtr);
					count++;
					pWalk = 0; // End loop
				}
				else
				{
					pWalk = pWalk->getLeftPtr(); // If walker's left child is occupied, set walker to it
				}
			}
			else
			{
				if (pWalk->getRightPtr() == 0) // If walker's right child is empty, insert new node
				{
					pWalk->setRightPtr(newNodePtr);
					count++;
					pWalk = 0; // End loop
				}
				else
				{
					pWalk = pWalk->getRightPtr(); // If walker's right child is occupied, set walker to it
				}
			}
		}

		newNodePtr->setLeftPtr(0);
		newNodePtr->setRightPtr(0);
	}

	return 0;
}

CustomerNode *BinarySearchTree::_remove(CustomerNode *nodePtr, const std::string target, bool &success)
{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (nodePtr->getSsn() > target)
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getSsn() < target)
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

CustomerNode *BinarySearchTree::deleteNode(CustomerNode *nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		CustomerNode *nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		CustomerNode *nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		std::string newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setSsn(newNodeValue);
		return nodePtr;
	}
}

CustomerNode *BinarySearchTree::removeLeftmostNode(CustomerNode *nodePtr, std::string &successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getSsn();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

CustomerNode *BinarySearchTree::findNode(CustomerNode *nodePtr, const std::string targetSsn, std::string &name, bool &result) const
{
	CustomerNode *pWalk = nodePtr;

	while (pWalk != 0)
	{
		if (targetSsn == pWalk->getSsn())
		{
			name = pWalk->getName();
			result = true;
			return 0;
		}
		else if (targetSsn < pWalk->getSsn())
		{
			pWalk = pWalk->getLeftPtr();
		}
		else
		{
			pWalk = pWalk->getRightPtr();
		}
	}
	return 0;
}

CustomerNode *BinarySearchTree::_getSmallest(CustomerNode *nodePtr, std::string &foundID) const
{
	CustomerNode *pWalk = nodePtr; // Initialize walker with root node

	while (pWalk->getLeftPtr() != 0) // Move walker to the leftmost node
	{
		pWalk = pWalk->getLeftPtr();
	}

	foundID = pWalk->getSsn();

	return 0;
}

CustomerNode *BinarySearchTree::_getLargest(CustomerNode *nodePtr, std::string &foundID) const
{
	CustomerNode *pWalk = nodePtr; // Initialize walker with root node

	while (pWalk->getRightPtr() != 0) // Move walker to the rightmost node
	{
		pWalk = pWalk->getRightPtr();
	}

	foundID = pWalk->getSsn();

	return 0;
}

#endif
