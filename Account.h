//Account.h
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
	Account();
	float getBalance();
	void addBalance(float);
	void setBalance(float);
	~Account();
protected:
	float cashBalance;
};

#endif