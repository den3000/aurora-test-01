#include "sqlqueryvm.h"

SqlQueryVM::SqlQueryVM(BookDao *bookDao, QObject *parent)
{
    dao = bookDao;
}

SqlQueryVM::~SqlQueryVM()
{
    dao->closeDb();
}
