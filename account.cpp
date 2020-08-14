#include <string>

class Account {
    private:
        int id, pin;
        std::string firstName, lastName;
        double balance = 0;
    public:
        void createAccount(std::string fname, std::string lname, int pinNum);
        void showBalance();
        void deposit(int ammount);
        void withdraw(int ammount);

};

void Account::createAccount(std::string fname, std::string lname, int pinNum){
    //random seed
    srand(time(NULL));
    //random number between 1 and 10
    id = rand() % 10 + 1;
    //set variables
    firstName = fname;
    lastName = lname;
    pin = pinNum;
    return;
};

void Account::showBalance(){
    std::cout << "Current account balance: "<< balance << std::endl;
}

void Account::deposit(int ammount) {
    balance += ammount;
}

void Account::withdraw(int ammount) {
    balance -= ammount;
}
