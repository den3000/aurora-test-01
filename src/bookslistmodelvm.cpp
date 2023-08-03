#include "bookslistmodelvm.h"

BooksListModelVM::BooksListModelVM(IBooksModelTableProvider * tableProvider, QObject *parent) : QObject(parent)
{
    qDebug() << "Created";
    this->tableProvider = tableProvider;
    this->tableProvider->openDb();

    // 1. We assigning parent here because bookModelTable is a QObject
    // child and will be exposed to QMl. QObject without a parent is
    // immedialy released when exposed to qml, unless it is assigned
    // to some qml property
    // this->bookModelTable = this->tableProvider->booksModelTable(this);

    // 2. We can set parent to nullptr, but then this need to be assigned
    // to designated property in qml in `onViewModelChanged` or right after
    // first access, in other way it will be released immediately 
    this->bookModelTable = this->tableProvider->booksModelTable(nullptr);

    // Scenario 2 is used as a demo because object is saved on qml side
    // in designated property
}

BooksListModelVM::~BooksListModelVM()
{
    // TODO: This should be improved, probably BookQueryModel
    // should be explicitly responsible for all DB stuff
    delete bookModelTable;
    tableProvider->closeDb();
    qDebug() << "Released";
}

BookModelTable* BooksListModelVM::tableModel()
{
    return bookModelTable;
}
