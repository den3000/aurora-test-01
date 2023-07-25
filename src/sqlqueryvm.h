#ifndef SQLQUERYVM_H
#define SQLQUERYVM_H

#include <QObject>

#include "bookdao.h"

class SqlQueryVM : public QObject
{
    Q_OBJECT
public:
    explicit SqlQueryVM(QObject *parent = nullptr) : QObject(parent) { };
    explicit SqlQueryVM(BookDao * bookDao, QObject *parent = nullptr);
    ~SqlQueryVM();

signals:

private: 
    BookDao *dao;
};

#endif // SQLQUERYVM_H
