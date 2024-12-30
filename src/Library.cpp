#include "Library.h"


Library::Library() : books(), users(), nextUserId(1) {
    for(const auto& pair : users) {
        nextUserId = max(nextUserId, pair.first + 1);
    }
};

bool Library::addBook(string& title, string& author, string& isbn, bool isAvailable) {
    if(books.find(isbn) != books.end()) {
        return false;
    }

    Book newBook(title, author, isbn, isAvailable);
    books[isbn] = newBook;
    return true;
}

bool Library::removeBook(const string& isbn) {
    return books.erase(isbn) > 0; 
}

Book* Library::searchBook(const string& isbn) {
    auto it = books.find(isbn);

    if(it != books.end()) {
        return &it->second;
    }

    return nullptr;
}

bool Library::addUser(string& name, string& username, string& password) {
    if(users.find(nextUserId) != users.end()) {
        cout << "Id@" << nextUserId << " already exists";
        return false;
    }

    for(const auto& pair : users) {
        if(pair.second.getUsername() == username) {
            cout << "Useranme is taken\n";
            return false;
        }
    }

    User newUser(nextUserId, name, username, password);
    users.emplace(nextUserId, newUser);
    nextUserId++;
    return true;
}

bool Library::removeUser(int id) {
    return users.erase(id) > 0;
}

User* Library::getUser(int id) {
    auto it = users.find(id);
    
    if(it != users.end()) {
        return &it->second;
    }

    return nullptr;
}

User* Library::getUserByUsername(string& username) {
    for(auto& pair : users) {
        if(pair.second.getUsername() == username) {
            return &pair.second;
        }
    }

    return nullptr;
}
