#include "sqlqueryvm.h"

SqlQueryVM::SqlQueryVM(BookQueryTable *bookTable, QObject *parent) : QObject(parent)
{
    dao = bookTable;
    dao->openDb();

    qm = dao->queryModel(this);
}

SqlQueryVM::~SqlQueryVM()
{
    // TODO: This should be improved, probably BookQueryModel
    // should be explicitly responsible for all DB stuff
    delete qm;
    dao->closeDb();
    qDebug() << "released";
}

BookQueryModel* SqlQueryVM::queryModel()
{
    return qm;
}
