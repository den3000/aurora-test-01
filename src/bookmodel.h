#ifndef BOOKMODEL_H
#define BOOKMODEL_H

#include <QString>

struct BookModel
{
    explicit BookModel(const int id, const QString author, const QString title, const int totalPages, const int position){
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

#endif // BOOKMODEL_H
