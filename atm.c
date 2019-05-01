#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Grading mode
//Displays all account numbers and pins
//  1-enabled 0-disabled
int GRADINGMODE = 1;

//Customer struct
struct customerInformation {
    int accountNumber[5];
    int pinNumber[5];
    int socialSecurity[5];
    double balance[5];
};

//Teller struct
struct tellerInformation {
    int accountNumber;
};

//Customer struct array
struct customerInformation customer =
{
        {12345, -1, -1, -1, -1},
        {1234, -1, -1, -1, -1},
        {232476545, -1, -1, -1},
        {100, -1, -1, -1, -1}
};

//Teller account
struct tellerInformation teller = {10001};

/*
* Function to validate the users account number.
*/
int validateAccount()
{

    int accountIndex;
    int userAccountNumberInput;

    //Allows professor to see all account numbers and PINs
    if(GRADINGMODE == 1) {
        printf("\nGrading Mode ENABLED:\n--------------------------\nCurrent User Accounts:\n");
        for(int i=0; i<=4; i++) {
            if(customer.accountNumber[i] != -1) {
                printf("ID: %d PIN: %d\n", customer.accountNumber[i], customer.pinNumber[i]);
            }
        }
        printf("--------------------------\n");
    }

    printf("\nEnter your account number: ");
    scanf("%d", &userAccountNumberInput);

    for(int i=0; i<=4; i++) {
        if(userAccountNumberInput == customer.accountNumber[i] && userAccountNumberInput != -1) {

            accountIndex = i;
            return accountIndex;

        }
        else {
            accountIndex = -1;
        }
    }

    return -1;
}

