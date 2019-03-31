//Account_Management_System.cpp(main.cpp)
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#include "Account.h"
#include "BankAccount.h"
#include "StockAccount.h"
#include "StockNode.h"

#include<string>
#include<fstream>
#include<iostream>
#include<time.h>
using namespace std;

#include<stdio.h>
#include<stdlib.h>

int main() {
	
//1.decide which result of price will use and record.
	int randNum;
	srand((int)time(0));
	randNum = (rand() % 2);
	string readName, readDate;
	float readPrice;
	ifstream stockMessage;
	StockAccount Message;
	if (randNum == 1) {
		stockMessage.open("Result_1.txt",ios::in);
	}
	else {
		stockMessage.open("Result_2.txt",ios::in);
	}

	if (stockMessage.is_open())
	{
		while (!stockMessage.eof()) {
			stockMessage >> readName >> readPrice >> readDate;
			StockNode *read1 = new StockNode(readName, readPrice, 1);
			Message.addNodeSorted(read1);		
		}//end while
	}//end if
	stockMessage.close();

//2.read the portfolio information from txt file.(build portfolio linked list)
	float cashBalance;
	string portfolioName;
	int portfolioNum;
	ifstream portfolioRecord_in("portfolioRecord.txt",ios::in);	

	StockAccount portfolio;

	if (portfolioRecord_in.is_open()) {
		portfolioRecord_in >> cashBalance;
		while (!portfolioRecord_in.eof()) {
			portfolioRecord_in >> portfolioName >> portfolioNum;
			if (portfolioRecord_in.eof())
				break;
			StockNode *readMessage = new StockNode(portfolioName, Message.findPrice(portfolioName), portfolioNum);
			portfolio.addNodeSorted(readMessage);
		}
		portfolio.addBalance(cashBalance);
	}
	else {
		portfolio.addBalance(10000);
	}
	portfolio.output_TotalPortfolioValue();

//3.Build bank account
	BankAccount *bankAccount = new DecorateTime(new BankAccount);
	bankAccount->setBalance(portfolio.getBalance());

//4.Start run the manu.
	float Balance = portfolio.getBalance();
	int choiceFirst, choiceSecond;
	do{
		cout << "Welcome to the Account Management System." << endl;
		cout << "Please select an account to access:" << endl
			<< "1.Stock Portfolio Account" << endl
			<< "2.Bank Account" << endl
			<< "3.Exit" << endl << endl;
		cout << "Option: ";
		cin >> choiceFirst;
		while (choiceFirst < 1 || choiceFirst > 3) {
			cout << "Option: ";
			cin >> choiceFirst;
		}
		switch (choiceFirst)
		{
		case 1://Stock Portfolio Account
			do {
				cout << "Stock Portfolio Account" << endl
					<< "Please select an option:" << endl
					<< "1.Display the price for a stock symbol" << endl
					<< "2.Display the current portfolio" << endl
					<< "3.Buy shares" << endl
					<< "4.Sell shares" << endl
					<< "5.View a graph for the portfolio value" << endl
					<< "6.View transaction history" << endl
					<< "7.Return to previous menu" << endl << endl;
				cout << "Option: ";
				cin >> choiceSecond;
				while (choiceSecond < 1 || choiceSecond > 7) {
					cout << "Option: ";
					cin >> choiceSecond;
				}
				
				string symbol;
				int Num_shares;
				float max_per_share;
				StockNode *newShares;
				switch (choiceSecond)
				{
				case 1://Display the price for a stock symbol	
					cout << "Please enter the stock symbol: ";
					cin >> symbol;
					cout << "Company Symbol Price per share" << endl
						<< symbol << " $" << Message.findPrice(symbol) << endl << endl;
					break;
				case 2://Display the current portfolio
					portfolio.printCurrent();
					break;
				case 3://Buy shares
					cout << "Please enter the stock symbol you wish to purchase:";
					cin >> symbol;
					cout << "Please enter the number of shares: ";
					cin >> Num_shares;
					cout << "Please enter the maximum amount you are willing to pay per share: ";
					cin >> max_per_share;
					if (Message.findPrice(symbol) <= max_per_share) {
						newShares = new StockNode(symbol, Message.findPrice(symbol), Num_shares);
						portfolio.buyShares(newShares);
						cout << endl;
					}
					else {
						cout << "The price of " << symbol << " at $" << Message.findPrice(symbol)
							<< " is larger than the maximum ammout you are willing to pay per share." << endl << endl;
					}
					portfolio.outputToTxt();
					break;
				case 4://Sell shares
					cout << "Please enter the stock symbol you wish to sell:";
					cin >> symbol;
					cout << "Please enter the number of shares: ";
					cin >> Num_shares;
					newShares = new StockNode(symbol, Message.findPrice(symbol), Num_shares);
					portfolio.sellShares(newShares);
					cout << endl;
					portfolio.outputToTxt();
					break;
				case 5://View a graph for the portfolio value
					portfolio.plotValue();
					break;
				case 6://View transaction history
					portfolio.setLeftPrint();
					portfolio.printTransaction();
					break;
				case 7://Return to previous menu
					break;
				}//end switch choiceSecond
			} while (choiceSecond != 7);
			Balance = portfolio.getBalance();
			break;
		case 2://Bank Account
			do{
				cout << "Bank Account" << endl
					<< "Please select an option:" << endl
					<< "1.View account balance" << endl
					<< "2.Deposit money" << endl
					<< "3.Withdraw money" << endl
					<< "4.Print out history" << endl
					<< "5.Return to previous menu" << endl;
				cout << "Option: ";
				cin >> choiceSecond;
				while (choiceSecond < 1 || choiceSecond>5) {
					cout << "Option: ";
					cin >> choiceSecond;
				}//end while
				float amount;
				switch (choiceSecond)
				{
				case 1://View account balance
					cout << "You have $" << bankAccount->getBalance() << "in your bank account." << endl;
					cout << endl;
					break;
				case 2://Deposit money
					cout << "Please select the amount you wish to deposit: $";
					cin >> amount;
					bankAccount->deposit(amount);
					portfolio.setBalance(bankAccount->getBalance());
					portfolio.output_TotalPortfolioValue();
					break;
				case 3://Withdraw money
					cout << "Please select the amount you wish to withdraw: $";
					cin >> amount;
					bankAccount->withdraw(amount);
					portfolio.setBalance(bankAccount->getBalance());
					portfolio.output_TotalPortfolioValue();
					break;
				case 4://Print out history
					bankAccount->print_bank_history();
					cout << endl;
					break;
				case 5://Return to previous menu
					break;
				}
			} while (choiceSecond != 5);
			Balance = bankAccount->getBalance();
			break;
		case 3:
			break;
		}//end switch choiceFirst
		
		portfolio.setBalance(Balance);
		bankAccount->setBalance(Balance);
	} while (choiceFirst != 3);
	
//5.output the doubly linked list to txt file.
	//portfolio.output_TotalPortfolioValue();
	portfolio.outputToTxt();
	system("pause");
	return 0;
}