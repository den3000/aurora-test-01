#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

#include "smoozyutils.h"
#include "mainvm.h"
#include "aboutvm.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
    rootView = QSharedPointer<QQuickView>(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));

    auto qi = Smoozy::findQuickViewChildByObjectName(rootView.data(), "rootCoordinatorQml");
    qmlCoordinatorInstance = QSharedPointer<QQuickItem>(qi);
}

void RootCoordinator::start() {
    rootView->show();

    auto page = Smoozy::createPage(rootView.data(), "qml/pages/MainPage.qml");

    auto vm = new MainVM();
    QObject::connect(vm, &MainVM::gotoAboutPage, this, &RootCoordinator::showAboutPage);
    QObject::connect(vm, &MainVM::gotoAboutPageWithInt, this, &RootCoordinator::showAboutPageWithInt);

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<MainVM *>(vm);
    Smoozy::pushPage(qmlCoordinatorInstance.data(), page, properties);
}

void RootCoordinator::showAboutPage()
{
    auto page = Smoozy::createPage(rootView.data(), "qml/pages/AboutPage.qml");

    auto vm = new AboutVM();
    QObject::connect(vm, &AboutVM::bar, this, [=]() {
        qDebug() << "lambda bar";
    });

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushPage(qmlCoordinatorInstance.data(), page, properties);
}

void RootCoordinator::showAboutPageWithInt(int value)
{
    auto page = Smoozy::createPage(rootView.data(), "qml/pages/AboutPage.qml");

    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, [=]() {
        qDebug() << "lambda bar";
    });

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushPage(qmlCoordinatorInstance.data(), page, properties);
}

