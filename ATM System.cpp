#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
void ShowMainMenueATM();
struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};
stClient FillClientInfo(stClient Client1)
{
    stClient C;
    C.AccountNumber = Client1.AccountNumber;
    C.PinCode = Client1.PinCode;
    C.Name = Client1.Name;
    C.Phone = Client1.Phone;
    C.AccountBalance = Client1.AccountBalance;
    return C;
}
stClient ConstClient;

void ShowQuickWithout();
void ShowNormalWithout();
vector<string> SpilaterWord(string S1, string Delim = "#//#")
{
    vector<string>vString;
    short Pos = 0;
    string sWord;
    while ((Pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, Pos);
        if (sWord != " ")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, Pos + Delim.length());
    }
    if (S1 != " ")
    {
        vString.push_back(S1);
    }
    return vString;
}
stClient ConvernLineToRecord(string S1, string Delim = "#//#")
{
    stClient Client;
    vector<string>vString;
    vString = SpilaterWord(S1, Delim);
    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stod(vString[4]);
    return Client;
}
bool ClientExistsByAccountNumber(string AccountNumber)
{
    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open("Bank2.txt", ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient ClinetRecord;
        while (getline(MyFile, Line))
        {
            ClinetRecord = ConvernLineToRecord(Line);
            if (ClinetRecord.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClient.push_back(ClinetRecord);
        }
        MyFile.close();
    }
    return false;
}
stClient FillstClient()
{
    stClient Client;
    cout << "Enter AccountNumber : \n";
    getline(cin >> ws, Client.AccountNumber);

    cout << "Enter PinCode : \n";
    getline(cin, Client.PinCode);
    cout << "Enter Name : \n";
    getline(cin, Client.Name);
    cout << "Enter Phone : \n";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance : \n";
    cin >> Client.AccountBalance;
    return Client;
}
vector<stClient> ReadClientFromFile()
{
    vector<stClient>vClient;
    fstream MyFile;
    MyFile.open("Bank2.txt", ios::in);
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvernLineToRecord(Line);
            vClient.push_back(Client);
        }
        MyFile.close();
    }
    return vClient;
}
string RecordToLineClient(stClient Client, string Delim = "#//#")
{
    string Line;
    Line = Client.AccountNumber + Delim;
    Line += Client.PinCode + Delim;
    Line += Client.Name + Delim;
    Line += Client.Phone + Delim;
    Line += to_string(Client.AccountBalance);
    return Line;
}

void FillClientInFile(string Line)
{
    fstream MyFile;                //| ios::app
    MyFile.open("Bank2.txt", ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << Line << endl;
    }
    MyFile.close();
}

vector<stClient> SaveClientDatatToFile(vector<stClient>vClient)
{
    fstream MyFile;
    MyFile.open("Bank2.txt", ios::out);
    if (MyFile.is_open())
    {
        string Line;

        for (stClient& C : vClient)
        {
            if (ConstClient.AccountNumber == C.AccountNumber && ConstClient.PinCode == C.PinCode)
            {
                C = FillClientInfo(ConstClient);

            }
            Line = RecordToLineClient(C);
            MyFile << Line << endl;

        }
        MyFile.close();
    }
    return vClient;
}
string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Enter account number ? ";
    cin >> AccountNumber;
    return AccountNumber;
}
string ReadPincode()
{
    string PinCode;
    cout << "Enter Pin Code ? ";
    cin >> PinCode;
    return PinCode;
}
bool IsFoundAccountNumberAndPincodeInFile(string AccountNumber, string Pincode, stClient& Client)
{
    vector<stClient>vC = ReadClientFromFile();
    for (stClient C : vC)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == Pincode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode)
{

    if (IsFoundAccountNumberAndPincodeInFile(AccountNumber, PinCode, ConstClient))
    {
        return true;
    }
    return false;
}
void Login()
{
    bool LoginIsFaild = false;
    string AccountNumber, PinCode;
    do
    {
        system("cls");
        cout << "===================================\n";
        cout << "\tLogin Screen \n";
        cout << "===================================\n";
        if (LoginIsFaild)
        {
            cout << "Invlaid AccountNumber/Pincode!\n";
        }
        AccountNumber = ReadAccountNumber();
        PinCode = ReadPincode();
        LoginIsFaild = !LoadClientInfo(AccountNumber, PinCode);

    } while (LoginIsFaild);
    ShowMainMenueATM();
}
enum enQuickWithout {
    eChoice1 = 1, eChoice2 = 2, eChoice3 = 3,
    eChoice4 = 4, eChoice5 = 5, eChoice6 = 6,
    eChoice7 = 7, eChoice8 = 8, eExit = 9
};

