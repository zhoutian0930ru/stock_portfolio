//Account.cpp
//Name:Zhou Tian
//Course:16:332:503,Programming Finance
//Date of submission:2017/12/11
//Example:Final Project

#include"Account.h"

Account::Account() {

}

Account::~Account() {

}

float Account::getBalance() {
	return cashBalance;
}
void Account::addBalance(float add) {
	cashBalance = cashBalance + add;
}
void Account::setBalance(float balance) {
	cashBalance = balance;
}