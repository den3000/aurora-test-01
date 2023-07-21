#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QtSql>

struct BookModel;

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
