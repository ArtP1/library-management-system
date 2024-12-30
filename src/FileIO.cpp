#include "FileIO.h"
#include <fstream>
#include <iostream>
#include <sstream>

FileIO::FileIO()
{
}

bool FileIO::loadBooks(Library& lib, const string& fpath) {
    ifstream file(fpath);

    if(!file.is_open()) {
        cerr << "Failed to open file: " << fpath << endl;
        return false;
    }

    string line;
    while(getline(file, line)) {
        stringstream ss(line);
        string title, author, isbn, isAvailableStr;

        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, isbn, ',');
        getline(ss, isAvailableStr);

        bool isAvailable = (isAvailableStr == "1");
        lib.addBook(title, author, isbn, isAvailable);
    }

    file.close();
    return true;
}

bool FileIO::saveBooks(const Library& lib, const string& fpath) {
    ofstream file(fpath);

    if(!file.is_open()) {
        cerr << "Failed to open file: " << fpath << endl;
        return false;
    }

    for(const auto& pair : lib.getBooks()) {
        const Book& book = pair.second;

        file << book.getTitle() << ","
             << book.getAuthor() << ","
             << book.getIsbn() << ","
             << (book.getAvailability() ? "1" : "0") << "\n";
    }

    file.close();
    return true;
}


bool FileIO::loadUsers(Library& lib, const string& fpath) {
    ifstream file(fpath);
    
    if(!file.is_open()) {
        cerr << "Failed to open file: " << fpath << endl;
        return false;
    }

    string line;
    while(getline(file, line)) {
        stringstream ss(line);

        int id;
        vector<string> borrowedBooks;
        string idStr, name, username, password, borrowedBooksStr;

        if(!getline(ss, idStr, ',') || !(id = stoi(idStr))) {
            cerr << "Failed to parse ID in line: " << line << endl;
            continue;
        }

        if (!getline(ss, name, ',')) {
            cerr << "Failed to parse name in line: " << line << endl;
            continue;
        }

        try {
            id = stoi(idStr);
        } catch (const invalid_argument& e) {
            cerr << "Invalid ID format in line: " << line << endl;
            continue;
        }

        if (!getline(ss, username, ',')) {
            cerr << "Failed to parse username in line: " << line << endl;
            continue;
        }

        if (!getline(ss, password, ',')) {
            cerr << "Failed to parse password in line: " << line << endl;
            continue;
        }

        if (getline(ss, borrowedBooksStr)) {
            stringstream booksStream(borrowedBooksStr);
            string book;
            while(getline(booksStream, book, '|')) {
                borrowedBooks.push_back(book);
            }
        }

        
        if(lib.addUser(name, username, password)) {
            User* user = lib.getUserByUsername(username);
            for(const auto& isbn : borrowedBooks) {
                user->borrowBook(isbn);
            }
        }
    }

    file.close();
    return true;
}

bool FileIO::saveUsers(const Library& lib, const string& fpath) {
    ofstream file(fpath);
    
    if(!file.is_open()) {
        cerr << "Failed to open file: " << fpath << endl;
        return false;
    }

    for(const auto& pair : lib.getUsers()) {
        const User& user = pair.second;

        const auto& borrowedBooks = user.getBorrowedBooks();
        string borrowedBooksStr;

        for(size_t i = 0; i < borrowedBooks.size(); i++) {
            borrowedBooksStr += borrowedBooks[i];
            if(i < borrowedBooks.size() - 1) {
                borrowedBooksStr += "|";
            }
        }

        file << user.getId() << ","
             << user.getName() << ","
             << user.getUsername() << ","
             << user.getPassword();

        if(!borrowedBooksStr.empty()) {
            file << "," << borrowedBooksStr;
        }

        file << "\n";
    }

    file.close();
    return true;
}

