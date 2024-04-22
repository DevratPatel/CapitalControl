#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures
struct User {
    char username[50];
    char password[50];
    double balance;
};

// Function prototypes
void registerUser();
void loginUser();
void menu();
void deposit(struct User *user);
void withdraw(struct User *user);
void interest(struct User *user);
void deleteAccount(struct User *user);

// Global variables
struct User users[100]; // Assuming maximum of 100 users
int userCount = 0;
int userPos = 0;

int main() {
    int choice;
    do {
        printf("\n|----------------------|\n");
        printf("|    CapitalControl    |\n");
        printf("|----------------------|\n");
        printf("| 1. Register          |\n");
        printf("| 2. Login             |\n");
        printf("| 3. Exit              |\n");
        printf("|----------------------|\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("\nExiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}

void registerUser() {
    char username[50];
    printf("\nEnter username: ");
    scanf("%s", username);

    // Check if username already exists
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0) {
            printf("\nUsername already taken. Please select a different username.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    strcpy(users[userCount].username, username);
    users[userCount].balance = 0.0;
    userCount++;
    printf("\nUser registered successfully.\n");

}


void loginUser() {
    char username[50];
    char password[50];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            userPos = i;
			printf("\nLogin successful. Welcome, %s!\n", users[i].username);
			printf("Your balance is: $%.2lf\n",users[userPos].balance);
			menu();
            return;
        }
    }
    printf("\nInvalid username or password.\n");
}

void menu(){
	int choice2;

	do{
		printf("1. Deposit\n");
		printf("2. Withdraw\n");
        printf("3. Calculate Interest\n");
        printf("4. Delete Account\n");
        printf("5. Logout\n\n");
		scanf("%d", &choice2);
		
		switch(choice2){
			case 1:
                deposit(&users[userPos]);
                break;
            case 2:
                withdraw(&users[userPos]);
                break;
            case 3:
                interest(&users[userPos]);
                break;
            case 4:
                deleteAccount(&users[userPos]);
                break;
            case 5:
                printf("\nLogging out...\n");
                break;
            default:
                printf("Invalid choice\n");
		}
	}while((choice2 != 5) && (choice2 != 4));
	return;
}

void deposit(struct User *user) {
    double amount;
    printf("\nEnter amount to deposit: ");
    scanf("%lf", &amount);
    user->balance += amount;
    printf("\nDeposit successful. Current balance: %.2lf\n", user->balance);
}

void withdraw(struct User *user) {
    double amount;
    printf("\nEnter amount to withdraw: ");
    scanf("%lf", &amount);
    if (amount > user->balance) {
        printf("Insufficient funds\n");
    } else {
        user->balance -= amount;
        printf("\nWithdrawal successful. Current balance: %.2lf\n", user->balance);
    }
}

void interest(struct User *user) {
    // Implement interest calculation logic here
	double interestrate;
	double years;
	double currentbalance = user->balance;
	printf("Enter interest rate as a percentage\n");
	scanf("%lf", &interestrate);
	interestrate = interestrate*.01;
	printf("Enter the amount of years interest will accrue\n");
	scanf("%lf", &years);
	double amount = currentbalance*interestrate*years;
	printf("The amount of accrued interest over %n years is: $%.2lf\n",amount);
    printf("Interest calculated.\n");
}

void deleteAccount(struct User *user) {
    char username[50];
    char password[50];
    printf("\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    int i;
    for (i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            // User found, delete the account
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1]; // Shift all elements one position left
            }
            userCount--;
            printf("\nAccount deleted successfully.\n");
            return;
        }
    }
    printf("\nInvalid username or password. Account deletion failed.\n");
}
