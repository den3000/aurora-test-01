#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QtSql>

struct BookModel;

class BookDao
{
public:
    BookDao();

    void openDb();
    QList<BookModel> getAllBooks();
    void insert(BookModel book);
    void insert(const QString author, const QString title, const int totalPages, const int position);
    void remove(const int id, const int position);
    void moveToTop(const int id, const int position);
    void update(const int id, const QString author, const QString title, const int totalPages, const int position);
    void closeDb();
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
