#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(QObject *parent) : QAbstractListModel(parent)
{
    books
        << BookModel("A0", "T0", 00, 0)
        << BookModel("A1", "T1", 11, 1)
        << BookModel("A2", "T2", 22, 2)
        << BookModel("A3", "T3", 33, 3)
        << BookModel("A4", "T4", 44, 4)
        << BookModel("A5", "T5", 55, 5)
        << BookModel("A6", "T6", 66, 6)
        << BookModel("A7", "T7", 77, 7)
        << BookModel("A8", "T8", 88, 8)
        << BookModel("A9", "T9", 99, 9);

    openDb();
}

SQLiteCppVM::~SQLiteCppVM() { closeDb(); }

QVariant SQLiteCppVM::data(const QModelIndex &index, int role) const
{
    // Default roleNames: https://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames

    if(!index.isValid()) return QVariant();
    switch (role) {
    case Author: return QVariant(books[index.row()].author);
    case Title: return QVariant(books[index.row()].title);
    case TotalPages: return QVariant(books[index.row()].totalPages);
    case Position: return QVariant(books[index.row()].position);
    }
    
    return QVariant();
}

QHash<int, QByteArray> SQLiteCppVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Author] = "author";
    roles[Title] = "title";
    roles[TotalPages] = "totalPages";
    roles[Position] = "position";
    return roles;
}

void SQLiteCppVM::openDb()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
       qDebug() << "Error: connection with database failed";
    } else {
       qDebug() << "Database: connection ok";
    }
}

void SQLiteCppVM::closeDb()
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

BookModel::BookModel(const QString author, const QString title, const int totalPages, const int position) {
    this->author = author;
    this->title = title;
    this->totalPages = totalPages;
    this->position = position;
}
