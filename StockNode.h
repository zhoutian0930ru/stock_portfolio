//StockNode.h
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#ifndef STOCKNODE_H
#define STOCKNODE_H

#include<string>
using namespace std;

#include"StockAccount.h"

class StockNode
{
	friend class StockAccount;
public:
	StockNode(string name, float price, int num)
		:stockName(name), stockPrice(price), stockNum(num) {
		this->next = NULL;
		this->previous = NULL;
	}
	void addNum(int add)
	{
		stockNum = stockNum + add;
	}
	void setPrice(float price)
	{
		stockPrice = price;
	}
	float totalPrice()
	{
		return stockPrice*stockNum;
	}
	~StockNode() {}
private:
	string stockName;
	float stockPrice;
	int stockNum;
	StockNode *next;
	StockNode *previous;
};

#endif 
