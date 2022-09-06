#include <iostream>
#include <fstream>
#include "User.h"
#include "Session.h"
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include "exceptions.h"

using namespace std;

Session::Session()
{
    askLoginData();
}

void Session::askLoginData()
{
    for (int i=0; i != 1; i++)
    {
        //retrieve database
        int pos = 0;
        fstream file;
        string line;
        file.open("database.csv", ios::in);
        if (file.is_open())
        {
            while(getline(file,line))
            {
                line.push_back('\n');
                database.push_back(line);
            }
            file.close();
        }
        else
        {
            cout << " - Could not access database :(" << endl;
            break;
        }

        //check if the card number is present in the database
        string bankID, name, cardNumber, pinCode, balance, lastTransaction;
        string cardNumberInput, pinCodeInput;
        int counter=0;
        bool flag = false;
        cout << "                The Bank of <All Cash IT> " << endl<< endl;
        cout << " - Card number (6 digits): ";
        cin >> cardNumberInput;
        for (auto it = database.begin(); it!=database.end(); it++)
        {
            pos++;
            line = *it;
            bankID.clear();
            name.clear();
            cardNumber.clear();
            pinCode.clear();
            balance.clear();
            lastTransaction.clear();
            counter = 0;
            for (int i=0; i<line.length(); i++)
            {
                if (line[i]==',')
                {
                    counter ++;
                }
                if (counter==0)
                {
                    if (line[i]!=',')
                    {
                        bankID.push_back(line[i]);
                    }
                }
                if (counter==1)
                {
                    if (line[i]!=',')
                    {
                        name.push_back(line[i]);
                    }
                }
                if (counter==2)
                {
                    if (line[i]!=',')
                    {
                        cardNumber.push_back(line[i]);
                    }
                }
                if (counter==3)
                {
                    if (line[i]!=',')
                    {
                        pinCode.push_back(line[i]);
                    }
                }
                if (counter==4)
                {
                    if (line[i]!=',')
                    {
                        balance.push_back(line[i]);
                    }
                }
                if (counter==5)
                {
                    if (line[i]!=',')
                    {
                        lastTransaction.push_back(line[i]);
                    }
                }
            }
            if (cardNumberInput==cardNumber)
            {
                user.setBankID(bankID);
                user.setName(name);
                user.setPinCode(pinCode);
                user.setBalance(balance);
                user.setCardNumber(cardNumber);
                user.setLastTransaction(lastTransaction);
                flag = true;
                current = it;
                user.setPositionInDataBase(pos);
                break;
            }
        }

        if (flag == true)
        {
//        if (isNewUser(user.getPinCode()))
//        {
//            modifyPinCode();
//        }
//        else
//        {
//            mainMenuCounter = 0;
//            askPinCode();
//            if (mainMenuCounter++<1)
//            {
//                cout <<endl;
//                mainMenu();
//            }
//        }
            (isNewUser(user.getPinCode()))?isNew = true:isNew = false;
            mainMenuCounter = 0;
            if (isNew)
            {
                system("CLS");
                mainMenu();
            }
            else
            {
                askPinCode();
            }

        }
        else
        {
            cout << endl << " - Such user does not exist in the database"<< endl;
            cout << " - Would you like to enter the card number again? (Y/N): ";
            string option;
            option.clear();
            cin >> option;
            while (option != "Y" && option != "y" && option != "N" && option != "n")
            {
                cout << " - Please enter correct option: ";
                cin >> option;
            }
            if (option == "Y" || option == "y")
            {
                system("CLS");
                cout << endl;
                askLoginData();
            }
            else
            {
                cout << " - Program terminated" <<endl;
            }
        }
    }
}

bool Session::isNewUser(string pinCode)
{
    for (int i=0; i<pinCode.length(); i++)
    {
        if (pinCode[i]<48 || pinCode[i]>57)
        {
            return true;
        }
    }
    return false;
}

