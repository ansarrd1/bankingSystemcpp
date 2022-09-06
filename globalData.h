#ifndef METHODS_H_INCLUDED
#define METHODS_H_INCLUDED

#include <iostream>
#include <list>
using namespace std;

class globalData
{
protected:
    User user;
    User benefUser;
    int mainMenuCounter;
    list<string>::iterator current;
    list<string>::iterator benefCurrent;
    list<string> database;
    globalData();
    bool isNew;
};

#endif // METHODS_H_INCLUDED
