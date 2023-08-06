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

public:
    // IDbProvider interface
    void openDb() override;
    void closeDb() override;

    // IBooksModelTableProvider interface
    BookModelTable *booksModelTable(QObject *parent = nullptr) const override;

    // IBooksQueryTableProvider interface
    BookQueryTable *booksQueryTable() const override;
};

#endif // SQLITEDB_H