string Session::setCommas(string num)
{
    string result;
    string temp;
    temp.clear();
    result.clear();
    bool flag = false;
    bool isNegative = false;;
    int counter = 0;
    int dotPos = num.length();
    if(num[0] == '-')
    {
        for (int i = 1; i < num.length()-1; i++)
        {
            temp.push_back(char(num[i]));
        }
        isNegative = true;
        num = temp;
    }
    for(int i = num.length()-1; i >= 0; i--)
    {
        if(num[i] == 46)
        {
            flag = true;
            dotPos = i;
            break;
        }
    }
    if(flag)
    {
        for(int i = num.length()-1; i >= dotPos; i--)
        {
            result.push_back( char (num[i]));
        }
    }
    for(int i = dotPos-1; i >= 0; i--)
    {
        result.push_back(char (num[i]));
        if(++counter == 3)
        {
            counter = 0;
            if(i != 0)
            {
                result.push_back(',');
            }
        }
    }
    if(isNegative)
    {
        result.push_back('-');
    }

    for (int i = 0; i < result.length()/2; i++)
        swap(result[i], result[result.length() - i - 1]);

    return result;
}


bool Session::isValidPinCode(string pinCode)
{
    if(pinCode.length()!=4)
    {
        return false;
    }
    for(int i=0; i<pinCode.length(); i++)
    {
        if(pinCode[i]<48 || pinCode[i]>57)
        {
            return false;
        }
    }
    return true;
}

void Session::mainMenu()
{
    //if(!isNew) system("CLS");
    string option;
    option.clear();
    cout<< endl << "                The Bank of <All Cash IT> " << endl << endl << "    Select one of the following options: " <<endl << endl;
    cout<< "    1. Withdraw Cash                  2. Deposit Cash"<< endl;
    cout<< "    3. Modify PIN Code                4. Show Balance"<<endl;
    cout<< "    5. Transfer Between Accounts      6. End Session"<<endl << endl;
    cout<< "    Enter option number: ";
    cin >> option;
    cout << endl << endl;
    while (option.size()!=1 || option[0] < 49 || option[0] > 54)
    {
        cout << " - Enter valid option: ";
        cin>>option;
        cout << endl;
    }
    switch (stoi(option))
    {
    case 1:
        if(!isNew) system("CLS");
        withdrawCash();
        break;
    case 2:
        if(!isNew) system("CLS");
        depositCash();
        break;
    case 3:
    {
        system("CLS");
        cout<< "        The Bank of <All Cash IT> " << endl << endl;
        string pinCode;
        cout << " - New PIN: ";
        cin >> pinCode;
        while (!isValidPinCode(pinCode))
        {
            cout << " - Enter valid PIN: ";
            cin >> pinCode;
        }
        modifyPinCode(pinCode);
        break;
    }
    case 4:
        system("CLS");
        cout<< "        The Bank of <All Cash IT> " << endl << endl;
        showBalance();
        break;
    case 5:
        if(!isNew) system("CLS");
        transferBetweenAccounts(database);
        break;
    case 6:
        system("CLS");
        askLoginData();
    }
}

void Session::askPinCode()
{
    string pinCode;
    cout << " - PIN code (4 digits): ";
    cin >> pinCode;
    cout << endl;
    while(pinCode != user.getPinCode())
    {
        cout << " - The card number or PIN code is incorrect. Try again!" <<endl << endl;
        askLoginData();
        break;
    }
    mainMenuCounter = 0;
    mainMenu();
}

void Session::modifyPinCode(string newPin)
{
    user.setPinCode(newPin);
    updateDatabase("pinCode", user);
    isNew = false;
    cout << " - Would you like to return to the main menu? (Y/N): ";

    string option;
    option.clear();
    cin >> option;
    while (option != "Y" && option != "y" && option != "N" && option != "n")
    {
        cout << " - Please enter correct option: ";
        cin >> option;
    }
    if (option == "Y" || option == "y")
    {
        mainMenuCounter = 0;
        cout << endl <<endl;
        mainMenu();
    }
    else
    {
        askLoginData();
    }
}

