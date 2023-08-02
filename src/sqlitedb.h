#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "bookquerytable.h"
#include "bookmodeltable.h"

class SQLiteDb:
        public IBooksQueryTableProvider,
        public IBooksModelTableProvider
{
public:
    SQLiteDb();
    ~SQLiteDb();

    // IDbProvider interface
public:
    void openDb();
    void closeDb();

    // IBooksModelTableProvider interface
public:
    BookModelTable *booksModelTable();

    // IBooksQueryTableProvider interface
public:
    BookQueryTable *booksQueryTable();
};

#endif // SQLITEDB_H
