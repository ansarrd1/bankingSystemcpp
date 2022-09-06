#include <stdlib.h>
#include <iostream>

using namespace std;
class activateBeforeWithdraw: public exception
{
public:
    const char* what() const throw()
    {
        system("CLS");
        return " - Activate your account before withdrawing cash. Please select option 3";
    }
};

class activateBeforeDeposit: public exception
{
public:
    const char* what() const throw()
    {
        system("CLS");
        return " - Activate your account before depositing cash. Please select option 3";
    }
};

class activateBeforeTransfer: public exception
{
public:
    const char* what() const throw()
    {
        system("CLS");
        return " - Activate your account before transferring cash. Please select option 3";
    }
};
