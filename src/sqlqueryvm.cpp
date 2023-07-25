#include "sqlqueryvm.h"

SqlQueryVM::SqlQueryVM(BookTable *bookTable, QObject *parent)
{
    dao = bookTable;
}

SqlQueryVM::~SqlQueryVM()
{
    dao->closeDb();
}
