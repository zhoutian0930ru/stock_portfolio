//StockAccount.h
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include "Account.h"
#include "StockNode.h"
#include "PrintImpl.h"

class StockAccount :
	public Account
{
public:
	
	friend class StockNode;
	friend class PrintImpl;
	StockAccount();
	~StockAccount();

	int size();
	void setRightPrint(){
		delete printType;
		printType = new PrintRight;
	}
	void setLeftPrint() {
		delete printType;
		printType = new PrintLeft;
	}
	
	void addNodeSorted(StockNode*);
	void removeFromList(StockNode*);
	void buyShares(StockNode*);
	void sellShares(StockNode*);
	float findPrice(string);
	void outputToTxt();
	void output_TotalPortfolioValue();
	float getWorth();
	void plotValue();
	void sortInsertion();

	void printCurrent();
	void printTransaction();
	
private:
	StockNode *Head;
	StockNode *Tail;
	int mySize;
	PrintImpl *printType;
};

#endif // !STOCKACCOUNT_H