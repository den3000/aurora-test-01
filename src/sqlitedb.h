#ifndef SQLITEDB_H
#define SQLITEDB_H

#include "idbprovider.h"
#include "bookquerytable.h"
#include "bookmodeltable.h"

/*
    1. It is not recommended to save anywhere any references to DB by Qt
    2. By default when creating a DB default connectionName will be used
    3. In the app you can use multiple DB, which might be managed by connectionNames
    4. While this situation is not so common for mobile app, it still might be the case

    Summing up all above the implementation that you see now below has been chosen
    It might looks like overcomplicated, but has some space to be extaneded with 
    multiple DBs managed by connectionNames in a generalised way when it is necvessary
*/

class SQLiteDb:
        public IDbProvider,
        public IBooksQueryTableProvider,
        public IBooksModelTableProvider
{
public:
    SQLiteDb();
    ~SQLiteDb();

public:
    // IDbProvider interface
    void connectToDBs() override;
    void disconnectFromDBs() override;

    // IBooksModelTableProvider interface
    BookModelTable *booksModelTable(QObject *parent = nullptr) const override;

    // IBooksQueryTableProvider interface
    BookQueryTable *booksQueryTable() const override;
};

#endif // SQLITEDB_H
