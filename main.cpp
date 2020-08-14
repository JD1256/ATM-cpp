#include "main.h"

int DEFAULT_INPUTS = 2;
int choice = -1;
std::string first = "", last = "";
int newPin = 0;
int accIncrement = 0;
int accSelect = 0;
bool signedIn = false;



int main() {
    Account acc[10];
    
    std::cout << "==============================\n";
    std::cout << "         ATM SERVICES         \n";
    std::cout << "0. Sign in\n";
    std::cout << "1. Create Account\n";
    while(choice < 0 || choice >= DEFAULT_INPUTS){
        std::cout << "Please select from above: \n";
        std::cin >> choice;

    }

    
    switch (choice){
        case 0: //Sign into account (change accSelector)
            std::cout << "In case 0\n";
            signedIn = true;
            break;
        case 1: //Create account
            std::cout << "=====================================\n";
            std::cout << "Please enter your first then last name\n";
            std::cin >> first;
            std::cin >> last;
            //handle name input
            std::cout << "Please create a 5 digit pin\n";
            std::cin >> newPin;
            //handle pin input

            Account test;
            acc[accIncrement].createAccount(first, last, newPin);
            acc[accIncrement].showBalance();
            acc[accIncrement].deposit(50);
            acc[accIncrement].showBalance();
            break;
    }



    return 0;
}