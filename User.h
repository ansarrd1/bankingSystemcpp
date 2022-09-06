#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include <iostream>
using namespace std;

class User
{
private:
    string name;
    string cardNumber;
    string pinCode;
    string balance;
    string bankID;
    string lastTransaction;
    int positionInDatabase;
public:
    //constructors
    User();
    //setters
    void setBankID(string ID);
    void setName(string name);
    void setCardNumber(string cardNumber);
    void setPinCode(string pinCode);
    void setBalance(string balance);
    void setLastTransaction(string lastTransaction);
    void setPositionInDataBase(int pos);

    //getters
    string getBankID();
    string getName();
    string getCardNumber();
    string getPinCode();
    string getBalance();
    string getLastTransaction();
    int getPositionInDatabase();

    //operator override
    bool operator > (string& amount);
    string operator - (string& amount);
    string operator + (string& amount);
};

#endif // USER_H_INCLUDED
