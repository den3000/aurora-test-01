#ifndef SQLQUERYVM_H
#define SQLQUERYVM_H

#include <QObject>

#include "bookquerytable.h"

class SqlQueryVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SqlQueryVM(QObject *parent = nullptr) : QObject(parent) { };
    explicit SqlQueryVM(BookTable * bookTable, QObject *parent = nullptr);
    ~SqlQueryVM();

    Q_INVOKABLE BookQueryModel* queryModel();
signals:

private: 
    BookTable *dao;
    BookQueryModel *qm;
};

#endif // SQLQUERYVM_H
