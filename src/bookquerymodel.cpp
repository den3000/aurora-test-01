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
    case Id: return record(index.row()).value("id");
    case Author: return record(index.row()).value("author");
    case Title: return record(index.row()).value("title");
    case TotalPages: return record(index.row()).value("tp");
    case Position: return record(index.row()).value("position");
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
    switch (role)
    {
    case Id: return false;
    case Author: {
        auto r = record(index.row());
        r.setValue("author", value);
        setRecord(index.row(), r);
        return true;
    }
    case Title: {
        auto r = record(index.row());
        r.setValue("title", value);
        setRecord(index.row(), r);
        return true;
    }
    case TotalPages: {
        auto r = record(index.row());
        r.setValue("tp", value);
        setRecord(index.row(), r);
        return true;
    }
    case Position: return false;
    default: QSqlTableModel::setData(index, value, role);
    }

    qDebug() << "index " << index << " value " << value << " role " << role;
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

    for (int i = position; i < rowCount(); i++) {
        auto r = record(i);
        r.setValue("position", QVariant(i - 1));
        setRecord(i, r);
    }

    submitAll();
}

void BookQueryModel::insert(const QString author, const QString title, const int totalPages, const int position)
{
    QSqlRecord r = record();
    r.setValue("author", QVariant::fromValue(author));
    r.setValue("title", QVariant::fromValue(title));
    r.setValue("tp", QVariant::fromValue(totalPages));
    r.setValue("position", QVariant::fromValue(position));

    if (!insertRecord(position, r)) { qDebug() << lastError(); }

    for (int i = position + 1; i < rowCount(); i++) {
        auto r = record(i);
        r.setValue("position", QVariant(i));
        setRecord(i, r);
    }

    submitAll();
}