/*
* Function to validate the users pin number.
*/
bool validatePIN(int accountIndex)
{
    bool pinValidate;
    int userPIN;

    printf("\nEnter your PIN: ");
    scanf("%d", &userPIN);

    if(userPIN == customer.pinNumber[accountIndex] && userPIN != -1) {

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
int validateUser() {

    int accountIndex;
    bool accountValidation = false;
    while(accountValidation == false) {

        accountIndex = validateAccount();

        if(accountIndex == -1) {

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
        if(!validatePIN(accountIndex)) {

                //If there are no more remaining attempts, transaction is canceled.
                if(remaningAttempts <= 0) {

                     printf("PIN number is incorrect! You have %d", remaningAttempts);
                     printf(" attempts left!\nTransaction terminated!\n");
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
            printf("\nPin correct!\n");
            pinValidation = true;
            return accountIndex;
        }

    }

}

/*
* Function to validate the tellers account.
*/
void validateTeller()
{

    bool tellerValidate = false;
    int tellerAccountNumberInput;

    while(tellerValidate == false) {
        printf("\nDefault Teller Account Number: 10001\nEnter your account number: ");
        scanf("%d", &tellerAccountNumberInput);

        if(tellerAccountNumberInput == teller.accountNumber) {

            tellerValidate = true;

        }
        else {
            printf("\nInvalid account number! Try again!\n");
            tellerValidate = false;

        }

    }
}

/*
* Displays the main menu to the standard user.
* Gets the users selected choice, and calls
* appropriate function.
*/
void displayMenu(int accountIndex) {

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
                depositFunds(accountIndex);
                break;
            case(2) :
                withdrawFunds(accountIndex);
                break;
            case(3) :
                queryFunds(accountIndex);
                break;
            case(4) :
                transferFunds(accountIndex);
                break;
            case(5) :
                cancelTransaction();
                userCancel = true;
                break;
            default :
                printf("Invalid choice!\n");
        }

    }

}

/*
* Function to display menu for teller.
*/
void displayBankerMenu() {

    bool userCancel = false;
    while(userCancel == false) {

        printf("\nPlease select one of the following options:\n");
        printf("1. Open Account\n");
        printf("2. Close Account\n");
        printf("3. Cancel\n");

        int choice;
        scanf("%d", &choice);

        switch(choice) {
            case(1) :
                openAccount();
                break;
            case(2) :
                closeAccount();
                break;
            case(3) :
                cancelTransaction();
                userCancel = true;
                break;
            default :
                printf("Invalid choice!\n");
        }

    }

}

/*
* Function to deposit selected funds.
*/
void depositFunds(int accountIndex) {

    double depositAmount;
    printf("\nEnter the amount you'd like to deposit: \n");
    scanf("%lf", &depositAmount);

    if(depositAmount >= 0.01) {
    customer.balance[accountIndex] = (customer.balance[accountIndex] + depositAmount);
    queryFunds(accountIndex);
    }
    else {
        printf("\nDeposit must be more than $0.00.\n");
    }

}

/*
* Function to withdraw selected funds.
*/
void withdrawFunds(int accountIndex) {

    double withdrawAmount;
    printf("\nEnter the amount you'd like to withdraw: \n");
    scanf("%lf", &withdrawAmount);

    if(withdrawAmount >= 0.01)  {

        if(withdrawAmount <= customer.balance[accountIndex]) {
        customer.balance[accountIndex] = (customer.balance[accountIndex] - withdrawAmount);
        queryFunds(accountIndex);
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
void transferFunds(int accountIndex) {

    int reciveeAccountNumber;
    printf("\nEnter the account number of the user you'd like to send money to: ");
    scanf("%d", &reciveeAccountNumber);

    for(int i=0; i<=4; i++) {

        if(i == accountIndex) {

        }
        else {

            if(reciveeAccountNumber == customer.accountNumber[i]) {

                double reciveeMoney;
                printf("\nEnter the amount you'd like to transfer: ");
                scanf("%lf", &reciveeMoney);

                if(reciveeMoney >= 0.01) {

                    if(reciveeMoney <= customer.balance[accountIndex]) {
                        customer.balance[accountIndex] = customer.balance[accountIndex] - reciveeMoney;
                        customer.balance[i] = customer.balance[i] + reciveeMoney;
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
                if(i==4) {
                    printf("\nNo account found!\n");
                }
            }
        }

    }

}

/*
* Function to print user's balance.
*/
void queryFunds(int accountIndex) {

    printf("\nYour current balance is now $%.2f\n", customer.balance[accountIndex]);

}

/*
* Function to open a user account.
*/
void openAccount() {

    //If there are more than 5 accounts
    if(customer.accountNumber[4] != -1) {
        printf("\nYou can only create 5 accounts at one time!\n");
    }
    else {

        int newIndex;
        for(int i=0; i<=4; i++) {

            if(customer.accountNumber[i] == -1) {
                newIndex = i;
            }

        }

        int userPin;
        printf("\nEnter the users PIN: \n");
        scanf("%d", &userPin);

        //Must be 4 digit number
        if(userPin > 999 && userPin < 10000) {

            int userSSN;
            printf("\nEnter the users SSN: \n");
            scanf("%d", &userSSN);

            //Must be 9 digit number
            if(userSSN > 99999999 && userSSN < 1000000000 ) {
                customer.pinNumber[newIndex] = userPin;
                customer.socialSecurity[newIndex] = userSSN;
                customer.balance[newIndex] = 0;

                //Makes random number
                int randomAccountNumber = (rand() % (99999 + 1 - 10000)) + 10000;
                customer.accountNumber[newIndex] = randomAccountNumber;

                printf("\nCustomers new account number is: %d\n", randomAccountNumber);

            }
            else {
                printf("\nSSN must be 9 digits!\n");
            }

        }
        else {
            printf("\nPin must be 4 digits!\n");
        }

    }

}

/*
* Function to close users account.
*/
void closeAccount() {

    int userAccount;
    printf("\nEnter the users account number to cancel: \n");
    scanf("%d", &userAccount);

    for(int i=0; i<=4; i++) {

        if(userAccount == customer.accountNumber[i] && userAccount != -1) {
            //Reset all info
            customer.accountNumber[i] = -1;
            customer.pinNumber[i] = -1;
            customer.balance[i] = -1;
            customer.socialSecurity[i] = -1;

            printf("\nAccount %d has been closed!\n", userAccount);

        }
        else {
            if(i == 4) {
                printf("\nUser not found!\n");
            }
        }

    }



}

/*
* Function to exit program
*/
void cancelTransaction() {

    printf("\nTransaction canceled!\n");

}

/*
* Main function.
*/
int main() {

    bool exitSelection = false;

    //While user doesn't want to quit
    while(exitSelection == false) {

        //Sign in menu
        int userSelection;
        printf("1. Sign in as customer.\n");
        printf("2. Sign in as bank teller.\n");
        printf("3. Quit\n");
        scanf("%d", &userSelection);

        //If customer signs in
        if(userSelection == 1) {
            int accountIndex = validateUser();
            displayMenu(accountIndex);
        }
        else {
            //If teller signs in
            if(userSelection == 2) {
                validateTeller();
                displayBankerMenu();
            }
            else {
                //If user quits
                if(userSelection == 3) {
                    printf("\nThanks for using the ATM!\n");
                    exit(1);
                }
                //Else invalid option
                else {
                    printf("\nInvalid choice!\n");
                }

            }

        }

    }

}
