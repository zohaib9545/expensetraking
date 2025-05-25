#include <iostream>
#include <string>
using namespace std;

struct Expense {
    int id;
    string description;
    double price;
    int day, month, year;
    Expense* next;

    Expense(int id_, string desc, double pr, int d, int m, int y) {
        id = id_;
        description = desc;
        price = pr;
        day = d;
        month = m;
        year = y;
        next = NULL;
    }
};

class ExpenseTracker {
private:
    Expense* head;
    int nextId;

public:
    ExpenseTracker() {
        head = NULL;
        nextId = 1;
    }

    void addExpense(string desc, double price, int day, int month, int year) {
        Expense* newNode = new Expense(nextId++, desc, price, day, month, year);
        if (head == NULL) {
            head = newNode;
        } else {
            Expense* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void showExpenses() {
        if (head == NULL) {
            cout << "No expenses to show." << endl;
            return;
        }

        cout << "ID\tDescription\tPrice\tDate" << endl;
        cout << "-----------------------------------------" << endl;

        Expense* current = head;
        while (current != NULL) {
            cout << current->id << "\t";
            cout << current->description << "\t\t";
            cout << current->price << "\t";
            cout << current->day << "/";
            cout << current->month << "/";
            cout << current->year << endl;
            current = current->next;
        }
    }

    bool deleteExpenseById(int id) {
        if (head == NULL) return false;

        if (head->id == id) {
            Expense* toDelete = head;
            head = head->next;
            delete toDelete;
            return true;
        }

        Expense* current = head;
        while (current->next != NULL && current->next->id != id) {
            current = current->next;
        }

        if (current->next == NULL) return false;

        Expense* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        return true;
    }

    void reportByMonth(int month, int year) {
        Expense* current = head;
        bool found = false;
        double maxPrice = -1;
        Expense* maxExpense = NULL;

        cout << "Report for month:\t" << month << "/" << year << endl;
        cout << "ID\tDescription\tPrice\tDate" << endl;
        cout << "-----------------------------------------" << endl;

        while (current != NULL) {
            if (current->month == month && current->year == year) {
                cout << current->id << "\t";
                cout << current->description << "\t\t";
                cout << current->price << "\t";
                cout << current->day << "/";
                cout << current->month << "/";
                cout << current->year << endl;
                found = true;

                if (current->price > maxPrice) {
                    maxPrice = current->price;
                    maxExpense = current;
                }
            }
            current = current->next;
        }

        if (!found) {
            cout << "No expenses found for this month." << endl;
        } else {
            cout << "Most Expensive Item:\n";
            cout << "ID:\t" << maxExpense->id << "\t";
            cout << "Description:\t" << maxExpense->description << "\t";
            cout << "Price:\t" << maxExpense->price << "\t";
            cout << "Date:\t" << maxExpense->day << "/" << maxExpense->month << "/" << maxExpense->year << endl;
        }
    }

    void reportByWeek(int startDay, int month, int year) {
        Expense* current = head;
        bool found = false;
        double maxPrice = -1;
        Expense* maxExpense = NULL;

        cout << "Weekly Report from\t" << startDay << "/" << month << "/" << year << endl;
        cout << "ID\tDescription\tPrice\tDate" << endl;
        cout << "-----------------------------------------" << endl;

        while (current != NULL) {
            if (current->year == year && current->month == month &&
                current->day >= startDay && current->day <= startDay + 6) {
                
                cout << current->id << "\t";
                cout << current->description << "\t\t";
                cout << current->price << "\t";
                cout << current->day << "/";
                cout << current->month << "/";
                cout << current->year << endl;

                found = true;

                if (current->price > maxPrice) {
                    maxPrice = current->price;
                    maxExpense = current;
                }
            }
            current = current->next;
        }

        if (!found) {
            cout << "No expenses found for this week." << endl;
        } else {
            cout << "Most Expensive Item:\n";
            cout << "ID:\t" << maxExpense->id << "\t";
            cout << "Description:\t" << maxExpense->description << "\t";
            cout << "Price:\t" << maxExpense->price << "\t";
            cout << "Date:\t" << maxExpense->day << "/" << maxExpense->month << "/" << maxExpense->year << endl;
        }
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "===== Expense Tracker Menu =====" << endl;
        cout << "1. Add Expense" << endl;
        cout << "2. Show All Expenses" << endl;
        cout << "3. Delete Expense by ID" << endl;
        cout << "4. Report by Month" << endl;
        cout << "5. Report by Week" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string desc;
        double price;
        int day, month, year, id;

        if (choice == 1) {
            cout << "Enter description: ";
            cin >> desc;
            cout << "Enter price: ";
            cin >> price;
            cout << "Enter date (dd mm yyyy): ";
            cin >> day >> month >> year;
            tracker.addExpense(desc, price, day, month, year);
        } else if (choice == 2) {
            tracker.showExpenses();
        } else if (choice == 3) {
            cout << "Enter ID of expense to delete: ";
            cin >> id;
            if (tracker.deleteExpenseById(id)) {
                cout << "Expense deleted successfully." << endl;
            } else {
                cout << "Expense not found." << endl;
            }
        } else if (choice == 4) {
            cout << "Enter month and year (mm yyyy): ";
            cin >> month >> year;
            tracker.reportByMonth(month, year);
        } else if (choice == 5) {
            cout << "Enter start day, month, year (dd mm yyyy): ";
            cin >> day >> month >> year;
            tracker.reportByWeek(day, month, year);
        } else if (choice == 0) {
            cout << "Exiting... Goodbye!" << endl;
        } else {
            cout << "Invalid option. Try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
