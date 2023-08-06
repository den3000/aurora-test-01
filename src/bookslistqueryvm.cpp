#include "bookslistqueryvm.h"

#include <QString>

BooksListQueryVM::BooksListQueryVM(IBooksQueryTableProvider * tableProvider, QObject *parent): QAbstractListModel(parent)
{
    qDebug() << "Created";
    // TODO:
    // 3. Use https://doc.qt.io/qt-5/model-view-programming.html

    this->tableProvider = tableProvider;
    this->tableProvider->openDb();
    this->bookQueryTable = this->tableProvider->booksQueryTable();

    books = this->bookQueryTable->getAllBooks();
    qDebug() << "Loaded books count: " << books.size();

    if (books.size() == 0) {
        this->bookQueryTable->insert(BookDao(0, "Leo Tolstoy", "Anna Karenina", 1300, 0));
        qDebug() << "Default book inserted";
    }
}

BooksListQueryVM::~BooksListQueryVM()
{
    delete bookQueryTable;
    tableProvider->closeDb();

    qDebug() << "Released";
}

QVariant BooksListQueryVM::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> BooksListQueryVM::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Author] = "author";
    roles[Title] = "title";
    roles[TotalPages] = "totalPages";
    roles[Position] = "position";
    return roles;
}

void BooksListQueryVM::insert(const QString author, const QString title, const int totalPages, const int position)
{
    auto book = BookDao(0, author, title, totalPages, position);
    book.id = bookQueryTable->insert(book);

    beginInsertRows(QModelIndex(), position, position);
    books.insert(position, book);
    endInsertRows();

    updateData(position + 1, books.size(), [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void BooksListQueryVM::remove(const int id, const int position)
{
    bookQueryTable->remove(id, position);

    beginRemoveRows(QModelIndex(), position, position);
    books.erase(books.begin() + position);
    endRemoveRows();

    updateData(position, books.size(), [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void BooksListQueryVM::moveToTop(const int id, const int position)
{
    bookQueryTable->moveToTop(id, position);

    beginMoveRows(QModelIndex(), position, position, QModelIndex(), 0);
    books.move(position, 0);
    endMoveRows();

    updateData(0, position+1, [](int idx, BookDao &book) {
        book.position = idx;
    });
}

void BooksListQueryVM::update(const int id, const QString author, const QString title, const int totalPages, const int position)
{
    bookQueryTable->update(id, author, title, totalPages);

    updateData(position, position+1, [author, title, totalPages](int idx, BookDao &book) {
        Q_UNUSED(idx)
        book.author = author;
        book.title = title;
        book.totalPages = totalPages;
    });
}

