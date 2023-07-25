#include "rootcoordinator.h"

#include "smoozyutils.h"
#include "pagepaths.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
    bookTable = QSharedPointer<BookTable>(new BookTable());

    rootView = QSharedPointer<QQuickView>(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));

    // Use this to inject anything, including C++ models, into qml context
    // to make this model available directly in qml, probably something like
    // singletons or any other widely used objects is a good examplke for this
    // But this might create hard-coupling in code
    rootView->engine()->rootContext()->setContextProperty("cppContextProperty", "cppContextProperty value from c++");

    qmlCoordinatorInstance = QSharedPointer<QQuickItem>(Smoozy::findQuickViewChildByObjectName(rootView.data(), "rootCoordinatorQml"));
}

RootCoordinator::~RootCoordinator() { qDebug() << "RootCoordinator destroyed"; }

void RootCoordinator::start() {
    rootView->show();

    auto vm = new MainVM();
    QObject::connect(vm, &MainVM::gotoAboutPage, this, &RootCoordinator::showAboutPage);
    QObject::connect(vm, &MainVM::gotoAboutPageWithInt, this, &RootCoordinator::showAboutPageWithInt);
    QObject::connect(vm, &MainVM::gotoAboutPageWithString, this, &RootCoordinator::showAboutPageWithString);
    QObject::connect(vm, &MainVM::gotoAboutPageWithModel, this, &RootCoordinator::showAboutPageWithModel);
    QObject::connect(vm, &MainVM::gotoSqliteCpp, this, &RootCoordinator::showSqliteCpp);
    QObject::connect(vm, &MainVM::gotoSqliteQueryModelCpp, this, &RootCoordinator::showSqliteQueryModelCpp);

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::mainPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showAboutPage()
{
    auto vm = new AboutVM();
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::aboutPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showAboutPageWithInt(int value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, []() { qDebug() << "lambda bar"; });

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::aboutPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showAboutPageWithString(QString value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::aboutPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showAboutPageWithModel(CustomModel value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::aboutPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showSqliteCpp()
{
    auto vm = new SQLiteCppVM(bookTable.data(), nullptr);

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::sqliteCppPage), Smoozy::wrapInProperties(vm));
}

void RootCoordinator::showSqliteQueryModelCpp()
{
    auto vm = new SqlQueryVM(bookTable.data(), nullptr);

    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo(PagePaths::sqlQueryModelPage), Smoozy::wrapInProperties(vm));
}
