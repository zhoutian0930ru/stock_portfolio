//BankAccount.h
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Account.h"
#include<time.h>
#include<iostream>
using namespace std;

class BankAccount :
	public Account
{
public:
	BankAccount();
	~BankAccount();
	void deposit(float);
	void withdraw(float);
	void virtual print_bank_history();
private:

};

class DecorateTime :public BankAccount
{
public:
	DecorateTime(BankAccount *bankAccount):mybankAccount(bankAccount){}
	virtual void print_bank_history()
	{
		const time_t t = time(NULL);
		struct tm* current_time = localtime(&t);
		mybankAccount->print_bank_history();
		cout << "The current local time and date is: " << asctime(current_time);
	}
private:
	BankAccount *mybankAccount;
};



#endif // !BANKACCOUNT_H

/*
class Decorator :
	public Account
{
	Account* wid;
public:
	Decorator(Account *w){ 
		wid = w; 
	}
	void print_bank_history() {
		const time_t t = time(NULL);
		struct tm* current_time = localtime(&t);
		wid->print_bank_history();
		cout << "The current local time and date is: " << asctime(current_time) << endl;
	}
};
*/