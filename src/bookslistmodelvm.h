#ifndef BOOKSLISTMODELVM_H
#define BOOKSLISTMODELVM_H

#include <QObject>

#include "bookquerytable.h"

class SqlQueryVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SqlQueryVM(QObject *parent = nullptr) : QObject(parent) { };
    explicit SqlQueryVM(BookQueryTable * bookTable, QObject *parent = nullptr);
    ~SqlQueryVM();

    Q_INVOKABLE BookModelTable* tableModel();
signals:

private: 
    BookQueryTable *bookQueryTable;
    BookModelTable *bookModelTable;
};

#endif // BOOKSLISTMODELVM_H