void Session::updateDatabase(string option, User user)
{
    current = database.begin();
    advance(current, user.getPositionInDatabase()-1);
    database.erase(current);

    string temp = user.getBankID() + "," + user.getName() + "," + user.getCardNumber() + "," + user.getPinCode() + "," + user.getBalance() + "," + user.getLastTransaction();
    current = database.begin();
    advance(current, user.getPositionInDatabase()-1);
    database.insert(current, temp);

    ofstream file("database.csv", ios::out | ios::trunc);
    if(file.is_open())
    {
        for (auto it = database.begin(); it!=database.end(); it++)
        {
            file << *it;
        }
        file.close();

        if (option == "pinCode")
        {
            cout << " - New PIN was set correctly" <<endl << endl;
        }
        if (option == "withdraw")
        {
            cout << " - Cash withdrawn successfully!" <<endl << endl;
        }
        if (option == "deposit")
        {
            cout << " - Cash deposited successfully!" <<endl << endl;
        }
        file.close();
    }
    else
    {
        cout << "Database access error :(" << endl;
    }
}

void Session::depositCash()
{
    try
    {
        if (isNew)
        {
            exception* e = new activateBeforeDeposit;
            system("CLS");
            throw e;
        }
        cout<< "        The Bank of <All Cash IT> " << endl << endl;
        stringstream s("");
        string temp;
        temp.clear();

        string amountToDeposit;

        s << fixed << setprecision(2) << stold(user.getBalance());
        s >> temp;

        cout << " - Current balance: " << setCommas(temp) << " KZT" << endl;
        cout << endl;
        cout << " - Enter amount to deposit: ";
        cin >> amountToDeposit;
        while (!isValidNumber(amountToDeposit))
        {
            cout << " - Enter valid amount: ";
            cin >> amountToDeposit;
        }
        user.setLastTransaction(amountToDeposit + '\n');
        user.setBalance(user + amountToDeposit);
        updateDatabase("deposit", user);

        s.clear();
        temp.clear();
        s << fixed << setprecision(2) << stold(user.getBalance());
        s >> temp;

        cout << " - Remaining balance: " <<  setCommas(temp) << " KZT" <<endl <<endl;

        cout << " - Would you like to return to the main menu? (Y/N): ";

        string option;
        option.clear();
        cin >> option;
        while (option != "Y" && option != "y" && option != "N" && option != "n")
        {
            cout << " - Please enter correct option: ";
            cin >> option;
        }
        if (option == "Y" || option == "y")
        {
            mainMenuCounter = 0;
            cout << endl <<endl;
            mainMenu();
        }
        else
        {
            system("CLS");
            askLoginData();
        }
    }
    catch (exception* e)
    {
        cout << e -> what() << endl << endl;
        mainMenu();
    }
}

void Session::withdrawCash()
{
    for (int i=0; i!=1; i++)
    {
        try
        {
            if (isNew)
            {
                exception* e = new activateBeforeWithdraw;
                system("CLS");
                throw e;
            }
            if (stold(user.getBalance())==0)
            {
                cout << " - Nothing to withdraw" <<endl;
                mainMenuCounter = 0;
                mainMenu();
                break;
            }
            cout<< "        The Bank of <All Cash IT> " << endl << endl;
            stringstream s("");
            string temp;
            temp.clear();
            s << fixed << setprecision(2) << stold(user.getBalance());
            s >> temp;

            string amountToWithdraw;
            cout << " - Current balance: " << setCommas(temp) << " KZT" << endl;
            cout << endl;
            cout << " - Enter amount to withdraw: ";
            cin >> amountToWithdraw;

            while (!(user > amountToWithdraw) || !isValidNumber(amountToWithdraw))
            {
                cout << " - Enter valid amount: ";
                cin >> amountToWithdraw;
            }
            user.setLastTransaction("-" + amountToWithdraw + '\n');
            user.setBalance(user - amountToWithdraw);
            updateDatabase("withdraw", user);

            s.clear();
            temp.clear();
            s << fixed << setprecision(2) << stold(user.getBalance());
            s >> temp;

            cout << " - Remaining balance: " << setCommas(temp) << " KZT" << endl << endl;

            cout << " - Would you like to return to the main menu? (Y/N): ";

            string option;
            option.clear();
            cin >> option;
            while (option != "Y" && option != "y" && option != "N" && option != "n")
            {
                cout << " - Please enter correct option: ";
                cin >> option;
            }
            if (option == "Y" || option == "y")
            {
                mainMenuCounter = 0;
                cout << endl <<endl;
                mainMenu();
            }
            else
            {
                system("CLS");
                askLoginData();
            }
        }
        catch (exception* e)
        {
            cout << e -> what() << endl << endl;
            mainMenu();
        }
    }
}

