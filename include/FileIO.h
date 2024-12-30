#ifndef FILE_IO_H
#define FILE_IO_H

#include "Library.h"
#include <string>

class FileIO {
    public:
        FileIO();
        static bool loadBooks(Library& lib, const string& fpath);
        static bool saveBooks(const Library& lib, const string& fpath);

        static bool loadUsers(Library& lib, const string& fpath);
        static bool saveUsers(const Library& lib, const string& fpath);
};

#endif // FILE_IO_H
