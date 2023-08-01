#include "sqlqueryvm.h"

SqlQueryVM::SqlQueryVM(BookQueryTable *bookTable, QObject *parent) : QObject(parent)
{
    bookQueryTable = bookTable;
    bookQueryTable->openDb();

    bookModelTable = bookQueryTable->tableModel(this);
}

SqlQueryVM::~SqlQueryVM()
{
    // TODO: This should be improved, probably BookQueryModel
    // should be explicitly responsible for all DB stuff
    delete bookModelTable;
    bookQueryTable->closeDb();
    qDebug() << "released";
}

BookModelTable* SqlQueryVM::tableModel()
{
    return bookModelTable;
}
