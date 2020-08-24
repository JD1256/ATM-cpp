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
    bool working = true;


    //read in from file
    std::ifstream infile;
    std::string line = "";
    infile.open("data.txt");
    while (std::getline(infile, line)){
        std::istringstream  iss(line);
        //input file variables
        std::string fileFname = "", fileLname=  "";
        int filePin;
        if (!(iss >> accIncrement >> fileFname >> fileLname >> filePin)) {break;}//error
        
        std::cout << line << std::endl;
        acc[accIncrement].createAccount(accIncrement,fileFname, fileLname, filePin);

        accIncrement++;
    }
    infile.close();

    
    while (working)
    {
        std::cout << "==============================\n";
        std::cout << "         ATM SERVICES         \n";
        std::cout << "0. Sign in\n";
        std::cout << "1. Create Account\n";
        while(choice < 0 || choice >= DEFAULT_INPUTS){
            std::cout << "Please select from above: \n";
            std::cin >> choice;

        }

        
        switch (choice){
            case 0: //Sign into account (change accSelect)
                std::cout << "In case 0\n";
                signedIn = true;
                break;
            case 1: //Create account
                std::cout << "=====================================\n";
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
        }
        working = false;
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