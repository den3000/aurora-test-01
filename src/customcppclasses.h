#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "mainvm.h"
#include "aboutvm.h"
#include "sqlitecppvm.h"
#include "sqlqueryvm.h"

class CustomCppClasses {
public:
    static void registerModuleInQml() {
        qmlRegisterType<MainVM>("CustomCppClasses.Module", 1, 0, "MainVM");
        qmlRegisterType<AboutVM>("CustomCppClasses.Module", 1, 0, "AboutVM");
        qmlRegisterType<SQLiteCppVM>("CustomCppClasses.Module", 1, 0, "SqliteCppVM");
        qmlRegisterType<SqlQueryVM>("CustomCppClasses.Module", 1, 0, "SqlQueryVM");
    }
};

#endif // CUSTOMCPPCLASSES_H
