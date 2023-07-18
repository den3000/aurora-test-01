#ifndef SQLITECPPVM_H
#define SQLITECPPVM_H

#include <QAbstractListModel>

class SQLiteCppVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SQLiteCppVM(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex&) const { return 10; }
    virtual QVariant data(const QModelIndex &index, int role) const;

signals:

};

#endif // SQLITECPPVM_H
