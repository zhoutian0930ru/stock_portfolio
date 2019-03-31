//StockAccount.cpp
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#include "StockAccount.h"

#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib")

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include <engine.h>

#include<fstream>
#include<cstring>
#include<iomanip>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

StockAccount::StockAccount()
{
	mySize = 0;
	printType = new PrintRight;
}

StockAccount::~StockAccount()
{
	StockNode *temp;
	temp = Head;
	if (size() == 1) {
		delete Head;
	}
	else {
		while (temp != 0) {
			temp = Head->next;
			delete Head;
			Head = temp;
		}
	}
}

int StockAccount::size()
{
	return mySize;
}

void StockAccount::addNodeSorted(StockNode *addPtr)
{
	StockNode *scanPtr;
	scanPtr = Head;
	//float scanPtrTotal = (scanPtr->stockNum)*(scanPtr->stockPrice);
	float addPtrTotal = (addPtr->stockNum)*(addPtr->stockPrice);

	if (Head==0) {
		Head = Tail = addPtr;
		Head->previous = 0;
		Tail->next = 0;
	}//end if
	else {
		if (addPtrTotal >= (Head->stockNum)*(Head->stockPrice)) {
			addPtr->next = Head;
			Head->previous = addPtr;
			Head = addPtr;
			Head->previous = 0;
		}//end if
		else {
			if (addPtrTotal < (Tail->stockNum)*(Tail->stockPrice)) {
				Tail->next = addPtr;
				addPtr->previous = Tail;
				Tail = addPtr;
				Tail->next = 0;
			}//end if
			else {
				while (addPtrTotal < (scanPtr->stockNum)*(scanPtr->stockPrice)) {
					scanPtr = scanPtr->next;

				}//end while
				StockNode *temp;
				temp = scanPtr->previous;
				addPtr->next = scanPtr;
				addPtr->previous = scanPtr->previous;
				temp->next = addPtr;
				scanPtr->previous = addPtr;
			}//end else
		}//end else
	}//end else	
	mySize++;
}

void StockAccount::removeFromList(StockNode *removePtr)
{
	StockNode *tempPtr;
	tempPtr = Head;
	if (removePtr == Head) {
		if (Head == Tail)
			Head = Tail = 0;
		else {
			Head = Head->next;
			Head->previous = 0;
		}//end else
	}//end if
	else {
		if (removePtr == Tail) {
			Tail = Tail->previous;
			Tail->next = 0;
		}//end if
		else {
			while (removePtr != tempPtr) {
				tempPtr = tempPtr->next;
			}//end while
			(tempPtr->previous)->next = tempPtr->next;
			(tempPtr->next)->previous = tempPtr->previous;

		}//end else		
	}//end else

	mySize--;
}

void StockAccount::buyShares(StockNode *newPtr)
{
	StockNode *modifiedPtr;
	modifiedPtr = newPtr;
	const time_t t = time(NULL);
	ofstream history_out;
	ofstream history_bank;

	if ((newPtr->stockPrice)*(newPtr->stockNum) > getBalance()) {
		cout << "The balance in the stock account is not enough to perchase shares." << endl;
	}//end if compare to the balance
	else {
		addBalance(-(newPtr->stockNum)*(newPtr->stockPrice));
		if (size() == 0) {
			Head = Tail = newPtr;
			mySize++;
		}
		else {
			//find out whether the new stock is in the list
			StockNode *scanPtr;
			scanPtr = Head;
			while(scanPtr!=0) {
				if (scanPtr->stockName.compare(newPtr->stockName) == 0) {
					scanPtr->addNum(newPtr->stockNum);
					modifiedPtr = scanPtr;
					removeFromList(modifiedPtr);
				}//endif: compare the stockName	
				scanPtr = scanPtr->next;
			}//end for loop
			addNodeSorted(modifiedPtr);
		}
		cout << "You have purchased " << newPtr->stockNum << " shares of " << newPtr->stockName
			<< " at $" << newPtr->stockPrice << " each for a total of $" << newPtr->totalPrice() << "." << endl;

		struct tm* current_time = localtime(&t);
		history_out.open("stock_transaction_history.txt", ios::out | ios::app);
		if (history_out.is_open()) {
			history_out << "Buy" << "\t"
				<< newPtr->stockName << "\t"
				<< newPtr->stockNum << "\t"
				<< newPtr->stockPrice << "\t"
				<< newPtr->totalPrice() << "\t"
				<< current_time->tm_hour << ":"
				<< current_time->tm_min << ":"
				<< current_time->tm_sec << endl;
		}
		history_out.close();
		
		history_bank.open("bank_transaction_history.txt", ios::out | ios::app);
		if (history_bank.is_open()) {
			history_bank << "Buyshares" << "\t"
				<< newPtr->totalPrice() << "\t"
				<< 1 + current_time->tm_mon << "/" << current_time->tm_mday << "/" << 1900 + current_time->tm_year << "\t"
				<< getBalance() << endl;
		}
		history_bank.close();
		output_TotalPortfolioValue();

	}//end else

}//end function buyShares

