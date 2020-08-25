#include "main.h"

//fix transfer function not modifying balances


int choice; //used when getting input from the user

//used when creating a new acocunt
std::string first = "", last = ""; 
int newPin = 0, accPin = -1;

int accIncrement = 0; //contains the total number of accounts and will increase when new account is made
int accSelect = -1; //used to select the account when signing in

//sign in variables
bool signedIn = false, flag;
int attempts, transferSel;
double money = 0;




std::string transfer(Account acc1, Account acc2, double amount);


int main() {
    Account acc[10]; //Max of 10 Accounts
    bool working = true; //main loop control


    //read in from file
    std::ifstream infile;
    std::string line = "";
    infile.open("data.txt");
    while (std::getline(infile, line)){
        std::istringstream  iss(line);
        //input file variables
        std::string fileFname = "", fileLname=  "";
        int filePin;
        double fileBalance;
        if (!(iss >> accIncrement >> fileFname >> fileLname >> filePin >> fileBalance)) {break;}//error
        
        std::cout << line << std::endl;
        acc[accIncrement].createAccount(accIncrement,fileFname, fileLname, filePin);
        acc[accIncrement].deposit(fileBalance);
        accIncrement++;
    }
    infile.close();

    
    while (working)
    {   
        //main screen options
        choice = -1;
        if (!signedIn) {
            choice = -1;
            while(choice < 0 || choice >= 3){
                std::cout << "==============================\n";
                std::cout << "         ATM SERVICES         \n";
                std::cout << "0. Sign in\n";
                std::cout << "1. Create Account\n";
                std::cout << "2. Exit\n";
                std::cout << "Please select from above: \n";
                std::cin >> choice;
                if (choice == 0 && accIncrement == 0){
                    std::cout << "There are no active accounts.\n";
                    std::cout << "Try creating a new one!\n";
                    choice = -1;
                }
            }
        
        

            //sign in, create account, exit screen
            switch (choice){
                case 0: //Sign into account (change accSelect)
                    std::cout << "=================================\n";
                    //select account
                    accSelect = -1;
                    while(accSelect < 0 || accSelect >= accIncrement){
                        std::cout << "Please enter your account number:\n";
                        std::cin >> accSelect;
                        if (accSelect < 0 || accSelect >= accIncrement){
                            std::cout << "Account does not exist, try again\n";
                        }
                    }
                    //confirm correct pin to login, 3 attempts then kicked out
                    flag = false;
                    attempts = 2;
                    while (!flag && attempts >= 0) {
                        std::cout << "Please enter your 5-digit pin:\n";
                        std::cin >> accPin;
                        flag = acc[accSelect].validatePin(accPin);
                        if (flag == false) {
                            std::cout << "Incorrect Pin. " << attempts << " remaining.\n";
                            attempts--;
                        } else {
                            flag = true;
                            signedIn = true;
                            std::cout << "Login successful\n";
                        }
                    }
                    break;

                case 1: //Create account
                    std::cout << "=======================================\n";
                    std::cout << "Please enter your first then last name:\n";
                    std::cin >> first;
                    std::cin >> last;
                    //handle name input
                    std::cout << "Please create a 5 digit pin:\n";
                    std::cin >> newPin;
                    //handle pin input

                    //check accIncrement if account number is used
                    if (acc[accIncrement].checkValid()) {
                        std::cout << accIncrement << std::endl;
                        accIncrement++;
                    }
                    acc[accIncrement].createAccount(accIncrement,first, last, newPin);
                    accIncrement++;
                    break;
                case 2:
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
            while(choice < 0 || choice >= 5){
                std::cout << "Please select from above: \n";
                std::cin >> choice;
            }
            

            switch (choice){
                case 0:  //Check balance
                    acc[accSelect].showBalance();
                    break;
                case 1: //Deposit
                    std::cout << "\n";
                    std::cout << "Enter the amount you are depositing: \n";
                    
                    std::cin >> money; //add input handeling

                    acc[accSelect].deposit(money);
                    break;
                case 2:  //
                    std::cout << "\n";
                    std::cout << "Enter the amount you are withdrawing: \n";
                    
                    std::cin >> money; //add input handeling

                    acc[accSelect].withdraw(money);
                    break;
                case 3:  //
                    std::cout << "\n";

                    transferSel = -1;
                    while(transferSel < 0 || transferSel >= accIncrement){
                    std::cout << "Enter the account number you would like to transfer to: \n";
                        std::cin >> transferSel;
                        if (transferSel < 0 || transferSel >= accIncrement){
                            std::cout << "Account does not exist, try again\n";
                        }
                    }
                    std::cout << "Enter the amount you are transfering: \n";
                    std::cin >> money; //add input handeling
                    std::cout << std::fixed << std::setprecision(2) << transfer(acc[accSelect], acc[transferSel] , money);


                    break;
                case 4:
                    //Exit screen (entered from a sign in choice and will continue to loop in signedIn choices)
                    std::cout << "==============================\n";
                    std::cout << " Would you like to sign out?  \n";
                    std::cout << "0. Yes\n";
                    std::cout << "1. No\n";
                    choice = -1;
                    while(choice < 0 || choice >= 2){
                        std::cout << "Please select from above: \n";
                        std::cin >> choice;
                        
                    }
                    if (choice == 0) {
                        signedIn = false;
                    }
                    break;
                break;
            }
        }

    }
    
    //update data in textfile
    std::ofstream outfile("data.txt");
    accSelect = 0;
    while (acc[accSelect].checkValid()) {
        std::string toWrite = acc[accSelect].write();
        //write out to file
        outfile << toWrite << std::endl;
        accSelect++;
    }
    outfile.close();
    return 0;
}

//transfer money from acc1 to acc2, cancel if not enough money
std::string transfer(Account acc1, Account acc2, double amount){
    acc1.withdraw(amount);
    if (acc1.isBalanceNeg()){
        acc1.deposit(amount); //account went negative so undo the withdraw
        return "Not enough money for transfer.\n";
    }
    acc2.deposit(amount);
    std::string out = "Transfered $";
    out.append(std::to_string(amount));
    out.append("\n");
    return out;
}