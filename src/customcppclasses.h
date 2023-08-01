#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "mainvm.h"
#include "aboutvm.h"
#include "bookslistqueryvm.h"
#include "sqlqueryvm.h"
#include "bookmodeltable.h"

class CustomCppClasses {
public:
    static void registerModuleInQml() {
        qmlRegisterType<MainVM>("CustomCppClasses.Module", 1, 0, "MainVM");
        qmlRegisterType<AboutVM>("CustomCppClasses.Module", 1, 0, "AboutVM");
        qmlRegisterType<BooksListQueryVM>("CustomCppClasses.Module", 1, 0, "BooksListQueryVM");
        qmlRegisterType<SqlQueryVM>("CustomCppClasses.Module", 1, 0, "SqlQueryVM");
        qmlRegisterType<BookModelTable>("CustomCppClasses.Module", 1, 0, "BookModelTable");
    }
};

#endif // CUSTOMCPPCLASSES_H