enQuickWithout ReadNumberFromQuickWithout()
{
    short Number;
    do
    {
        cout << "Choose what to without from[1] to [8] ? ";
        cin >> Number;

    } while (Number < 1 || Number > 9);
    return (enQuickWithout)Number;
}
double WithoutAccountBalance(enQuickWithout QuickWithout)
{

    switch (QuickWithout)
    {
    case enQuickWithout::eChoice1:
    {

        if (ConstClient.AccountBalance < 20)
        {

            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 20;
        }

    }
    case enQuickWithout::eChoice2:
    {
        if (ConstClient.AccountBalance < 50)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 50;

        }

    }
    case enQuickWithout::eChoice3:
    {
        if (ConstClient.AccountBalance < 100)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 100;

        }

    }
    case enQuickWithout::eChoice4:
    {
        if (ConstClient.AccountBalance < 200)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 200;

        }

    }
    case enQuickWithout::eChoice5:
    {
        if (ConstClient.AccountBalance < 400)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 400;

        }

    }
    case enQuickWithout::eChoice6:
    {
        if (ConstClient.AccountBalance < 600)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 600;

        }

    }
    case enQuickWithout::eChoice7:
    {
        if (ConstClient.AccountBalance < 800)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 800;

        }

    }
    case enQuickWithout::eChoice8:
    {
        if (ConstClient.AccountBalance < 1000)
        {
            cout << "\nThe amount exceeds your balance, makeanother choice.\n";
            cout << "Press AnyKey to continue...";
            system("pause>0");
            ShowQuickWithout();

        }
        else
        {
            return ConstClient.AccountBalance -= 1000;

        }

    }

    }

}
void ShowWithoutMenue()
{
    cout << "===========================================\n";
    cout << "\tQuick Without \n";
    cout << "===========================================\n";
    cout << "\t[1] 20 \t [2] 50  \n";
    cout << "\t[3] 100\t [4] 200 \n";
    cout << "\t[5] 400\t [6] 600 \n";
    cout << "\t[7] 800\t [8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
}



