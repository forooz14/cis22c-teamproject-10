// Node for binary tree
// Student: Johnny Nguyen
// IDE: Microsoft Visual Studio

#ifndef _CUSTOMER_NODE
#define _CUSTOMER_NODE

#include <string>

class CustomerNode
{
private:
	std::string ssn; // Unique variable for social security number
	std::string name; // Secondary variable for customer's name
	double checking; // Variable for checking account balance
	double savings; // Variable for savings account balance
	int score; // Variable for credit score

	CustomerNode *leftPtr; // Pointer to left child
	CustomerNode *rightPtr; // Pointer to right child

public:
	// Constructors
	CustomerNode(const std::string &inputSsn, const std::string &inputName, const double &inputChecking, const double &inputSavings, const int &inputScore)
	{
		ssn = inputSsn;
		name = inputName;
		checking = inputChecking;
		savings = inputSavings;
		score = inputScore;

		leftPtr = 0;
		rightPtr = 0;
	}

	CustomerNode(const std::string &inputSsn, const std::string &inputName, const double &inputChecking, const double &inputSavings, const int &inputScore, CustomerNode *left, CustomerNode *right)
	{
		ssn = inputSsn;
		name = inputName;
		checking = inputChecking;
		savings = inputSavings;
		score = inputScore;

		leftPtr = left;
		rightPtr = right;
	}

	// Accessors
	void setSsn(const std::string &inputSsn)
	{ssn = inputSsn;}

	void setName(const std::string &inputName)
	{name = inputName;}

	void setChecking(const double &inputChecking)
	{checking = inputChecking;}

	void setSavings(const double &inputSavings)
	{savings = inputSavings;}

	void setScore(const int &inputScore)
	{score = inputScore;}

	void setLeftPtr(CustomerNode *left)
	{leftPtr = left;}

	void setRightPtr(CustomerNode *right)
	{rightPtr = right;}

	// Mutators
	std::string getSsn() const
	{return ssn;}

	std::string getName() const
	{return name;}

	double getChecking() const
	{return checking;}

	double getSavings() const
	{return savings;}

	int getScore() const
	{return score;}

	CustomerNode *getLeftPtr() const
	{return leftPtr;}

	CustomerNode *getRightPtr() const
	{return rightPtr;}

	bool isLeaf() const 
	{return (leftPtr == 0 && rightPtr == 0);}

};

#endif