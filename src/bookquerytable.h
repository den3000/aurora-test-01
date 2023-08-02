#ifndef BOOKQUERYTABLE_H
#define BOOKQUERYTABLE_H

#include <QtSql>

#include "bookdao.h"
#include "bookmodeltable.h"

class BookQueryTable;

class IBooksQueryTableProvider: public IDbProvider {
public:
    virtual BookQueryTable * booksQueryTable() = 0;
};

class BookQueryTable
{
public:
    BookQueryTable();
    ~BookQueryTable();
    
    QList<BookDao> getAllBooks();
    int insert(BookDao book);
    void remove(const int id, const int position);
    void moveToTop(const int id, const int position);
    void update(const int id, const QString author, const QString title, const int totalPages);
    BookModelTable* tableModel(QObject * parent);
};

#endif // BOOKQUERYTABLE_H
