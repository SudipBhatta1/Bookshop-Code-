#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>
#include <cctype>
#include <conio.h>
#include <cstring>
#include <cstdlib> 
#include <sstream>


using namespace std;


class books {
public:
    void options();
    void bookadd();
    void bookshow();
    void bookcheck();
    void bookdelete();
    void booksale();
    void viewsoldbooks();
    void changeLoginCredentials();
    void bookShopRecord(); 
};

void books::options() {
    cout << "\n\n\t\t\t\tCONTROL PANEL";
    cout << "\n\n1. ADD BOOK";
    cout << "\n2. DISPLAY BOOKS";
    cout << "\n3. CHECK PARTICULAR BOOK";
    cout << "\n4. DELETE BOOK";
    cout << "\n5. SALE BOOK";
    cout << "\n6. VIEW SOLD BOOKS";
    cout << "\n7. CHANGE USERNAME AND PASSWORD";
    cout << "\n8. EXIT";
}

void books::changeLoginCredentials() {
    system("cls");
    string new_username, new_password;

    cout << "\n\n\t\t\t\tCHANGE USERNAME AND PASSWORD";
    cout << "\n\nEnter new username: ";
    cin >> new_username;
    cout << "Enter new password: ";
    cin >> new_password;

    ofstream loginFile("login.txt");
    loginFile << new_username << "\n" << new_password;
    loginFile.close();

    cout << "\nUsername and Password changed successfully!\n";
    system("pause");
}

void login();
void registerUser() {
    system("cls");
    string username, password;
    cout << "\n\n\t\tWELCOME TO BOOKSHOP MANAGEMENT SYSTEM";
    cout << "\n\n\t\t\t\tREGISTER";
    cout << "\n\nEnter a new username: ";
    cin >> username;
    cout << "Enter a new password: ";
    cin >> password;

    ofstream loginFile("login.txt");
    loginFile << username << "\n" << password;
    loginFile.close();

    cout << "\nRegistration successful!\n";
    system("pause");

    login(); 
}

void login() {
    system("cls");
    cout << "\n\n\t\tWELCOME TO BOOKSHOP MANAGEMENT SYSTEM";
    cout << "\n\n\t\t\t\tLOGIN PAGE";

    while (true) {
        cout << "\n\nEnter username: ";
        string login_username;
        cin >> login_username;
        cout << "Enter password: ";
        string password;
        cin >> password;

        ifstream readLoginFile("login.txt");
        if (readLoginFile) {
            string stored_username, stored_password;
            readLoginFile >> stored_username >> stored_password;
            readLoginFile.close();

            if (login_username == stored_username && password == stored_password) {
                cout << "\nLogin successful!\n";
                system("pause");
                system("cls");
                return;
            }
        }
        cout << "\nLogin failed. Please try again.\n";
    }
}


