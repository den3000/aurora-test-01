#include "bookmodeltable.h"

// this include is required to access QSqlRecord type
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QSqlField>

BookModelTable::BookModelTable(QObject *parent, QSqlDatabase db) : QSqlTableModel(parent, db)
{
    qDebug() << "Created";

    // TODO: define table here
    
    setTable("books");
    setSort(4, Qt::SortOrder::AscendingOrder);
    setEditStrategy(QSqlTableModel::OnManualSubmit);
    select();
}

BookModelTable::~BookModelTable()
{
    qDebug() << "Released";
}

QVariant BookModelTable::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> BookModelTable::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Id] = "id";
    roles[Author] = "author";
    roles[Title] = "title";
    roles[TotalPages] = "tp";
    roles[Position] = "position";
    return roles;
}

bool BookModelTable::setData(const QModelIndex &index, const QVariant &value, int role)
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

    return QSqlTableModel::setData(index, value, role);
}

void BookModelTable::moveToTop(const int position)
{
    auto r = record(position);
    r.setValue("position", QVariant(0));
    setRecord(position, r);

    updateRecordsInRange(0, position, true, [](int row, QSqlRecord &record) {
        record.setValue("position", QVariant(row + 1));
    });
}

void BookModelTable::remove(const int position)
{
    removeRow(position);

    updateRecordsInRange(position, rowCount(), true, [](int row, QSqlRecord &record) {
        record.setValue("position", QVariant(row - 1));
    });
}

void BookModelTable::insert(const QString author, const QString title, const int totalPages, const int position)
{
    QSqlRecord r = record();
    r.setValue("author", QVariant::fromValue(author));
    r.setValue("title", QVariant::fromValue(title));
    r.setValue("tp", QVariant::fromValue(totalPages));
    r.setValue("position", QVariant::fromValue(position));

    if (!insertRecord(position, r)) { qDebug() << lastError(); }

    updateRecordsInRange(position + 1, rowCount(), true, [](int row, QSqlRecord &record) {
        record.setValue("position", QVariant(row));
    });
}

template<typename F> inline
void BookModelTable::updateRecordsInRange(const int start, const int end, const bool executeSubmitAll, F &&lambda)
{
    for (int row = start; row < end; row++) {
        auto r = record(row);
        lambda(row, r);
        setRecord(row, r);
    }

    if (executeSubmitAll) { submitAll(); }
}
