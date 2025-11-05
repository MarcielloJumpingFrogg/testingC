#include <stdio.h>

struct bankSystem
{
    char uuid[37];
    char password[12];
    char accountHolder[100];
    int balanceInCents;

};


void generateUuid();

void initialLoading();

void createAccount();

void loginAccount();

void withdrawFromAccount(int accountNumber);

void depositIntoAccount ( int accountNumber);

void effectPayment(int from, int destinaiton);


int main() {

    initialLoading();

}


void initialLoading(){

    char selection;

    printf("Welcome, \nWhat would you like to do?\npress *l* for login and *r* to register: ");
    scanf("%c", &selection);

    switch (selection)
    {
    case 'r':
        createAccount();
        break;
    
    case 'l':
        loginAccount();
        break;
    }
}



void createAccount() {
    printf("Creating account\n");
}


void generateUuid() {
    char v[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
}


void loginAccount() {
    printf("Login into account\n");
}


void withdrawFromAccount(int accountNumber) {

}

void depositIntoAccount(int accountNumber) {

}

void effectPayment(int from, int destination) {

}