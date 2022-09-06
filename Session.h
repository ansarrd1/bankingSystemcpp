#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED

#include "globalData.h"
using namespace std;

class Session : public globalData
{
    void withdrawCash();
    void depositCash();
    void modifyPinCode(string newPin);
    void showBalance();
    void transferBetweenAccounts(list<string>& database);
    void endSession();
    bool isNewUser(string pinCode);
    bool isValidPinCode(string pinCode);
    void askPinCode();
    void mainMenu();
    void updateDatabase(string option, User user);
    bool isValidNumber(string);
    string setCommas(string num);
public:
    void askLoginData();
    Session();
};


#endif // SESSION_H_INCLUDED