void Session::showBalance()
{
    stringstream s("");
    string temp;
    temp.clear();
    s << fixed << setprecision(2) << stold(user.getBalance());
    s >> temp;

    cout << " - Card owner: " << user.getName() << endl;
    cout << " - Card number: " << user.getCardNumber() << endl;
    cout << " - Card balance in KZT: " << setCommas(temp) << endl;

    s.clear();
    temp.clear();
    s << fixed << setprecision(2) << stold(user.getBalance())/450;
    s >> temp;

    cout << " - Card balance in USD: " << setCommas(temp) << endl;

    s.clear();
    temp.clear();
    s << fixed << setprecision(2) << stold(user.getLastTransaction());
    s >> temp;

    cout << " - Last transaction: " << setCommas(temp) << endl;

    cout << endl << " - Would you like to return to the main menu? (Y/N): ";
    string option;
    option.clear();
    cin >> option;
    while (option != "Y" && option != "y" && option != "N" && option != "n")
    {
        cout << " - Please enter correct option: ";
        cin >> option;
    }
    if (option == "Y" || option == "y")
    {
        system("CLS");
        mainMenuCounter = 0;
        cout << endl <<endl;
        mainMenu();
    }
    else
    {
        system("CLS");
        askLoginData();
    }
}

bool Session::isValidNumber(string number)
{
    if (number[0] < 49 || number[0] > 57) return false;
    int dotCounter = 0;
    int decimalCounter = 0;
    for (int i=0; i<number.length(); i++)
    {
        if (number[i] < 48 || number [i] > 57)
        {
            if (number[i]!=46)
            {
                return false;
            }
        }
        (dotCounter == 1)? decimalCounter++:decimalCounter+=0;
        (number[i]==46)?dotCounter++:dotCounter+=0;
    }
    if (stold(number) == 0)
    {
        return false;
    }
    if (stold(number) < 0)
    {
        return false;
    }
    if(dotCounter < 2 && decimalCounter <3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Session::transferBetweenAccounts(list<string>& database)
{
    for (int i = 0; i != 1; i++)
    {
        try
        {
            if (isNew)
            {
                exception* e = new activateBeforeTransfer;
                system("CLS");
                throw e;
            }
            if (stold(user.getBalance())==0)
            {
                cout << " - Nothing to transfer" <<endl;
                mainMenuCounter = 0;
                mainMenu();
                break;
            }
            cout<< "        The Bank of <All Cash IT> " << endl << endl;
            string amountToTransfer;
            string cardNumberInput;
            cout << "**Commission for fund transfers over 20000 KZT is 500 KZT" <<endl << endl;

            stringstream stream("");
            string temporary;
            temporary.clear();
            stream << fixed << setprecision(2) << stold(user.getBalance());
            stream >> temporary;
            cout << " - Card balance in KZT: " << setCommas(temporary) << endl;

            cout << " - Beneficiary's card number: ";
            cin >> cardNumberInput;
            while (cardNumberInput == user.getCardNumber())
            {
                cout << " - Cannot transfer to the same account. Enter another card number: ";
                cin >> cardNumberInput;
            }

            int benefPos = 0;
            fstream file;
            string line;
            file.open("database.csv", ios::in);
            if (file.is_open())
            {
                while(getline(file,line))
                {
                    line.push_back('\n');
                }
                file.close();
            }
            else
            {
                cout << " - Could not access database :(" << endl;
                break;
            }

            //check if the card number is present in the database
            string bankID, name, cardNumber, pinCode, balance, lastTransaction;
            int counter=0;
            bool flag = false;
            for (auto it = database.begin(); it!=database.end(); it++)
            {
                benefPos++;
                line = *it;
                bankID.clear();
                name.clear();
                cardNumber.clear();
                pinCode.clear();
                balance.clear();
                lastTransaction.clear();
                counter = 0;
                for (int i=0; i<line.length(); i++)
                {
                    if (line[i]==',')
                    {
                        counter ++;
                    }
                    if (counter==0)
                    {
                        if (line[i]!=',')
                        {
                            bankID.push_back(line[i]);
                        }
                    }
                    if (counter==1)
                    {
                        if (line[i]!=',')
                        {
                            name.push_back(line[i]);
                        }
                    }
                    if (counter==2)
                    {
                        if (line[i]!=',')
                        {
                            cardNumber.push_back(line[i]);
                        }
                    }
                    if (counter==3)
                    {
                        if (line[i]!=',')
                        {
                            pinCode.push_back(line[i]);
                        }
                    }
                    if (counter==4)
                    {
                        if (line[i]!=',')
                        {
                            balance.push_back(line[i]);
                        }
                    }
                    if (counter==5)
                    {
                        if (line[i]!=',')
                        {
                            lastTransaction.push_back(line[i]);
                        }
                    }
                }
                if (cardNumberInput==cardNumber)
                {
                    benefUser.setBankID(bankID);
                    benefUser.setName(name);
                    benefUser.setPinCode(pinCode);
                    benefUser.setBalance(balance);
                    benefUser.setCardNumber(cardNumber);
                    benefUser.setLastTransaction(lastTransaction);
                    flag = true;
                    benefCurrent = it;
                    benefUser.setPositionInDataBase(benefPos);
                    break;
                }
            }

            if (flag == true)
            {
                long double a = 0, b = 0, tempD = 0;
                string option, temp = "";
                stringstream s("");
                cout << " - Transfer amount (in KZT): ";
                cin >> amountToTransfer;

                while (!(user > temp) || !isValidNumber(amountToTransfer))
                {
                    cout << " - Enter valid amount: ";
                    cin >> amountToTransfer;
                    if(isValidNumber(amountToTransfer))
                    {
                        (stold(amountToTransfer) > 20000)?a = 500:a = 0;
                        (user.getBankID() != benefUser.getBankID())?b = 200:b = 0;
                        tempD = stold(amountToTransfer) + a + b;
                        s.clear();
                        s << fixed << setprecision(2) << tempD;
                        temp.clear();
                        s >> fixed >> setprecision(2) >> temp;
                    }
                }

                cout << endl << " - Beneficiary's name: " << benefUser.getName() << endl;
                cout << " - Confirm transfer? (Y/N): ";
                option.clear();
                cin >> option;
                while (option != "Y" && option != "y" && option != "N" && option != "n")
                {
                    cout << " - Please enter correct option: ";
                    cin >> option;
                }
                if (option == "Y" || option == "y")
                {
                    user.setBalance(user - temp);
                    benefUser.setBalance(benefUser + amountToTransfer);
                    user.setLastTransaction("-" + amountToTransfer + '\n');
                    benefUser.setLastTransaction(amountToTransfer + '\n');

                    updateDatabase("", user);
                    updateDatabase("", benefUser);

                    cout << endl << " - Transfer successful!" <<endl;

                    cout << endl << " - Would you like to return to the main menu? (Y/N): ";
                    string option;
                    option.clear();
                    cin >> option;
                    while (option != "Y" && option != "y" && option != "N" && option != "n")
                    {
                        cout << " - Please enter correct option: ";
                        cin >> option;
                    }
                    if (option == "Y" || option == "y")
                    {
                        mainMenuCounter = 0;
                        system("CLS");
                        cout << endl <<endl;
                        mainMenu();
                    }
                    else
                    {
                        system("CLS");
                        askLoginData();
                    }
                }
                else
                {
                    mainMenuCounter = 0;
                    mainMenu();
                }
            }
            else
            {
                string option;
                cout << " - Such user does not exist in the database"<< endl;
                cout << " - Would you like to enter beneficiary's card number again? (Y/N): ";
                option.clear();
                cin >> option;
                while (option != "Y" && option != "y" && option != "N" && option != "n")
                {
                    cout << " - Please enter correct option: ";
                    cin >> option;
                }
                if (option == "Y" || option == "y")
                {
                    transferBetweenAccounts(database);
                }
                else
                {
                    cout << endl;
                    mainMenuCounter = 0;
                    mainMenu();
                }
            }
        }
        catch (exception* e)
        {
            cout << e -> what() << endl << endl;
            mainMenu();
        }
    }
}
