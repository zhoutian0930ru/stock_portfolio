//PrintImpl.h
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#ifndef PRINTIMPL_H
#define PRINTIMPL_H

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class PrintImpl
{
public:
	PrintImpl::PrintImpl(){}
	virtual void printTransaction(string, string, int, float, float, string) = 0;
};

class PrintLeft :public PrintImpl {
public:
	PrintLeft::PrintLeft(){}
	void printTransaction(string event, string name, int num, float price, float total, string time) {
		cout << setw(10) << setiosflags(ios::left) << event
			<< setw(15) << setiosflags(ios::left) << name
			<< setw(10) << setiosflags(ios::left) << num
			<< "$" << setw(14) << setiosflags(ios::left) << price
			<< "$" << setw(14) << setiosflags(ios::left) << total
			<< setw(10) << setiosflags(ios::left) << time << endl;
	}
};

class PrintRight :public PrintImpl {
public:
	PrintRight::PrintRight() {}
	void printTransaction(string event, string name, int num, float price, float total, string time) {
		cout << setw(10) << setiosflags(ios::right) << event
			<< setw(15) << setiosflags(ios::right) << name
			<< setw(10) << setiosflags(ios::right) << num
			<< "$" << setw(14) << setiosflags(ios::right) << price
			<< "$" << setw(14) << setiosflags(ios::right) << total
			<< setw(10) << setiosflags(ios::right) << time << endl;
	}
};

#endif // !PRINTIMPL_H