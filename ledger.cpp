#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

struct Account
{
    char Title[20];
    int Account_number;
    bool Premium;
    double Balance;
    Account* Next;
};

Account** ledger = new Account * [8] {0}; // Array of pointers of data type account

bool withdraw(char title[], int account_number, double amount);
void populate(); // create and store data as shown, set balance for all accounts to 100
void display_ledger(); // display the whole ledger in given format

int main()
{
    populate();

    char Tayyab[] = "Tayyab";
    char Alex[] = "Alex";
    char Jeff[] = "Jeff";
    char Xavier[] = "Xavier";

    withdraw(Tayyab, 1, 80);
    withdraw(Alex, 2, 48.5);
    withdraw(Tayyab, 3, 64.29);
    // or withdraw(Jeff, 3, 65.53);
    withdraw(Xavier, 4, 87.57);

    display_ledger();

    return 0;
}

void populate()
{
    ledger[0] = new Account;
    strcpy(ledger[0]->Title, "Tayyab");
    ledger[0]->Account_number = 1;
    ledger[0]->Premium = true;
    ledger[0]->Balance = 100;

    ledger[1] = new Account;
    strcpy(ledger[1]->Title, "Alex");
    ledger[1]->Account_number = 2;
    ledger[1]->Premium = false;
    ledger[1]->Balance = 100;

    ledger[2] = new Account;
    strcpy(ledger[2]->Title, "Jeff");
    ledger[2]->Account_number = 3;
    ledger[2]->Premium = false;
    ledger[2]->Balance = 100;

    ledger[3] = new Account;
    strcpy(ledger[3]->Title, "Xavier");
    ledger[3]->Account_number = 4;
    ledger[3]->Premium = false;
    ledger[3]->Balance = 100;
    
    ledger[4] = new Account;
    strcpy(ledger[4]->Title, "Xavier");
    ledger[4]->Account_number = 5;
    ledger[4]->Premium = true;
    ledger[4]->Balance = 100;

    ledger[0]->Next = ledger[2];
    ledger[1]->Next = NULL;
    ledger[2]->Next = NULL;
    ledger[3]->Next = ledger[4];
    ledger[4]->Next = ledger[3];
}

bool withdraw(char title[], int account_number, double amount)
{
    // 1: Find the account
    Account* target = NULL;
    for (int i = 0; ledger[i] != NULL; i++)
    {
        if (ledger[i]->Account_number == account_number)
        {
            target = ledger[i];
            break;
        }
    }

    if (target == NULL) return false;

    // 2: Check if title is direct owner or shared
    bool is_direct = (strcmp(target->Title, title) == 0);
    bool is_shared = false;

    if (!is_direct)
    {
        for (int i = 0; ledger[i] != NULL; i++)
        {
            if (strcmp(ledger[i]->Title, title) == 0 && ledger[i]->Next == target)
            {
                is_shared = true;
                break;
            } 
        }
    }

    if (!is_direct && !is_shared) return false;

    // 3: Calculate fees
    double fee = 0.0;
    if (is_shared)
    {
        fee += 0.02;
    }
    if (target->Premium == false)
    {
        fee += 0.03;
    }
    
    // 4: Deduct from Balance
    double deduct = fee * amount + amount;

    if (target->Balance < deduct) return false;
    target->Balance -= deduct;
    return true;
}

void display_ledger()
{
    for (int i = 0; ledger[i] != NULL; i++)
    {
        // skip the second account of a dual 
        if (ledger[i]->Next != NULL && strcmp(ledger[i]->Title, ledger[i]->Next->Title) == 0 && 
            ledger[i]->Next->Next == ledger[i])
        {
            if (ledger[i]->Account_number > ledger[i]->Next->Account_number)
            {
                continue; // skip the account with the bigger account number
            }
        }
        
        bool is_shared = false;
        bool is_dual = false;
        int sharer[7] = {-1,-1,-1,-1,-1,-1,-1}; 
        // to store the index of which accounts have access to the shared account
        
        for (int j = 0; ledger[j] != NULL; j++)
        {
            if (ledger[j] != ledger[i] && ledger[j]->Next == ledger[i])
            {
                if (ledger[i]->Next == ledger[j])
                {
                    is_dual = true;
                }
                else
                {
                    is_shared = true;
                    sharer[j] = j;
                }
            }
        }

        // 1: TITLE
        cout << "Title: " << ledger[i]->Title;
        if (is_shared)
        {
            for (int k = 0; k < 7; k++) // go over the array of shared account index
            {
                if (sharer[k] > -1)
                {
                    cout << "\t\t" << ledger[k]->Title << " (Shared)";
                }
            }
        }
        else if (is_dual) cout << " (Dual)";
        cout << endl;

        // 2: ACCOUNT
        cout << "Account # " << ledger[i]->Account_number;
        if (is_dual) cout << "\t\t" << ledger[i]->Next->Account_number;
        cout << endl;

        // 3: TYPE
        cout << "Type: ";
        if (ledger[i]->Premium) cout << "Premium";
        else cout << "Standard";

        if (is_dual)
        {
            cout << "\t\t";
            if (ledger[i]->Next->Premium) cout << "Premium";
            else cout << "Standard";
        }
        cout << endl;

        // 4: BALANCE
        cout << fixed << setprecision(2);
        cout << "Balance: $" << ledger[i]->Balance;
        if (is_dual) cout << "\t\t$" << ledger[i]->Next->Balance;
        cout << endl << endl;
    }
}