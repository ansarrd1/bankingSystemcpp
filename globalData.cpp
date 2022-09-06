#include <iostream>
#include <fstream>
#include "User.h"
#include "Session.h"
#include <iomanip>

#include "globalData.h"
using namespace std;

globalData::globalData()
{
    mainMenuCounter = 0;
    current = database.begin();
    benefCurrent = database.begin();
}
