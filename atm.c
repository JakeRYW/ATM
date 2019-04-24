#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/***************************************
* THINGS THAT NEED TO BE ADDED/UPDATED *
*   1. Loops to get all user input.    *
*   2. Check for overdraw.             *
*   3. Change hard-coding so it can be *
*      any account, rather than just   *
*      accountA.                       *
****************************************/


struct customerInformation {
    int accountNumber;
    int pinNumber;
    double balance;
};

struct customerInformation customerA = {1, 1234, 100};
struct customerInformation customerB = {2, 1235, 200};

/*
* Function to validate the users account number.
*/
bool validateAccount()
{

    bool accountValidate;
    int userAccountNumberInput;

    printf("Enter your account number: ");
    scanf("%d", &userAccountNumberInput);


    if(userAccountNumberInput == customerA.accountNumber) {

        accountValidate = true;
        return accountValidate;

    }
    else {
        accountValidate = false;

    }

    return accountValidate;
}

/*
* Function to validate the users pin number.
*/
bool validatePIN()
{
    bool pinValidate;
    int userPIN;

    printf("Enter your PIN: ");
    scanf("%d", &userPIN);

    if(userPIN == customerA.pinNumber) {

        pinValidate = true;
        return pinValidate;

    }
    else {
        pinValidate = false;

    }

    return pinValidate;
}

/*
* Function to validate the users information.
* Calls the validateAccount and validatePIN functions.
* Loops the validateAccount infinity, and loops validatePIN
* 3 times.
*/
bool validateUser() {

    bool accountValidation = false;
    while(accountValidation == false) {

        if(!validateAccount()) {

            printf("Account number is incorrect! Try again!\n");

        }
        else {
            accountValidation = true;

        }

    }

    //Counter to hold number of attempts user tried to enter PIN.
    //Starts at 1, because user must enter PIN at least once.
    int attempts = 1;
    bool pinValidation = false;

    while(pinValidation == false) {

        //User only gets 3 tries.
        int remaningAttempts = 3-attempts;

        //If the PIN was incorrect.
        if(!validatePIN()) {

                //If there are no more remaining attempts, transaction is canceled.
                if(remaningAttempts <= 0) {

                     printf("PIN number is incorrect! You have %d", remaningAttempts);
                     printf(" attempts left! Transaction terminated!\n");
                     exit(0);

                }
                //Otherwise, inform user of attempts left
                else {
                    printf("PIN number is incorrect! You have %d", remaningAttempts);
                    printf(" attempts left!\n");
                    attempts++;

                }

        }

        //Otherwise, PIN correct.
        else {
            printf("Pin correct!\n");
            pinValidation = true;

        }

    }

}

/*
* Displays the main menu to the standard user.
* Gets the users selected choice, and calls
* appropriate function.
*/
void displayMenu() {

    bool userCancel = false;
    while(userCancel == false) {

        printf("\nPlease select one of the following options:\n");
        printf("1. Deposit Funds\n");
        printf("2. Withdraw Funds\n");
        printf("3. Query Account\n");
        printf("4. Transfer Funds\n");
        printf("5. Cancel\n");

        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case(1) :
                depositFunds();
                break;
            case(2) :
                withdrawFunds();
                break;
            case(3) :
                queryFunds();
                break;
            case(4) :
                transferFunds();
                break;
            case(5) :
                cancelTransaction();
                break;
            default :
                printf("Invalid choice!\n");
        }

    }

}

/*
* Function to deposit selected funds.
*/
void depositFunds() {

    double depositAmount;
    printf("\nEnter the amount you'd like to deposit: \n");
    scanf("%lf", &depositAmount);

    if(depositAmount >= 0.01) {
    customerA.balance = (customerA.balance + depositAmount);
    queryFunds();
    }
    else {
        printf("\nDeposit must be more than $0.00.\n");
    }

}

/*
* Function to withdraw selected funds.
*/
void withdrawFunds() {

    double withdrawAmount;
    printf("\nEnter the amount you'd like to withdraw: \n");
    scanf("%lf", &withdrawAmount);

    if(withdrawAmount >= 0.01)  {

        if(withdrawAmount <= customerA.balance) {
        customerA.balance = (customerA.balance - withdrawAmount);
        queryFunds();
        }
        else {
            printf("\nYou can't withdraw more than you have.\n");
        }
    }
    else {
        printf("\nYou must withdraw more than $0.00.\n");
    }
}

/*
* Function to transfer selected funds between two accounts.
*/
void transferFunds() {

    int reciveeAccountNumber;
    printf("\nEnter the account number of the user you'd like to send money to: ");
    scanf("%d", &reciveeAccountNumber);

    if(reciveeAccountNumber == customerB.accountNumber) {

        double reciveeMoney;
        printf("\nEnter the amount you'd like to transfer: ");
        scanf("%lf", &reciveeMoney);

        if(reciveeMoney >= 0.01) {
            if(reciveeMoney <= customerA.balance) {
                customerA.balance = customerA.balance - reciveeMoney;
                customerB.balance = customerB.balance + reciveeMoney;
                printf("\nTransfer successful!\n");
            }
            else {
                printf("\nYou can't transfer more than you have.\n");
            }
        }
        else {
            printf("\nYou must transfer more than $0.00.\n");
        }

    }
    else {

        printf("\nNot a valid account!\n");

    }

}

/*
* Function to print user's balance.
*/
void queryFunds() {

    printf("\nYour currents balance is now $%.2f\n", customerA.balance);

}

/*
* Function to exit program
*/
void cancelTransaction() {

    printf("\nThank you for using ATM!\n");
    exit(0);

}

/*
* Main function.
*/
int main() {

    validateUser();
    displayMenu();

}
