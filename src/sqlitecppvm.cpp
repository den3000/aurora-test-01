#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(QObject *parent) : QAbstractListModel(parent)
{
    // TODO: 
    // 1. Extract DB into separate class and inject it in VM with DI
    // 2. Use https://doc.qt.io/qt-5/model-view-programming.html
    dao = BookDao();

    dao.openDb();
    books = dao.getAllBooks();
    qDebug() << "Loaded books count: " << books.size();

    if (books.size() == 0) {
        dao.insert(BookModel(0, "Leo Tolstoy", "Anna Karenina", 1300, 0));
        qDebug() << "Default book inserted";
    }
}

SQLiteCppVM::~SQLiteCppVM() { dao.closeDb(); }

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

void SQLiteCppVM::insert(const QString author, const QString title, const int totalPages, const int position)
{
    auto book = BookModel(0, author, title, totalPages, position);
    book.id = dao.insert(book);

    beginInsertRows(QModelIndex(), position, position);
    books.insert(position, book);
    endInsertRows();

    int next = position + 1;
    int end = books.size();
    for (int i = next; i < end; i++) { books[i].position = i; }
    emit dataChanged(createIndex(next, 0), createIndex(end, 0));
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

void SQLiteCppVM::update(const int id, const QString author, const QString title, const int totalPages, const int position)
{
    qDebug() << "Position: " << position;
    QSqlQuery query;

    query.prepare(
        "UPDATE books "
        "SET author = ?, title = ?, tp = ? "
        "WHERE id = ?;"
    );
    query.addBindValue(author);
    query.addBindValue(title);
    query.addBindValue(totalPages);
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    books[position].author = author;
    books[position].title = title;
    books[position].totalPages = totalPages;

    int next = position;
    int end = position;
    emit dataChanged(createIndex(next, 0), createIndex(end, 0));
}
