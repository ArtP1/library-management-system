#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "Book.h"
#include "User.h"

using namespace std;

class Library {
    public:
        Library();

        const unordered_map<string, Book>& getBooks() const { return books; }
        bool addBook(string& title, string& author, string& isbn, bool isAvailable);
        bool removeBook(const string& isbn);
        Book* searchBook(const string& isbn);

        const unordered_map<int, User>& getUsers() const { return users; }
        bool addUser(string& name, string& username, string& password);
        bool removeUser(int id);
        User* getUser(int id);
        User* getUserByUsername(string& username);
    private:
       unordered_map<string, Book> books; // by ISBN
       unordered_map<int, User> users; // by id
       int nextUserId;
};

#endif // LIBRARY_H