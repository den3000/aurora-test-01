#include "bookslistmodelvm.h"

BooksListModelVM::BooksListModelVM(IBooksModelTableProvider * tableProvider, QObject *parent) : QObject(parent)
{
    qDebug() << "Created";
    this->tableProvider = tableProvider;
    this->tableProvider->openDb();
    this->bookModelTable = this->tableProvider->booksModelTable();
}

BooksListModelVM::~BooksListModelVM()
{
    // TODO: This should be improved, probably BookQueryModel
    // should be explicitly responsible for all DB stuff
    delete bookModelTable;
//    bookQueryTable->closeDb();
    qDebug() << "Released";
}

BookModelTable* BooksListModelVM::tableModel()
{
    return bookModelTable;
}
