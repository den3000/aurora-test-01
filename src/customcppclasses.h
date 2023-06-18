#ifndef CUSTOMCPPCLASSES_H
#define CUSTOMCPPCLASSES_H

#include "QtQuick"
#include "mainvm.h"

class CustomCppClasses {
public:
    static void registerModuleInQml() {
        qmlRegisterType<MainVM>("CustomCppClasses.Module", 1, 0, "MainVM");
    }
};

#endif // CUSTOMCPPCLASSES_H
