#ifndef BOOK_H
#define BOOK_H

#include <string>

using namespace std;

class Book {
    public:
        Book() : title(""), author(""), isbn(""), isAvailable(true) {};
        Book(const string& title, const string& author, const string& isbn, bool isAvailable = true) 
            : title(title), author(author), isbn(isbn), isAvailable(isAvailable), borrowCount(0) {};

        const string& getTitle() const { return title; }
        const string& getAuthor() const { return author; }
        const string& getIsbn() const { return isbn; }
        bool getAvailability() const { return isAvailable; }
        int getBorrowCount() const { return borrowCount; }

        void setAvailability(bool status) { isAvailable = status; }
        void incrementBorrowCount() { borrowCount++; }
    private:
        string title;
        string author;
        string isbn;
        bool isAvailable;
        int borrowCount;
};

#endif // BOOK_H