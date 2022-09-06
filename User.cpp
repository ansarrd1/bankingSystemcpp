#include <iostream>
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

//constructors
User::User()
{
    name.clear();
    cardNumber.clear();
    pinCode.clear();
    balance.clear();
    bankID.clear();
    lastTransaction.clear();
}

//setters
void User::setBankID(string bankID)
{
    this-> bankID = bankID;
}
void User::setName(string name)
{
    this->name = name;
}
void User::setCardNumber(string cardNumber)
{
    this->cardNumber = cardNumber;
}
void User::setPinCode(string pinCode)
{
    this-> pinCode = pinCode;
}
void User::setBalance(string balance)
{
    this-> balance = balance;
}
void User::setLastTransaction(string lastTransaction)
{
    this-> lastTransaction = lastTransaction;
}
void User::setPositionInDataBase(int pos)
{
    this-> positionInDatabase = pos;
}


//getters
string User::getBankID()
{
    return this-> bankID;
}
string User::getName()
{
    return this->name;
}
string User::getCardNumber()
{
    return this-> cardNumber;
}
string User::getPinCode()
{
    return this-> pinCode;
}
string User::getBalance()
{
    return this-> balance;
}
string User::getLastTransaction()
{
    return this-> lastTransaction;
}
int User::getPositionInDatabase()
{
    return this-> positionInDatabase;
}

//operator override
bool User::operator > (string& amount)
{
    if (amount[0] <49 || amount[0] > 57) return false;
    if (stold(amount) > stold(this->balance))
    {
        return false;
    }
    return true;
}

string User::operator - (string& amount)
{
    long double temp;
    temp = stold(this->balance) - stold(amount);
    stringstream s("");
    string output;
    s << fixed << setprecision(2) << temp;
    s >> output;
    return output;
}

string User::operator + (string& amount)
{
    long double temp;
    temp = stold(this->balance) + stold(amount);
    stringstream s("");
    string output;
    s << fixed << setprecision(2) << temp;
    s >> output;
    return output;
}
