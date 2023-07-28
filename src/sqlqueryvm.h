#ifndef SQLQUERYVM_H
#define SQLQUERYVM_H

#include <QObject>

#include "booktable.h"

class SqlQueryVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SqlQueryVM(QObject *parent = nullptr) : QObject(parent) { };
    explicit SqlQueryVM(BookTable * bookTable, QObject *parent = nullptr);
    ~SqlQueryVM();

signals:

private: 
    BookTable *dao;
};

#endif // SQLQUERYVM_H