void books::bookadd() {
    system("cls");
    ofstream file("book.txt", ios::app);
    float price;
    string b_name, a_name, b_id;

    cout << "\n\n\t\t\t\tADD BOOKS";

    while (true) {
        cout << "\n\nBook ID : ";
        cin >> b_id;

        ifstream infile("book.txt");
        string existing_id;
        bool idExists = false;

        while (infile >> existing_id) {
            infile.ignore(10000, '\t');
            if (existing_id == b_id) {
                cout << "\nBook ID already exists. Please enter a different Book ID.\n";
                idExists = true;
                break;
            }
        }
        infile.close();

        if (!idExists) {
            break; 
        }
    }

    if (b_id.empty()) {
        cout << "\nBook ID cannot be empty. Please enter a valid Book ID.\n";
        return;
    }

    cin.ignore(); 
    cout << "\nBook Name : ";
    getline(cin, b_name);

    cout << "\nAuthor Name : ";
    getline(cin, a_name);

    while (true) {
        cout << "\nPrice in Rupee : ";
        cin >> price;

        if (cin.fail()) {
            cout << "\nInvalid input. Please enter a number for price.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }

    file << b_id << "\t" << b_name << "\t" << a_name << "\t" << price << "\n";
    file.close();
    cout << "\nBook added successfully!\n";
    system("pause");
}


void books::bookshow() {
    system("cls");
    ifstream file("book.txt");
    if (!file) {
        cout << "Error opening file!\n";
        system("pause");
        return;
    }

    float price;
    string b_name, b_id, a_name;

    cout << "\n\n\t\t\t\t\tAll BOOKS";

    cout << "\n\n";
 cout << "--------------------------------------------------------------------------------------------------------------\n";
    cout << "| ";
    cout << setw(20) << left << "Book ID";
    cout << " | ";
    cout << setw(30) << left << "Book";
    cout << " | ";
    cout << setw(20) << left << "Author";
    cout << " | ";
    cout << setw(15) << left << "Price";
    cout << " | ";
    cout << setw(10) << left << "Status";
    cout << " | ";
    cout << "\n";
 cout << "--------------------------------------------------------------------------------------------------------------\n";

    while (file >> b_id) {
        file.ignore();
        getline(file, b_name, '\t');
        getline(file, a_name, '\t');
        file >> price;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        // Check if the book has been sold
        ifstream soldFile("sold_books.txt");
        string sold_id;
        bool sold = false;
        while (soldFile >> sold_id) {
            if (b_id == sold_id) {
                sold = true;
                break;
            }
            soldFile.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        soldFile.close();

        cout << "| ";
        cout << setw(20) << left << b_id;
        cout << " | ";
        cout << setw(30) << left << b_name;
        cout << " | ";
        cout << setw(20) << left << a_name;
        cout << " | ";
        cout << setw(15) << left << price;
        cout << " | ";
        cout << setw(10) << left << (sold ? "SOLD" : "Available");
        cout << " | ";
        cout << "\n";
         cout << "--------------------------------------------------------------------------------------------------------------\n";
    }
    file.close();

    system("pause");
}

void books::bookcheck() {
    system("cls");
    ifstream file("book.txt");
    if (!file) {
        cout << "Error opening file!\n";
        system("pause");
        return;
    }

    string search_id;
    cout << "Enter the Book ID to check: ";
    cin >> search_id;

    float price;
    string b_name, b_id, a_name;
    bool found = false;

    cout << "\n\n\t\t\t\t\tBOOK DETAILS\n\n";
  cout << "--------------------------------------------------------------------------------------------------------------\n";
    cout << "| ";
    cout << setw(20) << left << "Book ID";
    cout << " | ";
    cout << setw(30) << left << "Book";
    cout << " | ";
    cout << setw(20) << left << "Author";
    cout << " | ";
    cout << setw(15) << left << "Price";
    cout << " | ";
    cout << setw(15) << left << "Status";
   
    cout << "\n";
 cout << "--------------------------------------------------------------------------------------------------------------\n";

    while (file >> b_id) {
        file.ignore();
        getline(file, b_name, '\t');
        getline(file, a_name, '\t');
        file >> price;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        if (b_id == search_id) {
            
            ifstream soldFile("sold_books.txt");
            string sold_id;
            bool sold = false;
            while (soldFile >> sold_id) {
                if (b_id == sold_id) {
                    sold = true;
                    break;
                }
                soldFile.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            soldFile.close();

            cout << "| ";
            cout << setw(20) << left << b_id;
            cout << " | ";
            cout << setw(30) << left << b_name;
            cout << " | ";
            cout << setw(20) << left << a_name;
            cout << " | ";
            cout << setw(15) << left << price;
            cout << " | ";
            cout << setw(15) << left << (sold ? "SOLD" : "Available");
            
            cout << "\n";
  cout << "--------------------------------------------------------------------------------------------------------------\n";

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n\nBook with ID " << search_id << " not found!!" << endl<<endl;
    }

    file.close();
    system("pause");
}

void books::bookdelete() {
    system("cls");
    string delete_id;
    cout << "Enter the Book ID to delete: ";
    cin >> delete_id;

    ifstream inFile("book.txt");
    ofstream tempFile("temp.txt");

    float price;
    string b_name, b_id, a_name;
    bool found = false;

    while (inFile >> b_id) {
        inFile.ignore();
        getline(inFile, b_name, '\t');
        getline(inFile, a_name, '\t');
        inFile >> price;
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (b_id != delete_id) {
            tempFile << b_id << "\t" << b_name << "\t" << a_name << "\t" << price << "\n";
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove("book.txt");
        rename("temp.txt", "book.txt");
        cout << "\n\nBook with ID " << delete_id << " has been deleted successfully." << endl<<endl;
    } else {
        remove("temp.txt");
        cout << "\n\nBook with ID " << delete_id << " not found!!" << endl<<endl;
    }

    system("pause");
}

void books::booksale() {
    system("cls");
    string sale_id, customer_name;
    cout << "Enter the Book ID: ";
    cin >> sale_id;

    ifstream bookFile("book.txt");
    bool id_found = false;
    string b_name, b_id, a_name;
    float price;

    while (bookFile >> b_id) {
        bookFile.ignore();
        getline(bookFile, b_name, '\t');
        getline(bookFile, a_name, '\t');
        bookFile >> price;
        bookFile.ignore(numeric_limits<streamsize>::max(), '\n');

        if (b_id == sale_id) {
            id_found = true;
            break;
        }
    }

    bookFile.close();

    if (!id_found) {
        cout << "\n\nBook with ID \"" << sale_id << "\" not found!!" << endl;
        system("pause");
        return;
    }

    ifstream inFile("sold_books.txt");
    string sold_id;
    bool alreadySold = false;
    while (inFile >> sold_id) {
        inFile.ignore();
        
        if (sale_id == sold_id) {
            cout << "\n\nBook with ID \"" << sale_id << "\" has already been sold!" << endl;
            alreadySold = true;
            break;
        }
        inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    inFile.close();

    if (alreadySold) {
        system("pause");
        return;
    }

    cout << "Enter the Customer Name: ";
    cin.ignore(); 
    getline(cin, customer_name); 

    ofstream soldFile("sold_books.txt", ios::app);

    soldFile << b_id << "\t" << b_name << "\t" << a_name << "\t" << customer_name << "\t" << price << "\n";
    soldFile.close();

    cout << "\n\nBook sold successfully!" << endl;
    system("pause");
}

void books::viewsoldbooks() {
    system("cls");

    ifstream file("sold_books.txt");
    if (!file) {
        cout << "Error opening file!\n";
        system("pause");
        return;
    }

    float price;
    string b_name, b_id, a_name, customer_name;

    cout << "\n\n\t\t\t\t\tSOLD BOOKS DETAILS";

    cout << "\n\n";
    cout << "----------------------------------------------------------------------------------------------------------------------\n";
    cout << "| ";
    cout << setw(20) << left << "Book ID";
    cout << " | ";
    cout << setw(30) << left << "Book";
    cout << " | ";
    cout << setw(20) << left << "Author";
    cout << " | ";
    cout << setw(25) << left << "Customer Name";
    cout << " | ";
    cout << setw(15) << left << "Price" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------------\n";

    while (file >> b_id) {
        file.ignore();
        getline(file, b_name, '\t');
        getline(file, a_name, '\t');
        getline(file, customer_name, '\t');
        file >> price;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "| ";
        cout << setw(20) << left << b_id;
        cout << " | ";
        cout << setw(30) << left << b_name;
        cout << " | ";
        cout << setw(20) << left << a_name;
        cout << " | ";
        cout << setw(25) << left << customer_name;
        cout << " | ";
        cout << setw(15) << left << price << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------\n";
    }
    file.close();

    system("pause");
}

void books::bookShopRecord() {
    int choice;
    books b;

    while (true) {
        system("cls");

        b.options();

        cout << "\n\nEnter your choice : ";
        string input;
        cin >> input;

        stringstream ss(input);
        if (!(ss >> choice) || ss.peek() != EOF) { 
            cout << "\nInvalid input. Please enter a number.\n";
            system("pause");
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                b.bookadd();
                break;
            case 2:
                b.bookshow();
                break;
            case 3:
                b.bookcheck();
                break;
            case 4:
                b.bookdelete();
                break;
            case 5:
                b.booksale();
                break;
            case 6:
                b.viewsoldbooks();
                break;
            case 7:
                b.changeLoginCredentials();
                break;
            case 8:
                return;
            default:
                cout << "\n\nINVALID CHOICE\n";
                system("pause");
        }
    }
}

int main() {
    ifstream loginFile("login.txt");
    if (!loginFile) {
        registerUser(); 
    } else {
        login();
    }

    books bookManager; 
    bookManager.bookShopRecord(); 

    return 0; 
}


