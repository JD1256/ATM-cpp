#include <string>

class Account {
    private:
        int id, pin;
        std::string firstName = "", lastName = "";
        double balance = 0;
    public:
        void createAccount(int idNum, std::string fname, std::string lname, int pinNum);
        void showBalance();
        void deposit(int amount);
        void withdraw(int amount);
        bool checkValid();
        std::string write();
        bool validatePin(int number);
        bool isBalanceNeg();

};

void Account::createAccount(int idNum, std::string fname, std::string lname, int pinNum){
    //random seed
    //srand(time(NULL));
    //random number between 1 and 10
    //id = rand() % 10 + 1;
    //set variables
    id = idNum;
    firstName = fname;
    lastName = lname;
    pin = pinNum;
    return;
};

void Account::showBalance(){
    std::cout << "\nCurrent account balance: $"<< std::fixed << std::setprecision(2) << balance << std::endl;
}

bool Account::isBalanceNeg(){
    return (balance < 0);
}

void Account::deposit(int amount) {
    balance += amount;
}

void Account::withdraw(int amount) {
    balance -= amount;
}

//Returns true if used. False if ID not used
bool Account::checkValid(){
    return (firstName != "");
}

bool Account::validatePin(int number){
    return (number == pin);
}

std::string Account::write(){
    std::string temp = "";
    //Id
    temp.append(std::to_string(id));
    temp.append(" ");
    //Fname
    temp.append(firstName);
    temp.append(" ");
    //Lname
    temp.append(lastName);
    temp.append(" ");
    //pin
    temp.append(std::to_string(pin));
    temp.append(" ");
    //balance
    temp.append(std::to_string(balance));
    temp.append(" ");
    return temp;
}

