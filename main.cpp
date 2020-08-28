#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <algorithm>
#include <cctype>
#include <unordered_map>

#include "account.h"

//one dark pro

std::string filename = "data.txt";
uint32_t choice; //used when getting input from the user
char letter[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char intNumber[10] = {'1','2','3','4','5','6','7','8','9','0'};
char number[11] = {'1','2','3','4','5','6','7','8','9','0','.'};
bool typing;
//used when creating a new acocunt
std::string first;
std::string last;
std::string newPin;


uint32_t accIncrement = 0; //contains the total number of accounts and will increase when new account is made
uint32_t accSelect = -1; //used to select the account when signing in

//sign in variables
bool signedIn = false, flag;
uint32_t transferSel;
double money = 0;



std::string transfer(std::unordered_map<uint32_t, Account> acc,uint32_t acc1, uint32_t acc2, double amount);
std::unordered_map<uint32_t, Account> loadAccounts(std::unordered_map<uint32_t, Account> accounts, std::string file);
void storeAccounts(std::unordered_map<uint32_t, Account> accounts , std::string file);
bool checkString(std::string input, char* type, char* end);
bool checkPin(std::string input, char* type, char* end);

int main() 
{
    std::unordered_map<uint32_t, Account> acc;
    bool working = true; //main loop control

    acc = loadAccounts(acc, filename);

    
    while (working)
    {   
        //main screen options
        //not signed in section handles all inputs
        if (!signedIn) 
        {
            choice = -1;

            while(choice < 0 || choice >= 3)
            {
                std::cout << "==============================\n";
                std::cout << "         ATM SERVICES         \n";
                std::cout << "0. Sign in\n";
                std::cout << "1. Create Account\n";
                std::cout << "2. Exit\n";
                
                //Check input for invalid characters
                std::string input;
                typing = true;
                while (typing){
                    std::cout << "Please select from above: \n";
                    std::cin >> input;
                    
                    char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                    typing = checkString(input, intNumber, end);
                }
                choice = stoi(input);

                //Check if trying to sign in with no accounts created
                if (choice == 0 && accIncrement == 0)
                {
                    std::cout << "There are no active accounts.\n";
                    std::cout << "Try creating a new one!\n";
                    choice = -1;
                }
            }
        
            
            

            //sign in, create account, exit screen
            switch (choice)
            {
                case 0: //Sign into account (change accSelect)
                {
                    std::cout << "=================================\n";
                    std::cout << "There are " << accIncrement << " active accounts\n";
                    accSelect = -1;
                    
                    while(accSelect < 0 || accSelect >= accIncrement)//cant select negative or above the total # of accounts
                    {  
                        std::string input;
                        typing = true;
                        //Check input for invalid characters first
                        while (typing)
                        {
                            std::cout << "Please enter your account number:\n";
                            std::cin >> input;
                            
                            char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                            typing = checkString(input, intNumber, end);
                        }
                        accSelect = stoi(input); //convert input to uint32_t after checking

                        if (accSelect < 0 || accSelect >= accIncrement)
                        { 
                            std::cout << "Account does not exist, try again\n";//display error message
                        }
                    }
                    //confirm correct pin to login, 3 attempts then kicked out
                    flag = false;
                    uint32_t attempts = 2;
                    uint32_t accPin;
                    while (!flag && attempts >= 0) 
                    {
                        std::string input;
                        typing = true;
                        //Check input for invalid characters first
                        while (typing)
                        {
                            std::cout << "Please enter your 5-digit pin:\n";
                            std::cin >> input;
                            
                            char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                            typing = checkPin(input, intNumber, end);
                        }
                        accPin = stoi(input); //convert input to uint32_t after checking
                        

                        flag = acc[accSelect].validatePin(accPin); //returns true when correct pin input

                        if (flag == false) 
                        {
                            std::cout << "Incorrect Pin. " << attempts << " remaining.\n";
                            attempts--;
                        } 
                        else 
                        {
                            flag = true;
                            signedIn = true;
                            std::cout << "\nLogin successful\n";
                        }
                    }
                    break;
                }
                case 1: //Create account
                {
                    std::cout << "=======================================\n";
                    std::cout << "           Account creation\n";

                    //Loop for first name input                                                         //if space entered it will take both name inputs at once
                    typing = true;
                    while (typing){
                        std::cout << "Please enter your first name: \n";
                        std::cin >> first;
                        
                        char* end = letter + sizeof(letter) / sizeof(letter[0]);
                        typing = checkString(first, letter, end);
                    }

                    //Loop for last name input (turn this into a function so its not repeated)
                    typing = true;
                    while (typing){
                        std::cout << "Please enter your last name: \n";
                        std::cin >> last;
                        
                        char* end = letter + sizeof(letter) / sizeof(letter[0]);
                        typing = checkString(last, letter, end);
                    }

                    typing = true;
                    while (typing){
                        std::cout << "Please create a 5 digit pin:\n";
                        std::cin >> newPin;
                        
                        char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                        typing = checkPin(newPin, intNumber, end);
                    }

                    uint32_t tempPin = std::stoi(newPin);
                    //check accIncrement if account number is used
                    if (acc[accIncrement].checkValid()) 
                    {
                        std::cout << accIncrement << std::endl;
                        accIncrement++;
                    }
                    acc[accIncrement] = Account(accIncrement, first, last, tempPin);
                    std::cout << "Your account number is: " << accIncrement << "\n";
                    accIncrement++;
                    break;
                }
                case 2:
                    //exit the program
                    working = false;
                    std::cout << "==============================\n";
                    std::cout << "      See you next time       \n";
                    std::cout << "==============================\n";
                    break;
                break;
            }
        }



        //signedIn choices
        while (signedIn){
            std::cout << "==============================\n";
            std::cout << "         USER SERVICES        \n";
            std::cout << "0. Check balance\n";
            std::cout << "1. Deposit\n";
            std::cout << "2. Withdraw\n";
            std::cout << "3. Transfer money\n";
            std::cout << "4. Sign out\n";
            choice = -1;

            while(choice < 0 || choice >= 5)//limit to the number of options listed above
            { 
                std::string input;
                typing = true;
                while (typing)
                {
                    std::cout << "Please select from above: \n";
                    std::cin >> input;
                    
                    char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                    typing = checkString(input, intNumber, end);
                }
                choice = stoi(input);
            }
            
            switch (choice){
                case 0:  
                {
                    //Check balance
                    acc[accSelect].showBalance();
                    break;
                }
                case 1: 
                {
                    //Deposit
                    std::cout << "\n";
                    std::string input;
                    typing = true;
                    double money;
                    //Check input for invalid characters first
                    while (typing)
                    {
                        std::cout << "Enter the amount you are depositing: \n";
                        std::cin >> input;
                        
                        char* end = number + sizeof(number) / sizeof(number[0]);
                        typing = checkString(input, number, end);
                    }
                    money = stod(input); //convert input to uint32_t after checking

                    acc[accSelect].deposit(money);
                    break;
                }
                case 2:  
                { //----------------------------------------------------------------------------------------- add limiter to not allow overdrafting
                    //Withdraw
                    std::cout << "\n";
                    std::string input;
                    typing = true;
                    double money;
                    //Check input for invalid characters first
                    while (typing)
                    {
                        std::cout << "Enter the amount you are withdrawing: \n";
                        std::cin >> input;
                        
                        char* end = number + sizeof(number) / sizeof(number[0]);
                        typing = checkString(input, number, end);
                        
                    }
                    money = stod(input); //convert input to uint32_t after checking
                    
                    acc[accSelect].withdraw(money); //withdraw

                    if (acc[accSelect].isBalanceNeg()) //if overdrafting
                    {
                        acc[accSelect].deposit(money); //undo withdraw
                        std::cout << "Invalid transaction, not enough money\n";
                    }
                    break;
                }
                case 3:  
                {
                    //Transfer
                    std::cout << "\n";
                    transferSel = -1;
                    
                    while(transferSel < 0 || transferSel >= accIncrement)//cant select negative or above the total # of accounts
                    {  
                        //get account num to transfer to
                        std::string input;
                        typing = true;
                        //Check input for invalid characters first
                        while (typing)
                        {
                            std::cout << "Enter the account number you would like to transfer to: \n";
                            std::cin >> input;

                            char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                            typing = checkString(input, intNumber, end);
                        }
                        transferSel = stoi(input); //convert input to uint32_t after checking

                        if (transferSel < 0 || transferSel >= accIncrement)
                        { 
                            std::cout << "Account does not exist, try again\n";//display error message
                        }
                    }

                    //Get amount to transfer
                    std::string input;
                    typing = true;
                    double money;
                    //Check input for invalid characters first
                    while (typing)
                    {
                        std::cout << "Enter the amount you are transfering: \n";
                        std::cin >> input;
                        
                        char* end = number + sizeof(number) / sizeof(number[0]);
                        typing = checkString(input, number, end);
                    }
                    money = stod(input); //convert input to uint32_t after checking

                    std::cout << std::fixed << std::setprecision(2) << transfer(acc, accSelect, transferSel, money);


                    break;
                }
                case 4:
                {
                    //Exit screen (entered from a sign in choice and will continue to loop in signedIn choices)
                    std::cout << "==============================\n";
                    std::cout << "Are you sure?\n";
                    std::cout << "0. Yes\n";
                    std::cout << "1. No\n";
                    choice = -1;

                    while(choice < 0 || choice >= 2)
                    {
                        std::string input;
                        typing = true;
                        while (typing)
                        {
                            std::cout << "Please select from above: \n";
                            std::cin >> input;
                            
                            char* end = intNumber + sizeof(intNumber) / sizeof(intNumber[0]);
                            typing = checkString(input, intNumber, end);
                        }
                        choice = stoi(input);
                    }

                    if (choice == 0) 
                        signedIn = false;

                    break;
                }
                break;
            }
        }

    }
    
    //update data in textfile
    storeAccounts(acc, filename);
    return 0;
}

//transfer money from acc1 to acc2, cancel if not enough money
std::string transfer(std::unordered_map<uint32_t, Account> acc, uint32_t acc1, uint32_t acc2, double amount)
{
    acc[acc1].withdraw(amount);

    if (acc[acc1].isBalanceNeg())
    {
        acc[acc1].deposit(amount); //account went negative so undo the withdraw
        return "Not enough money for transfer.\n";
    }

    acc[acc2].deposit(amount);
    std::string out = "Transfered $";
    out.append(std::to_string(amount));
    out.append("\n");
    return out;
}

//given a file name and hash map, load data into the hash map
std::unordered_map<uint32_t, Account> loadAccounts(std::unordered_map<uint32_t, Account> accounts, std::string file)
{
    //read in from file
    std::ifstream infile;
    std::string line;
    infile.open(file);
    while (std::getline(infile, line))
    {
        std::istringstream  iss(line);
        //temporary input file variables
        std::string fileFname;
        std::string fileLname;
        uint32_t filePin;
        double fileBalance;

        if (!(iss >> accIncrement >> fileFname >> fileLname >> filePin >> fileBalance)) 
            break; //error

        Account account(accIncrement,fileFname, fileLname, filePin);
        //acc[accIncrement] = Account(accIncrement,fileFname, fileLname, filePin);
        accounts[accIncrement] = account;
        accounts[accIncrement].deposit(fileBalance);
        accIncrement++;
    }
    infile.close();
    return accounts;
}

void storeAccounts(std::unordered_map<uint32_t, Account> accounts, std::string file)
{
    std::ofstream outfile(file);
    accSelect = 0;

    while (accounts[accSelect].checkValid()) 
    {
        std::string toWrite = accounts[accSelect].write();
        //write out to file
        outfile << toWrite << std::endl;
        accSelect++;
    }

    outfile.close();
    return;
}

bool checkString(std::string input, char* type, char* end)
{
    //convert to lowercase
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c){ return std::tolower(c); });

    uint32_t size = input.size(); //iterate through all characters of input

    for (uint32_t i = 0; i < size; i++)
    {
        char* position = std::find(type, end, input[i]); //look for character in array

        if (position == end)//if not found
        { 
            std::cout << "Input contains invalid characters, try again.\n";
            return true;
        }
        else if (i >= size-1)//if all characters are letters/numbers
        { 
            return false;
        }
    }
    return true;
}

bool checkPin(std::string input, char* type, char* end)
{
    uint32_t size = input.size(); //iterate through all characters of input

    if (size != 5)
    {
        std::cout << "Input is not 5 digits, try again.\n";
    }
    else
    {
        for (uint32_t i = 0; i < size; i++)
        {
            char* position = std::find(type, end, input[i]); //look for character of digits

            if (position == end)//if not found
            { 
                std::cout << "Input contains invalid characters, try again.\n";
                return true;
            }
            else if (i >= size-1)//if all characters are numbers
            { 
                return false;
            }
        }
    }
    return true;
}