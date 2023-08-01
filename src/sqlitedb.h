#ifndef SQLITEDB_H
#define SQLITEDB_H


class SQLiteDb
{
public:
    SQLiteDb();
    ~SQLiteDb();

    void openDb();
    void closeDb();
};

#endif // SQLITEDB_H