bool QuickWithoutBalance(vector<stClient>& vC, enQuickWithout QuickWithout)
{
    if (QuickWithout == enQuickWithout::eExit)
    {
        ShowMainMenueATM();
    }
    char Pass;
    cout << "\nAre you sure you want perform this transaction? [Y | N]? ";
    cin >> Pass;
    if (toupper(Pass) == 'Y')
    {
        ConstClient.AccountBalance = WithoutAccountBalance(QuickWithout);

        SaveClientDatatToFile(vC);
        cout << "\nDone successfully, New balance is: " << ConstClient.AccountBalance << endl;
        return true;
    }
    else
    {
        cout << "\nNot successfully, balance is: " << ConstClient.AccountBalance << endl;
        return false;
    }

}
void ShowQuickWithout()//Choice 1 
{
    system("cls");
    ShowWithoutMenue();
    cout << "Your Balance is: " << ConstClient.AccountBalance << endl;
    vector<stClient> vC = ReadClientFromFile();
    enQuickWithout  Number = ReadNumberFromQuickWithout();
    QuickWithoutBalance(vC, Number);
}
short ReadWithout()
{
    short W;
    do
    {
        cout << "Enter an amount multiple of 5`s? ";
        cin >> W;
    } while (W % 5 != 0);
    return W;
}
double WithoutNormal(short W)
{
    return ConstClient.AccountBalance -= W;
}
bool NormalWithout(vector<stClient>& vC)
{

    short W = ReadWithout();
    char Pass;
    if (W > ConstClient.AccountBalance)
    {

        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press AnyKey to continue...";
        system("pause>0");
        ShowNormalWithout();

    }
    else
    {
        cout << "\nAre you sure you want perform this transaction? [Y | N]? ";
        cin >> Pass;
        if (toupper(Pass) == 'Y')
        {
            ConstClient.AccountBalance = WithoutNormal(W);

            SaveClientDatatToFile(vC);
            cout << "\nDone successfully, New balance is: " << ConstClient.AccountBalance << endl;
            return true;
        }
        else
        {
            cout << "\nNot successfully, balance is: " << ConstClient.AccountBalance << endl;
            return false;
        }

    }
}
void ShowNormalWithout() //Choice 2
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tNormal Without Screen\n";
    cout << "===========================================\n";
    vector<stClient>vC = ReadClientFromFile();
    NormalWithout(vC);
}
short ReadDeposit()
{
    unsigned short D;
    do
    {
        cout << "Enter a positive deposit amount? ";
        cin >> D;
    } while (D < 1);
    return D;
}
double Deposit(short D)
{


    return ConstClient.AccountBalance += D;

}
bool DepositScreen(vector<stClient>& vC)
{

    short D = ReadDeposit();
    char Pass;

    cout << "\nAre you sure you want perform this transaction? [Y | N]? ";
    cin >> Pass;
    if (toupper(Pass) == 'Y')
    {
        ConstClient.AccountBalance = Deposit(D);

        SaveClientDatatToFile(vC);
        cout << "\nDone successfully, New balance is: " << ConstClient.AccountBalance << endl;
        return true;
    }
    else
    {
        cout << "\nNot successfully, balance is: " << ConstClient.AccountBalance << endl;
        return false;
    }
}
void ShowDepositScreen() //Choice 3
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tDeposit Screen\n";
    cout << "===========================================\n";
    vector<stClient>vC = ReadClientFromFile();
    DepositScreen(vC);
}

void ShowCheckBalanceScreen() //choice 4
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tCheck Balance Screen\n";
    cout << "===========================================\n";

    cout << "Your Balance is: " << ConstClient.AccountBalance;

}
enum enMainMenuATM { eQuickWithout = 1, eNormalWithout = 2, eDeosit = 3, eCheckBalance = 4, LogOut = 5 };
void GoBackToMainMenueATM()
{
    cout << "\n\nPress any key to go back to main menue...";
    system("pause>0");
    ShowMainMenueATM();
}
short ReadNumberFromMainMenuATM()
{
    short Num;
    do
    {
        cout << "chhose what do you want to do? [1 - 5]? ";
        cin >> Num;
    } while (Num < 1 || Num > 5);
    return Num;
}
void PerformMainMenueATM(enMainMenuATM MainMenuATM)
{
    switch (MainMenuATM)
    {
    case enMainMenuATM::eQuickWithout:
    {
        system("cls");
        ShowQuickWithout();
        GoBackToMainMenueATM();
        break;
    }
    case enMainMenuATM::eNormalWithout:
    {
        system("cls");
        ShowNormalWithout();
        GoBackToMainMenueATM();
        break;
    }
    case enMainMenuATM::eDeosit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenueATM();
        break;
    }
    case enMainMenuATM::eCheckBalance:
    {
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToMainMenueATM();
        break;
    }
    case enMainMenuATM::LogOut:
    {
        Login();
        break;
    }
    }
}

void ShowMainMenueATM()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tATM main menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1]. Quick Without.\n";
    cout << "\t[2]. Normal Without.\n";
    cout << "\t[3]. Deposit.\n";
    cout << "\t[4]. Check Balance.\n";
    cout << "\t[5]. Logout.\n";
    cout << "===========================================\n";
    PerformMainMenueATM((enMainMenuATM)ReadNumberFromMainMenuATM());
}
int main()
{

    Login();
    return 0;
}
