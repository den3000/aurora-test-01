#ifndef BOOKDAO_H
#define BOOKDAO_H

#include <QString>

struct BookDao
{
    explicit BookDao(const int id, const QString author, const QString title, const int totalPages, const int position){
        this->id = id;
        this->author = author;
        this->title = title;
        this->totalPages = totalPages;
        this->position = position;
    };

    int id;
    QString author;
    QString title;
    int totalPages;
    int position;
};

#endif // BOOKDAO_H
