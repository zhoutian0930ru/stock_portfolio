//BankAccount.cpp
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#include "BankAccount.h"
#include<fstream>
#include<iomanip>
#include<string>
#include<time.h>
#include<iostream>
using namespace std;

BankAccount::BankAccount()
{
}

BankAccount::~BankAccount()
{
}

void BankAccount::deposit(float amount)
{
	const time_t t = time(NULL);
	struct tm* current_time = localtime(&t);
	ofstream history_out;
	history_out.open("bank_transaction_history.txt",ios::out|ios::app);
	addBalance(amount);
	if (history_out.is_open()) {		
		history_out << "Deposit" << "\t" << amount << "\t"
			<< 1 + current_time->tm_mon << "/" << current_time->tm_mday << "/" << 1900 + current_time->tm_year << "\t"
			<< getBalance() << endl;
	}
	history_out.close();
}

void BankAccount::withdraw(float amount)
{
	const time_t t = time(NULL);
	struct tm* current_time = localtime(&t);
	if (amount <= getBalance()) {
		ofstream history_out;
		history_out.open("bank_transaction_history.txt", ios::out | ios::app);
		addBalance(-amount);
		if (history_out.is_open()) {
			history_out << "Withdraw" << "\t" << amount << "\t"
				<< 1 + current_time->tm_mon << "/" << current_time->tm_mday << "/" << 1900 + current_time->tm_year << "\t"
				<< getBalance() << endl;
		}
		history_out.close();
	}
	else {
		cout << "The amount of cash balance is not enough to withdraw $" << amount << endl;
	}	
}

void BankAccount::print_bank_history()
{
	ifstream history_in;
	string event, date;
	float amount, balance;
	history_in.open("bank_transaction_history.txt", ios::in);
	cout << "Transaction history of bank account:" << endl
		<< setw(10) << "Event" << setw(10) << "Amount" << setw(16) << "Date" << setw(10) << "Balance" << endl;
	if (history_in.is_open()) {
		while (!history_in.eof()) {
			history_in >> event >> amount >> date >> balance;
			if (history_in.eof())
				break;
			cout << setw(10) << event << setw(10) << amount << setw(16) << date << setw(10) << balance << endl;
		}
	}
	history_in.close();

}