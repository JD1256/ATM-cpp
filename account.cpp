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
    std::cout << "Current account balance: "<< balance << std::endl;
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
    return temp;
}

bool Account::validatePin(int number){
    return (number == pin);
}