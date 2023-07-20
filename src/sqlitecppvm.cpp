#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(QObject *parent) : QAbstractListModel(parent)
{
    // TODO: 
    // 1. Define DB here and use it
    // 2. Use https://doc.qt.io/qt-5/model-view-programming.html
    // 3. Extract DB into separate class and inject it in VM with DI

    
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
    auto l = getAllBooks();
    qDebug() << "Loaded books count: " << l.size();
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

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "author TEXT NOT NULL,"
        "title TEXT NOT NULL,"
        "tp INTEGER NOT NULL,"
        "position INTEGER NOT NULL);"
    );
    
    if (!query.exec()) { qDebug() << "Create table error:" << query.lastError(); }
}

QList<BookModel> SQLiteCppVM::getAllBooks()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM books ORDER BY position ASC;");

    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    int idxId = query.record().indexOf("id");
    int idxAuthor = query.record().indexOf("author");
    int idxTitle = query.record().indexOf("title");
    int idxTp = query.record().indexOf("tp");
    int idxPosition = query.record().indexOf("position");

    auto result = QList<BookModel>();

    while (query.next()) 
    {
        auto id = query.value(idxId).toInt();
        auto author = query.value(idxAuthor).toString();
        auto title = query.value(idxTitle).toString();
        auto tp = query.value(idxTp).toInt();
        auto position = query.value(idxPosition).toInt();

        result.append(BookModel(author, title, tp, position));
    }
    
    return result;
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
