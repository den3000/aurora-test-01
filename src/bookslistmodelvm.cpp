#include "bookslistmodelvm.h"

BooksListModelVM::BooksListModelVM(BookQueryTable *bookTable, QObject *parent) : QObject(parent)
{
    bookQueryTable = bookTable;
    bookQueryTable->openDb();

    bookModelTable = bookQueryTable->tableModel(this);
}

BooksListModelVM::~BooksListModelVM()
{
    // TODO: This should be improved, probably BookQueryModel
    // should be explicitly responsible for all DB stuff
    delete bookModelTable;
    bookQueryTable->closeDb();
    qDebug() << "released";
}

BookModelTable* BooksListModelVM::tableModel()
{
    return bookModelTable;
}
