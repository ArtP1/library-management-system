#include "User.h"

bool User::borrowBook(const string& isbn) {
    if(borrowedBooks.size() >= 5) {
        return false;
    }

    borrowedBooks.push_back(isbn);
    return true;
}

bool User::returnBook(const string& isbn) {
    auto it = find(borrowedBooks.begin(), borrowedBooks.end(), isbn);

    if(it != borrowedBooks.end()) {
        borrowedBooks.erase(it);
        return true;
    }

    return false;
}
