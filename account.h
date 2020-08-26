#include <iostream>
#include <ostream>
#include <string>
#include <iomanip>
#include <cstdint>


//change all int types
class Account {
    private:
        uint32_t id;
        uint32_t pin;
        std::string firstName;
        std::string lastName;
        double balance;
    public:
        Account(); //could also be just this Account() {}
        Account(uint32_t id, std::string firstName, std::string lastName, uint32_t pin);
        void showBalance();
        bool isBalanceNeg();
        void deposit(double amount);
        void withdraw(double amount);
        bool checkValid();
        bool validatePin(uint32_t number);
        std::string write();
};