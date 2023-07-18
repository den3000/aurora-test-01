#include "sqlitecppvm.h"

#include <QString>

SQLiteCppVM::SQLiteCppVM(QObject *parent) : QAbstractListModel(parent)
{

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
    return QVariant::fromValue(QString("Row # %1").arg(index.row()));
}
