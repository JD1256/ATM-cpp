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


//hash table id to point to account obj

//load accounts method takes in txt file name and returns hash map
//store accounts to dump hash map to file

uint32_t choice; //used when getting input from the user
char letter[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
char number[] = {'1','2','3','4','5','6','7','8','9','0'};
bool typing;
//used when creating a new acocunt
std::string first;
std::string last;
std::string newPin;
uint32_t accPin = -1;

uint32_t accIncrement = 0; //contains the total number of accounts and will increase when new account is made
uint32_t accSelect = -1; //used to select the account when signing in

//sign in variables
bool signedIn = false, flag;
uint32_t attempts, transferSel;
double money = 0;


uint32_t tempPin;



std::string transfer(std::unordered_map<uint32_t, Account> acc,uint32_t acc1, uint32_t acc2, double amount);


int main() 
{
    std::unordered_map<uint32_t, Account> acc;
    bool working = true; //main loop control

    //read in from file
    std::ifstream infile;
    std::string line = "";
    infile.open("data.txt");
    while (std::getline(infile, line))
    {
        std::istringstream  iss(line);
        //input file variables
        std::string fileFname = "", fileLname=  "";
        uint32_t filePin;
        double fileBalance;

        if (!(iss >> accIncrement >> fileFname >> fileLname >> filePin >> fileBalance)) 
            break; //error

        Account account(accIncrement,fileFname, fileLname, filePin);
        //acc[accIncrement] = Account(accIncrement,fileFname, fileLname, filePin);
        acc[accIncrement] = account;
        acc[accIncrement].deposit(fileBalance);
        accIncrement++;
    }
    infile.close();

    
    while (working)
    {   
        //main screen options
        choice = -1;

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
                std::cout << "Please select from above: \n";
                std::cin >> choice;

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
                    std::cout << "=================================\n";
                    accSelect = -1;

                    while(accSelect < 0 || accSelect >= accIncrement)
                    {  //cant select "-" or above the total # accounts
                        std::cout << "Please enter your account number:\n";
                        std::cin >> accSelect;
                        if (accSelect < 0 || accSelect >= accIncrement)
                        { //display error message
                            std::cout << "Account does not exist, try again\n";
                        }
                    }
                    //confirm correct pin to login, 3 attempts then kicked out
                    flag = false;
                    attempts = 2;
                    while (!flag && attempts >= 0) 
                    {
                        std::cout << "Please enter your 5-digit pin:\n";
                        std::cin >> accPin;
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
                            std::cout << "Login successful\n";
                        }
                    }
                    break;

                case 1: //Create account
                {
                    std::cout << "=======================================\n";
                    std::cout << "           Account creation\n";

                    //Loop for first name input
                    typing = true;
                    while (typing){
                        std::cout << "Please enter your first name: \n";
                        std::cin >> first;
                        //convert to lowercase
                        std::transform(first.begin(), first.end(), first.begin(), [](unsigned char c){ return std::tolower(c); });

                        int size = first.size(); //iterate through all characters of input
                        char* end = letter + sizeof(letter) / sizeof(letter[0]);
                        for (int i = 0; i < size; i++){
                            char* position = std::find(letter, end, first[i]); //look for character in alphabet
                            if (position == end){ //if not found
                                std::cout << "Input contains invalid characters, try again.\n";
                                break;
                            }else if (i >= size-1){ //if all characters are letters
                                typing = false;
                            }
                        }
                    }

                    //Loop for last name input (turn this into a function so its not repeated)
                    typing = true;
                    while (typing){
                        std::cout << "Please enter your last name: \n";
                        std::cin >> last;
                        //convert to lowercase
                        std::transform(last.begin(), last.end(), last.begin(), [](unsigned char c){ return std::tolower(c); });

                        int size = last.size(); //iterate through all characters of input
                        char* end = letter + sizeof(letter) / sizeof(letter[0]);
                        for (int i = 0; i < size; i++){
                            char* position = std::find(letter, end, last[i]); //look for character in alphabet
                            if (position == end){ //if not found
                                std::cout << "Input contains invalid characters, try again.\n";
                                break;
                            }else if (i >= size-1){ //if all characters are letters
                                typing = false;
                            }
                        }
                    }

                    typing = true;
                    while (typing){
                        std::cout << "Please create a 5 digit pin:\n";
                        std::cin >> newPin;

                        int size = newPin.size(); //iterate through all characters of input

                        if (size != 5){
                            std::cout << "Input is not 5 digits, try again.\n";
                        }else {
                            char* end = number + sizeof(number) / sizeof(number[0]);
                            for (int i = 0; i < size; i++){
                                char* position = std::find(number, end, newPin[i]); //look for character of digits
                                if (position == end){ //if not found
                                    std::cout << "Input contains invalid characters, try again.\n";
                                    break;
                                }else if (i >= size-1){ //if all characters are numbers
                                    typing = false;
                                }
                            }
                        }
                    }

                    uint32_t tempPin = std::stoi(newPin);
                    //check accIncrement if account number is used
                    if (acc[accIncrement].checkValid()) 
                    {
                        std::cout << accIncrement << std::endl;
                        accIncrement++;
                    }
                    acc[accIncrement] = Account(accIncrement, first, last, tempPin);
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

            while(choice < 0 || choice >= 5)
            { //limit to the number of options listed above
                std::cout << "Please select from above: \n";
                std::cin >> choice;
            }
            

            switch (choice){
                case 0:  
                    //Check balance
                    acc[accSelect].showBalance();
                    break;
                case 1: 
                    //Deposit
                    std::cout << "\n";
                    std::cout << "Enter the amount you are depositing: \n";
                    
                    std::cin >> money; //add input handeling ----------------------------------------------------------------------------------------

                    acc[accSelect].deposit(money);
                    break;
                case 2:  
                    //Withdraw
                    std::cout << "\n";
                    std::cout << "Enter the amount you are withdrawing: \n";
                    
                    std::cin >> money; //add input handeling ----------------------------------------------------------------------------------------

                    acc[accSelect].withdraw(money);
                    break;
                case 3:  
                    //Transfer
                    std::cout << "\n";

                    transferSel = -1;
                    while(transferSel < 0 || transferSel >= accIncrement)
                    {
                        std::cout << "Enter the account number you would like to transfer to: \n";
                        std::cin >> transferSel;

                        if (transferSel < 0 || transferSel >= accIncrement)
                        {
                            std::cout << "Account does not exist, try again\n";
                        }
                    }
                    std::cout << "Enter the amount you are transfering: \n";
                    std::cin >> money; //add input handeling ----------------------------------------------------------------------------------------
                    std::cout << std::fixed << std::setprecision(2) << transfer(acc, accSelect, transferSel, money);


                    break;
                case 4:
                    //Exit screen (entered from a sign in choice and will continue to loop in signedIn choices)
                    std::cout << "==============================\n";
                    std::cout << " Would you like to sign out?  \n";
                    std::cout << "0. Yes\n";
                    std::cout << "1. No\n";
                    choice = -1;

                    while(choice < 0 || choice >= 2)
                    {
                        std::cout << "Please select from above: \n";
                        std::cin >> choice;
                        
                    }

                    if (choice == 0) 
                        signedIn = false;

                    break;
                break;
            }
        }

    }
    
    //update data in textfile
    std::ofstream outfile("data.txt");
    accSelect = 0;

    while (acc[accSelect].checkValid()) 
    {
        std::string toWrite = acc[accSelect].write();
        //write out to file
        outfile << toWrite << std::endl;
        accSelect++;
    }

    outfile.close();
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

bool check_number(std::string str) 
{
    for (uint32_t i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i]) == false)
        {
            return false;
        }
    }
   
   return true;
}