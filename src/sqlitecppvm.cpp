#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(BookTable * bookTable, QObject *parent): QAbstractListModel(parent)
{
    // TODO:
    // 3. Use https://doc.qt.io/qt-5/model-view-programming.html
    dao = bookTable;

    dao->openDb();
    books = dao->getAllBooks();
    qDebug() << "Loaded books count: " << books.size();

    if (books.size() == 0) {
        dao->insert(BookDao(0, "Leo Tolstoy", "Anna Karenina", 1300, 0));
        qDebug() << "Default book inserted";
    }
}

SQLiteCppVM::~SQLiteCppVM()
{
    dao->closeDb();
}

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
    auto book = BookDao(0, author, title, totalPages, position);
    book.id = dao->insert(book);

    beginInsertRows(QModelIndex(), position, position);
    books.insert(position, book);
    endInsertRows();

    updateData(position + 1, books.size(), [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void SQLiteCppVM::remove(const int id, const int position)
{
    dao->remove(id, position);

    beginRemoveRows(QModelIndex(), position, position);
    books.erase(books.begin() + position);
    endRemoveRows();

    updateData(position, books.size(), [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void SQLiteCppVM::moveToTop(const int id, const int position)
{
    dao->moveToTop(id, position);

    beginMoveRows(QModelIndex(), position, position, QModelIndex(), 0);
    books.move(position, 0);
    endMoveRows();

    updateData(0, position+1, [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void SQLiteCppVM::update(const int id, const QString author, const QString title, const int totalPages, const int position)
{
    dao->update(id, author, title, totalPages);

    updateData(position, position+1, [author, title, totalPages](int idx, BookDao &book) {
        Q_UNUSED(idx)
        book.author = author;
        book.title = title;
        book.totalPages = totalPages;
    });
}

template<typename F> inline
void SQLiteCppVM::updateData(const int start, const int end, F && lambda) {
    for (int i = start; i < end; i++) {
        lambda(i, books[i]);
    }
    // interesting that index value might be out of
    // data range and this will not break anything
    emit dataChanged(createIndex(start, 0), createIndex(end, 0));
}

inline
void SQLiteCppVM::updateDataAlt(const int start, const int end, std::function<void(int, BookDao &)> && lambda)
{
    for (int i = start; i < end; i++) {
        lambda(i, books[i]);
    }
    emit dataChanged(createIndex(start, 0), createIndex(end, 0));
}
