#include <iostream>
#include <string>
using namespace std;

class Account {
public:
    string accountHolder;
    int accountNumber;
    double balance;
    Account* next;

    Account() {
        accountHolder = "";
        accountNumber = 0;
        balance = 0.0;
        next = NULL;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        } else {
            cout << "Invalid or insufficient balance.\n";
        }
    }

    virtual void displayAccountDetails() {
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Balance: " << balance << "\n";
    }
};

class SavingsAccount : public Account {
public:
    void setAccountDetails(string name, int accNumber, double initialDeposit) {
        accountHolder = name;
        accountNumber = accNumber;
        balance = initialDeposit;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount + (amount * 0.02);
            cout << "Amount deposited successfully with interest.\n";
        } else {
            cout << "Invalid deposit amount.\n";
        }
    }

    void displayAccountDetails() {
        cout << "Savings Account:\n";
        Account::displayAccountDetails();
    }
};

class CurrentAccount : public Account {
public:
    void displayAccountDetails() {
        cout << "Current Account:\n";
        Account::displayAccountDetails();
    }
};

class Bank {
private:
    Account* head;

public:
    Bank() {
        head = NULL;
    }

    void addAccount(Account* newAccount) {
        newAccount->next = head;
        head = newAccount;
        cout << "Account created successfully.\n";
    }

    Account* findAccount(int accNumber) {
        Account* current = head;
        while (current != NULL) {
            if (current->accountNumber == accNumber) {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void deleteAccount(int accNumber) {
        Account* current = head;
        Account* previous = NULL;

        while (current != NULL) {
            if (current->accountNumber == accNumber) {
                if (previous == NULL) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;
                cout << "Account deleted successfully.\n";
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Account not found.\n";
    }
};

int main() {
    Bank bank;
    int choice;

    while (true) {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Open New Savings Account\n";
        cout << "2. Open New Current Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Display Account Details\n";
        cout << "6. Delete Account\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string name;
            int accNumber;
            double initialDeposit;
            cout << "Enter account holder's name: ";
            cin >> name;
            cout << "Enter account number: ";
            cin >> accNumber;
            cout << "Enter initial deposit: ";
            cin >> initialDeposit;

            Account* newAccount;
            if (choice == 1) {
                newAccount = new SavingsAccount();
                ((SavingsAccount*)newAccount)->setAccountDetails(name, accNumber, initialDeposit);
            } else {
                newAccount = new CurrentAccount();
                newAccount->accountHolder = name;
                newAccount->accountNumber = accNumber;
                newAccount->balance = initialDeposit;
            }
            bank.addAccount(newAccount);

        } else if (choice == 3 || choice == 4 || choice == 5) {
            int accNumber;
            cout << "Enter account number: ";
            cin >> accNumber;

            Account* account = bank.findAccount(accNumber);
            if (account == NULL) {
                cout << "Account not found.\n";
            } else {
                if (choice == 3) {
                    double depositAmount;
                    cout << "Enter deposit amount: ";
                    cin >> depositAmount;
                    account->deposit(depositAmount);
                } else if (choice == 4) {
                    double withdrawAmount;
                    cout << "Enter withdraw amount: ";
                    cin >> withdrawAmount;
                    account->withdraw(withdrawAmount);
                } else if (choice == 5) {
                    account->displayAccountDetails();
                }
            }
        } else if (choice == 6) {
            int accNumber;
            cout << "Enter account number to delete: ";
            cin >> accNumber;
            bank.deleteAccount(accNumber);
        } else if (choice == 7) {
            cout << "Thank you for using the bank management system.\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
