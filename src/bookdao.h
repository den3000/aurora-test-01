#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QtSql>

struct BookModel;

class BookDao
{
public:
    BookDao();
};

struct BookModel
{
    explicit BookModel(const int id, const QString author, const QString title, const int totalPages, const int position);

    int id;
    QString author;
    QString title;
    int totalPages;
    int position;
};

#endif // BOOKDAO_H
