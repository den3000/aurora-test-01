#include "bookdao.h"

BookDao::BookDao()
{

}

BookModel::BookModel(const int id, const QString author, const QString title, const int totalPages, const int position) {
    this->id = id;
    this->author = author;
    this->title = title;
    this->totalPages = totalPages;
    this->position = position;
}
