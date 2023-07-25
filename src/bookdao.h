#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QtSql>

#include "bookmodel.h"

class BookDao
{
public:
    BookDao();
    ~BookDao();
    
    void openDb();
    QList<BookModel> getAllBooks();
    int insert(BookModel book);
    void remove(const int id, const int position);
    void moveToTop(const int id, const int position);
    void update(const int id, const QString author, const QString title, const int totalPages);
    void closeDb();
};

#endif // BOOKDAO_H