void StockAccount::sellShares(StockNode *newPtr)
{
	StockNode *scanPtr;
	StockNode *resultPtr;
	const time_t t = time(NULL);
	ofstream history_out;
	ofstream history_bank;
	resultPtr = 0;
	scanPtr = Head;
	while (scanPtr != 0) {
		if (scanPtr->stockName.compare(newPtr->stockName) == 0) {
			resultPtr = scanPtr;
		}//end if
		scanPtr = scanPtr->next;
	}//end while

	if (resultPtr != 0) {
		if (resultPtr->stockNum < newPtr->stockNum) {
			cout << "There are not enough " << newPtr->stockName << " shares in the account." << endl
				<< "Shares in the account: " << resultPtr->stockNum << endl;
		}
		else {
			if (resultPtr->stockNum > newPtr->stockNum) {
				resultPtr->addNum(-newPtr->stockNum);
				addBalance((newPtr->stockNum)*(newPtr->stockPrice));
				cout << "The shares sold out successfully." << endl;
			}//end if successful sold(sellNum < accountNum)
			else {
				removeFromList(resultPtr);
				addBalance((newPtr->stockNum)*(newPtr->stockPrice));
				cout << "The shares sold out successfully." << endl;
				delete resultPtr;
				mySize--;
			}//end else successful sold(sellNum = accountNum)
		}
		struct tm* current_time = localtime(&t);
		history_out.open("stock_transaction_history.txt", ios::out | ios::app);
		if (history_out.is_open()) {
			history_out << "Sell" << "\t"
				<< newPtr->stockName << "\t"
				<< newPtr->stockNum << "\t"
				<< newPtr->stockPrice << "\t"
				<< newPtr->totalPrice() << "\t"
				<< current_time->tm_hour << ":"
				<< current_time->tm_min << ":"
				<< current_time->tm_sec << endl;
		}
		history_out.close();

		history_bank.open("bank_transaction_history.txt", ios::out | ios::app);
		if (history_bank.is_open()) {
			history_bank << "Sellshares" << "\t"
				<< newPtr->totalPrice() << "\t"
				<< 1 + current_time->tm_mon << "/" << current_time->tm_mday << "/" << 1900 + current_time->tm_year << "\t"
				<< getBalance() << endl;
		}
		history_bank.close();
		output_TotalPortfolioValue();
	}//end if (resultPtr != 0)
	else {
		cout << "There is no " << newPtr->stockName << "shares in the account." << endl;
	}//end else
}//end function sellShares

float StockAccount::findPrice(string sampleName)
{
	StockNode *scanPtr;
	scanPtr = Head;
	while (scanPtr != 0) {
		if (scanPtr->stockName.compare(sampleName) == 0)
			return scanPtr->stockPrice;
		scanPtr = scanPtr->next;
	}	
	return 0;
}

void StockAccount::outputToTxt()
{
	StockNode *scanPtr;
	scanPtr = Head;
	ofstream portfolioRecord_out("portfolioRecord.txt", ios::out | ios::trunc);
	scanPtr = Head;
	if (portfolioRecord_out.is_open()) {
		portfolioRecord_out << getBalance() << endl ;
		while(scanPtr!=0){
			portfolioRecord_out << scanPtr->stockName << "\t" << scanPtr->stockNum << endl;
			scanPtr = scanPtr->next;
		}
	}
}

