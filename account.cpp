#include "account.h"

Account::Account() {}

//constructor
Account::Account(uint32_t id, std::string firstName, std::string lastName, uint32_t pin) :
    id(id),
    firstName(firstName),
    lastName(lastName),
    pin(pin),
    balance(0.0)
{
    //stuff happens when object is created (if wanted)
}

void Account::showBalance()
{
    std::cout << "\nCurrent account balance: $"<< std::fixed << std::setprecision(2) << balance << std::endl;
}

bool Account::isBalanceNeg()
{
    return (balance < 0);
}

void Account::deposit(double amount)
{
    balance += amount;
}

void Account::withdraw(double amount)
{
    balance -= amount;
}

//Returns true if used. False if ID not used
bool Account::checkValid()
{
    return (firstName != "");
}

bool Account::validatePin(uint32_t number)
{
    return (number == pin);
}

std::ostream& operator<<(std::ostream& os, const Account& ac)
{
    os << ac.id << " " << ac.firstName << " " << ac.lastName << " " << ac.pin << " " << ac.balance << "\n";
    return os;
}

