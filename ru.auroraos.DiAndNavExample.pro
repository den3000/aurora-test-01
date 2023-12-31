################################################################################
##
## Copyright (C) 2022 ru.auroraos
## 
## This file is part of the My Aurora OS Application project.
##
## Redistribution and use in source and binary forms,
## with or without modification, are permitted provided
## that the following conditions are met:
##
## * Redistributions of source code must retain the above copyright notice,
##   this list of conditions and the following disclaimer.
## * Redistributions in binary form must reproduce the above copyright notice,
##   this list of conditions and the following disclaimer
##   in the documentation and/or other materials provided with the distribution.
## * Neither the name of the copyright holder nor the names of its contributors
##   may be used to endorse or promote products derived from this software
##   without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
## THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
## FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
## IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
## FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
## OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
## LOSS OF USE, DATA, OR PROFITS;
## OR BUSINESS INTERRUPTION)
## HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
## WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
## (INCLUDING NEGLIGENCE OR OTHERWISE)
## ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
## EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
################################################################################

TARGET = ru.auroraos.DiAndNavExample

QT += sql

CONFIG += \
    auroraapp \
    c++1z

PKGCONFIG += \

SOURCES += \
    src/cpprefsandptrstestvm.cpp \
    src/cpptoqmlmemorytestabstractlistmodel.cpp \
    src/bookmodeltable.cpp \
    src/bookquerytable.cpp \
    src/aboutvm.cpp \
    src/bookslistmodelvm.cpp \
    src/bookslistqueryvm.cpp \
    src/cpptoqmlmemorytestmodel.cpp \
    src/cpptoqmlmemorytestvm.cpp \
    src/mainvm.cpp \
    src/main.cpp \
    src/rootcoordinator.cpp \
    src/sqlitedb.cpp

HEADERS += \
    src/cpprefsandptrstestvm.h \
    src/cpptoqmlmemorytestabstractlistmodel.h \
    src/bookdao.h \
    src/bookmodeltable.h \
    src/bookquerytable.h \
    src/aboutvm.h \
    src/bookslistmodelvm.h \
    src/bookslistqueryvm.h \
    src/cpptoqmlmemorytestmodel.h \
    src/cpptoqmlmemorytestvm.h \
    src/customcppclasses.h \
    src/idbprovider.h \
    src/mainvm.h \
    src/pagepaths.h \
    src/rootcoordinator.h \
    src/smoozyutils.h \
    src/sqlitedb.h

DISTFILES += \
    qml/RootCoordinatorQml.qml \
    qml/pages/BooksListModelPage.qml \
    qml/pages/BooksListQmlPage.qml \
    qml/pages/BooksListQmlTable.qml \
    qml/pages/BooksListQueryPage.qml \
    qml/pages/CppRefsAndPtrsTestPage.qml \
    qml/pages/CppToQmlMemoryTestPage.qml \
    rpm/ru.auroraos.DiAndNavExample.spec \
    AUTHORS.md \
    CODE_OF_CONDUCT.md \
    CONTRIBUTING.md \
    LICENSE.BSD-3-CLAUSE.md \
    README.md \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.auroraos.DiAndNavExample.ts \
    translations/ru.auroraos.DiAndNavExample-ru.ts \
