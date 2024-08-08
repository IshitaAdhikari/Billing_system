#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    int pcode;
    float price;
    float dis;
    string pname;

    Product* next;

    Product(int code, const string& name, float p, float d)
        : pcode(code), price(p), dis(d), pname(name), next(nullptr) {
    }
};

class Shopping {
private:
    Product* head;  // Pointer to the first product in the linked list

public:
    Shopping() : head(nullptr) {}
    ~Shopping();

    void menu();
    void administrator();
    void customer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

Shopping::~Shopping() {
    while (head) {
        Product* temp = head;
        head = head->next;
        delete temp;
    }
}

void Shopping::menu() {
    int choice;
    string email;
    string password;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tSupermarket Main Menu\n";
    cout << "\n ---------------------------------------------------------------\n\n";

    cout << "\t1] Administrator\n\n";
    cout << "\t2] Customer\n\n";
    cout << "\t3] Exit\n\n";

    cout << "\tPlease Enter your login option:\t";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "\nPlease login\n";
            cout << "Enter Email:\t";
            cin >> email;
            cout << "\nEnter Password:\t";
            cin >> password;

            if (email == "xyz@gmail.com" && password == "XYZ") {
                administrator();
            } else {
                cout << "\n------------------------------------------------------\n";
                cout << "\n\tInvalid Email or Password\n";
                cout << "\n------------------------------------------------------\n";
                menu();
            }
            break;

        case 2:
            customer();
            break;

        case 3:
            cout << "\n------------------------------------------------------\n";
            cout << "\n\tThank You!\n";
            cout << "\n------------------------------------------------------\n";
            exit(0);
            break;

        default:
            cout << "\n------------------------------------------------------\n";
            cout << "\nInvalid Choice, please select from the given choices\n";
            cout << "\n------------------------------------------------------\n";
            menu();
    }
}

void Shopping::administrator() {
    int choice;

    while (true) {
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\t\tAdministrator Menu\n";
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\n\t1] Add a product\n";
        cout << "\n\t2] Modify a product\n";
        cout << "\n\t3] Delete a product\n";
        cout << "\n\t4] Back to Main Menu\n";

        cout << "\nPlease Enter your choice:\t";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;

            case 2:
                edit();
                break;

            case 3:
                rem();
                break;

            case 4:
                menu();
                return;

            default:
                cout << "\n------------------------------------------------------\n";
                cout << "\nInvalid Choice, please select from the given choices\n";
                cout << "\n------------------------------------------------------\n";
        }
    }
}

void Shopping::customer() {
    int choice;

    while (true) {
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\t\tCustomer Menu\n";
        cout << "\n ---------------------------------------------------------------\n\n";

        cout << "\n\t1] Buy a product\n";
        cout << "\n\t2] Go Back\n";

        cout << "\nPlease Enter your choice:\t";
        cin >> choice;

        switch (choice) {
            case 1:
                receipt();
                break;

            case 2:
                menu();
                return;

            default:
                cout << "\n------------------------------------------------------\n";
                cout << "\nInvalid Choice, please select from the given choices\n";
                cout << "\n------------------------------------------------------\n";
        }
    }
}

void Shopping::add() {
    int pcode;
    float price, dis;
    string pname;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tAdd a new product\n";
    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\n\tProduct code of the product:\t";
    cin >> pcode;
    cout << "\n\tName of the product:\t";
    cin >> pname;
    cout << "\n\tPrice of the product:\t";
    cin >> price;
    cout << "\n\tDiscount of the product:\t";
    cin >> dis;

    Product* product = new Product(pcode, pname, price, dis);
    product->next = head;
    head = product;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tRecord Inserted\n";
    cout << "\n\n ---------------------------------------------------------------\n\n";
}

