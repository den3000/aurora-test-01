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
}

QVariant SQLiteCppVM::data(const QModelIndex &index, int role) const
{
    // Default roleNames: https://doc.qt.io/qt-5/qabstractitemmodel.html#roleNames

    if(!index.isValid()) return QVariant();
    // switch (role) {
    // case NameRole: return QVariant(_backing[index.row()].name);
    // case DescriptionRole: return QVariant(_backing[index.row()].description);
    // case AmountRole: return QVariant(_backing[index.row()].amount);
    // }
    
    auto book = books[index.row()];
    return QVariant::fromValue(QString("# %1 title: %2 author: %3 pages: %4")
        .arg(book.position)
        .arg(book.title)
        .arg(book.author)
        .arg(book.totalPages)
    );
}

BookModel::BookModel(const QString author, const QString title, const int totalPages, const int position) {
    this->author = author;
    this->title = title;
    this->totalPages = totalPages;
    this->position = position;
}
