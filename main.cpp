// main function
// Johnny Nguyen
// IDE: Microsoft Visual Studio

#include "stdafx.h" // Required for Microsoft Visual Studio

#include "BinarySearchTree.h" // Binary Search Tree ADT

void displaySsn(std::string &ssn);

int main()
{
	BinarySearchTree *customerTree = new BinarySearchTree();

	system("pause");
	return 0;
}

/*****************************************************************************
display function: Display social security number
*****************************************************************************/
void displaySsn(std::string &ssn)
{
	std::cout << ssn << " ";
}