void StockAccount::output_TotalPortfolioValue()
{
	const time_t t = time(NULL);
	int time_in_day;
	struct tm* current_time = localtime(&t);

	time_in_day = current_time->tm_hour * 60 * 60 + current_time->tm_min * 60 + current_time->tm_sec;
	ofstream output;
	output.open("Total_Portfolio_Value_Path.txt", ios::out | ios::app);
	if (output.is_open()) {
		output << getWorth()+getBalance() << "\t" << time_in_day << endl;
	}
	output.close();
}

float StockAccount::getWorth()
{
	float total = 0;
	StockNode *scanPtr;
	scanPtr = Head;
	while (scanPtr != 0) {
		total = total + scanPtr->totalPrice();
		scanPtr = scanPtr->next;
	}
	return total;
}

void StockAccount::plotValue()
{
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL) {
		std::cout << "Error: Not Found" << std::endl;
		exit(1);
	}
	ifstream readValue;
	vector<float> pValue;
	readValue.open("Total_Portfolio_Value_Path.txt", ios::in);
	float totalValue;
	time_t t;
	if (readValue.is_open()) {
		while (!readValue.eof()) {
			readValue >> totalValue >> t;
			if (readValue.eof())
				break;
			pValue.push_back(totalValue);
		}
	}
	readValue.close();

	float *valuePtr = &pValue[0];
	mxArray *A;
	A = mxCreateDoubleMatrix(1, pValue.size(), mxREAL);
	memcpy((void *)mxGetPr(A), (void *)valuePtr, pValue.size() * sizeof(float));
	engPutVariable(ep, "xx", A);
	engEvalString(ep, "X=xx;");
	engEvalString(ep, "plot(X);");	//call plot function
	engEvalString(ep, "title('Plot of Total Portfolio value')");

	system("pause");

	//clean operation
	mxDestroyArray(A);
	engEvalString(ep, "close;");

	//close engine
	engClose(ep);
}

void StockAccount::sortInsertion()
{
	StockNode *tempHead;
	StockNode *tempPtr;
	if (Head != 0) {
		Tail = Head;
		tempHead = Head->next;
		Tail->next = 0;
		while (tempHead != 0) {
			tempPtr = tempHead->next;
			addNodeSorted(tempHead);
			tempHead = tempPtr;
		}
	}//end if not empty
}

void StockAccount::printCurrent()
{

	cout << "Cash balance: $" << getBalance() << endl;

	if (Head==0) {
		cout << "The current portfolio is empty\n\n";
		return;
	}
	else {
		StockNode *currentPtr = Head;
		cout << setw(15) << setiosflags(ios::left) << "Company-Symbol"
			<< setw(10) << setiosflags(ios::left) << "Number"
			<< setw(10) << setiosflags(ios::left) << "Price"
			<< setw(10) << setiosflags(ios::left) << "Total value" << endl;
		while (currentPtr!=0) {
			cout << setw(15) << currentPtr->stockName
				<< setw(10) << currentPtr->stockNum
				<< "$" <<setw(9)<< setiosflags(ios::left) << currentPtr->stockPrice
				<< setw(10) << setiosflags(ios::left) << currentPtr->totalPrice() << endl;
			currentPtr = currentPtr->next;
		}//end while	
	}//end else

	cout << "Total portfolio value: $" << getWorth()+getBalance() << endl << endl;

}//end print

void StockAccount::printTransaction()
{
	ifstream history_in;
	string event, name, time;
	int num;
	float price, total;
	history_in.open("stock_transaction_history.txt", ios::in);
	cout << "Transaction history of stock account:" << endl
		<< setw(10) << setiosflags(ios::left) << "Event" 
		<< setw(15) << setiosflags(ios::left) << "CompSymbol" 
		<< setw(10) << setiosflags(ios::left) << "Number"
		<< setw(15) << setiosflags(ios::left) << "PricePerShare" 
		<< setw(15) << setiosflags(ios::left) << "TotalValue" 
		<< setw(10) << setiosflags(ios::left) << "Time" << endl;
	if (history_in.is_open()&&history_in.good()) {
		while (!history_in.eof()) {
			history_in >> event >> name >> num >> price >> total >> time;
			if (history_in.eof())
				break;	
			printType->printTransaction(event, name, num, price, total, time);
		}//end whild
	}//end if
	history_in.close();
}