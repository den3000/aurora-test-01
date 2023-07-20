#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(QObject *parent) : QAbstractListModel(parent)
{
    // TODO: 
    // 1. Define DB here and use it
    // 2. Use https://doc.qt.io/qt-5/model-view-programming.html
    // 3. Extract DB into separate class and inject it in VM with DI
    
    openDb();
    books = getAllBooks();
    qDebug() << "Loaded books count: " << books.size();

    if (books.size() == 0) {
        insert(BookModel(0, "Leo Tolstoy", "Anna Karenina", 1300, 0));
        qDebug() << "Default book inserted";
    }
}

SQLiteCppVM::~SQLiteCppVM() { closeDb(); }

QVariant SQLiteCppVM::data(const QModelIndex &index, int role) const
{
    // Default roleNames: https://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames

    if(!index.isValid()) return QVariant();
    switch (role) {
    case Id: return QVariant(books[index.row()].id);
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
    roles[Id] = "id";
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

        result.append(BookModel(id, author, title, tp, position));
    }
    
    return result;
}

void SQLiteCppVM::insert(BookModel book)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE books "
        "SET position = position + 1 "
        "WHERE position >= ?;"
    );
    query.addBindValue(book.position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare(
        "INSERT INTO books "
        "(author, title, tp, position) "
        "VALUES(?, ?, ?, ?);"
    );
    query.addBindValue(book.author);
    query.addBindValue(book.title);
    query.addBindValue(book.totalPages);
    query.addBindValue(book.position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    auto insertId = query.lastInsertId().toInt();
    book.id = insertId;

    beginInsertRows(QModelIndex(), book.position, book.position);
    books.insert(book.position, book);
    endInsertRows();

    int next = book.position + 1;
    int end = books.size();
    for (int i = next; i < end; i++) { books[i].position = i; }
    emit dataChanged(createIndex(next, 0), createIndex(end, 0));
}

void SQLiteCppVM::insert(const QString author, const QString title, const int totalPages, const int position)
{
    insert(BookModel(0, author, title, totalPages, position));
}

void SQLiteCppVM::remove(const int id, const int position)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE books "
        "SET position = position - 1 "
        "WHERE position >= ?;"
    );
    query.addBindValue(position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare("DELETE FROM books WHERE id = ?;");
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    beginRemoveRows(QModelIndex(), position, position);
    books.erase(books.begin() + position);
    endRemoveRows();

    int next = position;
    int end = books.size();
    for (int i = next; i < end; i++) { books[i].position = i; }
    emit dataChanged(createIndex(next, 0), createIndex(end, 0));
}

void SQLiteCppVM::moveToTop(const int id, const int position)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE books "
        "SET position = position + 1 "
        "WHERE position < ?;"
    );
    query.addBindValue(position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare(
        "UPDATE books "
        "SET position = 0 "
        "WHERE id = ?;"
    );
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    beginMoveRows(QModelIndex(), position, position, QModelIndex(), 0);
    books.move(position, 0);
    endMoveRows();

    int next = 0;
    int end = position;
    for (int i = next; i <= end; i++) { books[i].position = i; }
    emit dataChanged(createIndex(next, 0), createIndex(end, 0));
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

BookModel::BookModel(const int id, const QString author, const QString title, const int totalPages, const int position) {
    this->id = id;
    this->author = author;
    this->title = title;
    this->totalPages = totalPages;
    this->position = position;
}
