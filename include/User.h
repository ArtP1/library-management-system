#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class User {
    public:
        User(int id, string& name,const string& username, const string& password) 
            : id(id), name(name), username(username), password(password), borrowedBooks() {};

        int getId() const { return id; }
        const string& getName() const { return name; }
        const string& getUsername() const { return username; }
        const string& getPassword() const { return password; }
        const vector<string>& getBorrowedBooks() const { return borrowedBooks; }

        bool borrowBook(const string& isbn);
        bool returnBook(const string& isbn);
        bool hasBorrowed(const string& isbn) const {
            return find(borrowedBooks.begin(), borrowedBooks.end(), isbn) != borrowedBooks.end();
        }
    private:
        const int id;
        string name;
        vector<string> borrowedBooks;
        string username;
        string password;
};

#endif // USER_H