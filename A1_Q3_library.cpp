#include <iostream>
#include <iomanip>
using namespace std;

const int N = 10;

struct Date {
    int day;
    int month;
    int year;
};

struct Book {
    int id;
    double price;
    Date date;
};

struct Library {
    Book books[N] = { 0 };
    int num;
};

void sort_id(Library *p);
void add(Library *p);
void show(Library *p);
void listOptions(Library *p);
void del(Library *p);
void sort(Library *p);

void listOptions(Library *p) {
    int opt;
    cout << "~~~~~~~~~Welcome!~~~~~~~~~~" << endl;
    cout << "0: Exit" << endl;
    cout << "1: Add" << endl;
    cout << "2: Show" << endl;
    cout << "3: Delete" << endl;
    cout << "4: Sort" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    cin >> opt;

    if (opt == 0) {
        cout << "Bye!";
    }
    else if (opt == 1) {
        add(p);
        listOptions(p);
    }
    else if (opt == 2) {
        show(p);
        listOptions(p);
    }
    else if (opt == 3) {
        del(p);
        listOptions(p);
    }
    else if (opt == 4) {
        sort(p);
        listOptions(p);
    }
   

}

void add(Library* p) {
    // Check if the library is full
    if (p->num >= N) {
        cout << "Library is full" << endl;
        return;
    }

    // Input Book ID with validation for uniqueness
    cout << "Input Book ID: " << endl;
    cin >> p->books[p->num].id;

    // Validate uniqueness of Book ID
    bool isUniqueID = false;
    while (!isUniqueID) {
        isUniqueID = true;
        for (int i = 0; i < p->num; i++) {
            if (p->books[i].id == p->books[p->num].id) {
                cin >> p->books[p->num].id;
                isUniqueID = false;
                break;
            }
        }
    }

    // Input Price
    cout << "Input Price: " << endl;
    cin >> p->books[p->num].price;

    // Input Date (dd mm yyyy)
    cout << "Input Date (dd mm yyyy): " << endl;
    cin >> p->books[p->num].date.day >> p->books[p->num].date.month >> p->books[p->num].date.year;
    cout << endl;

    // Increment the number of books in the library
    p->num++;
}



void show(Library* p) {
    for (int bookIndex = 0; bookIndex < p->num; bookIndex++) {
        cout << setfill('0') << setw(3) << p->books[bookIndex].id;
        cout << "     ";

        if (bookIndex == p->num - 1) {
            cout << fixed << setprecision(2) << setw(5);
        }
        else {
            cout << setprecision(2) << fixed << setw(5);
        }

        cout << p->books[bookIndex].price << "   ";
        cout << p->books[bookIndex].date.day << "-" << p->books[bookIndex].date.month << "-" << p->books[bookIndex].date.year;
        cout << endl;
    }
    cout << endl;
}


void del(Library *p) {
    cout << "Enter the ID to be deleted" << endl;
    int id_del;
    cin >> id_del;

    int i;
    int j = 0;

    while (j < 2) {
        for (i = 0; i < p->num; ++i) {
            if (p->books[i].id == id_del) {
                p->books[i].id = 0;
                p->books[i].price = 0.0;
                p->books[i].date.day = 0;
                p->books[i].date.month = 0;
                p->books[i].date.year = 0;

                for (int w = i + 1; w < p->num; ++w) {
                    p->books[w - 1] = p->books[w];
                }

                --(p->num);
                cout << endl;

                return;
            }
        }

        cout << "The ID cannot be found" << endl << endl;
        return;
    }
}

void sort_id(Library* p) {
    // Bubble sort for sorting books based on ID
    for (int currentBookIndex = 0; currentBookIndex < p->num; currentBookIndex++) {
        for (int nextBookIndex = 0; nextBookIndex < p->num - 1; nextBookIndex++) {
            // Compare the IDs of two books
            if (p->books[nextBookIndex].id > p->books[nextBookIndex + 1].id) {
                // Swap the books if the current book has a greater ID
                Book temporaryBook = p->books[nextBookIndex];
                p->books[nextBookIndex] = p->books[nextBookIndex + 1];
                p->books[nextBookIndex + 1] = temporaryBook;
            }
        }
    }
}




void sort_date(Library* p) {
    // Bubble sort for sorting books based on date and ID
    for (int currentBook = 0; currentBook < p->num; currentBook++) {
        for (int nextBook = 0; nextBook < p->num - 1; nextBook++) {
            // Compare the dates of two books
            if (p->books[nextBook].date.year > p->books[nextBook + 1].date.year ||
                (p->books[nextBook].date.year == p->books[nextBook + 1].date.year &&
                    p->books[nextBook].date.month > p->books[nextBook + 1].date.month) ||
                (p->books[nextBook].date.year == p->books[nextBook + 1].date.year &&
                    p->books[nextBook].date.month == p->books[nextBook + 1].date.month &&
                    p->books[nextBook].date.day > p->books[nextBook + 1].date.day)) {
                // Swap the books if the current book is greater
                Book temp = p->books[nextBook];
                p->books[nextBook] = p->books[nextBook + 1];
                p->books[nextBook + 1] = temp;
            }
            else if (p->books[nextBook].date.year == p->books[nextBook + 1].date.year &&
                p->books[nextBook].date.month == p->books[nextBook + 1].date.month &&
                p->books[nextBook].date.day == p->books[nextBook + 1].date.day) {
                // If dates are equal, compare IDs and swap if necessary
                if (p->books[nextBook].id > p->books[nextBook + 1].id) {
                    Book temp = p->books[nextBook];
                    p->books[nextBook] = p->books[nextBook + 1];
                    p->books[nextBook + 1] = temp;
                }
            }
        }
    }
}


void sort(Library *p) {
    int n;
    cout << "1: Sort by ID" << endl;
    cout << "2: Sort by Date" << endl;
    cin >> n;
    cout << endl;
    if (n == 1) {
        sort_id(p);
    }
    else if (n == 2) {
        sort_date(p);
    }


}

void init(Library* p) {
    p->books[p->num].id = 3;
    p->books[p->num].price = 10.5;
    p->books[p->num].date.day = 15;
    p->books[p->num].date.month = 1;
    p->books[p->num].date.year = 1990;
    (p->num)++;

    p->books[p->num].id = 2;
    p->books[p->num].price = 20.55;
    p->books[p->num].date.day = 15;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2024;
    (p->num)++;

    p->books[p->num].id = 4;
    p->books[p->num].price = 10.5;
    p->books[p->num].date.day = 20;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2021;
    (p->num)++;

    p->books[p->num].id = 1;
    p->books[p->num].price = 30.1;
    p->books[p->num].date.day = 20;
    p->books[p->num].date.month = 2;
    p->books[p->num].date.year = 2021;
    (p->num)++;
}

int main() {
    Library lib;
    lib.num = 0;

    init(&lib);
    listOptions(&lib);

    return 0;
}
