#ifndef BOOKQUERYTABLE_H
#define BOOKQUERYTABLE_H

#include <QtSql>

#include "bookdao.h"
#include "bookquerymodel.h"

class BookTable
{
public:
    BookTable();
    ~BookTable();
    
    void openDb();
    QList<BookDao> getAllBooks();
    int insert(BookDao book);
    void remove(const int id, const int position);
    void moveToTop(const int id, const int position);
    void update(const int id, const QString author, const QString title, const int totalPages);
    void closeDb();
    BookQueryModel* queryModel(QObject * parent);
};

#endif // BOOKQUERYTABLE_H
