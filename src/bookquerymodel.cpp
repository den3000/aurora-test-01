#include "bookquerymodel.h"

// this include is required to access QSqlRecord type
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QSqlField>

BookQueryModel::BookQueryModel(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{
   setTable("books");
   setSort(4, Qt::SortOrder::AscendingOrder);
   setEditStrategy(QSqlTableModel::OnManualSubmit);
   select();
}

BookQueryModel::~BookQueryModel()
{
    qDebug() << "released";
}

QVariant BookQueryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) { return QVariant(); }
    if (role < Qt::UserRole) { return QSqlTableModel::data(index, role); }

    switch (role)
    {
    case Id: return extractValue("id", index.row(), role);
    case Author: return extractValue("author", index.row(), role);
    case Title: return extractValue("title", index.row(), role);
    case TotalPages: return extractValue("tp", index.row(), role);
    case Position: return extractValue("position", index.row(), role);
    default: return QSqlTableModel::data(index, role);
    }
}

QHash<int, QByteArray> BookQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Author] = "author";
    roles[Title] = "title";
    roles[TotalPages] = "tp";
    roles[Position] = "position";
    return roles;
}

bool BookQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return QSqlTableModel::setData(index, value, role);
}

void BookQueryModel::moveToTop(const int position)
{
    auto r = record(position);
    r.setValue("position", QVariant(0));
    setRecord(position, r);

    for (int i = 0; i < position; i++) {
        auto r = record(i);
        r.setValue("position", QVariant(i + 1));
        setRecord(i, r);
    }

    submitAll();
}

void BookQueryModel::remove(const int position)
{
    removeRow(position);
    submitAll();
}

QVariant BookQueryModel::extractValue(QString name, int row, int role) const
{
    auto rcrd = record(row);
//    qDebug() << "roleId: " << role
//             << " idx: " << row
//             << " value: " << rcrd.field(name).value()
//             << " role: " << name ;
    return rcrd.value(name);
}
