#include "sqlitedb.h"

#include <QDebug>
#include <QSqlDatabase>

SQLiteDb::SQLiteDb()
{
    qDebug() << "Created";
}

SQLiteDb::~SQLiteDb()
{
    qDebug() << "Released";
}

void SQLiteDb::openDb()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
       qDebug() << "Error: connection with database failed";
    } else {
       qDebug() << "Database: connection ok";
    }
}

void SQLiteDb::closeDb()
{
    {
        // this additional scope is necessary, because allows
        // to release db object after it was closed but before
        // removeDatabase will be called
        auto db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}


BookModelTable *SQLiteDb::booksModelTable(QObject *parent)
{
    return new BookModelTable(parent);
}

BookQueryTable *SQLiteDb::booksQueryTable()
{
    return new BookQueryTable();
}
