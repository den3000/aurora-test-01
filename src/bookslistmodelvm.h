#ifndef BOOKSLISTMODELVM_H
#define BOOKSLISTMODELVM_H

#include <QObject>

#include "sqlitedb.h"

class BooksListModelVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit BooksListModelVM(QObject *parent = nullptr) : QObject(parent) { };
    explicit BooksListModelVM(IBooksModelTableProvider * tableProvider, QObject *parent = nullptr);
    ~BooksListModelVM();

    Q_INVOKABLE BookModelTable* tableModel();
signals:

private: 
    IBooksModelTableProvider * tableProvider;
    BookModelTable *bookModelTable;
};

#endif // BOOKSLISTMODELVM_H