void Shopping::edit() {
    int pkey, token = 0, choice;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tModify a record\n";
    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\tProduct code:\t";
    cin >> pkey;

    Product* current = head;
    while (current) {
        if (current->pcode == pkey) {
            cout << "\n\tProduct's new code:\t";
            cin >> current->pcode;
            cout << "\n\tName of the product:\t";
            cin >> current->pname;
            cout << "\n\tDiscount:\t";
            cin >> current->dis;
            token++;
            break;
        }
        current = current->next;
    }

    if (token == 0) {
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\t\tRecord Not Found!\n";
        cout << "\n ---------------------------------------------------------------\n\n";
    }

    cout << "\nDo you want to modify another product?\nPress '1' for yes, '2' for no:\t";
    cin >> choice;

    if (choice != 1) {
        return;
    }
}

void Shopping::rem() {
    int pkey, token = 0;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tDelete a product\n";
    cout << "\n ---------------------------------------------------------------\n\n";

    list();

    cout << "\tProduct code:\t";
    cin >> pkey;

    if (head && head->pcode == pkey) {
        Product* temp = head;
        head = head->next;
        delete temp;
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\t\tProduct Deleted Successfully\n";
        cout << "\n ---------------------------------------------------------------\n\n";
        return;
    }

    Product* prev = head;
    Product* current = head->next;

    while (current) {
        if (current->pcode == pkey) {
            prev->next = current->next;
            delete current;
            cout << "\n ---------------------------------------------------------------\n\n";
            cout << "\t\tProduct Deleted Successfully\n";
            cout << "\n ---------------------------------------------------------------\n\n";
            token++;
            break;
        }
        prev = current;
        current = current->next;
    }

    if (token == 0) {
        cout << "\n ---------------------------------------------------------------\n\n";
        cout << "\t\tRecord Not Found!\n";
        cout << "\n ---------------------------------------------------------------\n\n";
    }
}

void Shopping::list() {
    cout << "\n\n_____________________\n";
    cout << "Product Code\tProduct Name\tPrice\n";
    cout << "\n\n_____________________\n";

    Product* current = head;
    while (current) {
        cout << current->pcode << "\t\t" << current->pname << "\t\t" << current->price << "\n";
        current = current->next;
    }
}

void Shopping::receipt() {
    int arrc[100], arrq[100];
    char choice;
    int c = 0;
    float total = 0;

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\t\tRECEIPT\n";
    cout << "\n ---------------------------------------------------------------\n\n";

    list();

    cout << "\n ---------------------------------------------------------------\n\n";
    cout << "\tPlace Your Orders\n";
    cout << "\n ---------------------------------------------------------------\n\n";

    do {
        cout << "\nEnter Product code:\t";
        cin >> arrc[c];
        cout << "\nEnter the Product Quantity:\t";
        cin >> arrq[c];
        cout << "\n";

        for (int i = 0; i < c; i++) {
            if (arrc[c] == arrc[i]) {
                cout << "\n ---------------------------------------------------------------\n\n";
                cout << "\tDuplicate Product Code. Please try again!\n";
                cout << "\n ---------------------------------------------------------------\n\n";
                continue;
            }
        }

        c++;

        cout << "\nDo you want to buy another product?\nPress 'y' if yes, 'n' for no:\t";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t_________RECEIPT_________\n";
    cout << "\nProduct Code\tProduct Name\tProduct Quantity\tPrice\tAmount\tAmount With Discount\n";
    cout << "\n\t______________________________\n\n";

    for (int i = 0; i < c; i++) {
        Product* current = head;
        while (current) {
            if (current->pcode == arrc[i]) {
                float amount = current->price * arrq[i];
                float discount = amount - (amount * current->dis / 100);
                total += discount;

                cout << "\n" << current->pcode << "\t\t" << current->pname << "\t\t" << arrq[i] << "\t\t" << current->price << "\t\t" << amount << "\t\t" << discount;
            }
            current = current->next;
        }
    }

    cout << "\n\t______________________________\n\n";
    cout << "\nTotal Amount:\t" << total;
    cout << "\n\n\t______________________________\n\n";
    cout << "\n------------------------------------------------------\n";
    cout << "\nThanks for Shopping with us!\n";
    cout << "\n------------------------------------------------------\n";

    cout << "\n\n========================================================================================================================\n\n";
}
int main() {
    Shopping shopping;

    shopping.menu();

    return 0;
}