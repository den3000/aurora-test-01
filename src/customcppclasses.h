#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "mainvm.h"
#include "aboutvm.h"
#include "bookslistqueryvm.h"
#include "bookslistmodelvm.h"
#include "bookmodeltable.h"
#include "cpptoqmlmemorytestvm.h"
#include "cpprefsandptrstestvm.h"

class CustomCppClasses {
public:
    static void registerModuleInQml() {
        qmlRegisterType<MainVM>("CustomCppClasses.Module", 1, 0, "MainVM");
        qmlRegisterType<AboutVM>("CustomCppClasses.Module", 1, 0, "AboutVM");
        qmlRegisterType<BooksListQueryVM>("CustomCppClasses.Module", 1, 0, "BooksListQueryVM");
        qmlRegisterType<BooksListModelVM>("CustomCppClasses.Module", 1, 0, "BooksListModelVM");
        qmlRegisterType<BookModelTable>("CustomCppClasses.Module", 1, 0, "BookModelTable");

        qmlRegisterType<CppToQmlMemoryTestVM>("CustomCppClasses.Module", 1, 0, "CppToQmlMemoryTestVM");
        qmlRegisterType<CppToQmlMemoryTestModel>("CustomCppClasses.Module", 1, 0, "CppToQmlMemoryTestModel");
        qmlRegisterType<CppToQmlMemoryTestAbstractListModel>("CustomCppClasses.Module", 1, 0, "CppToQmlMemoryTestAbstractListModel");
        qmlRegisterType<CppRefsAndPtrsTestVM>("CustomCppClasses.Module", 1, 0, "CppRefsAndPtrsTestVM");
    }
};

#endif // CUSTOMCPPCLASSES_H
