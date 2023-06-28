#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
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

    auto page = Smoozy::createPage(rootView.data(), "qml/pages/MainPage.qml");

    auto vm = new MainVM();
    QObject::connect(vm, &MainVM::gotoAboutPage, this, &RootCoordinator::showAboutPage);
    QObject::connect(vm, &MainVM::gotoAboutPageWithInt, this, &RootCoordinator::showAboutPageWithInt);
    QObject::connect(vm, &MainVM::gotoAboutPageWithString, this, &RootCoordinator::showAboutPageWithString);
    QObject::connect(vm, &MainVM::gotoAboutPageWithModel, this, &RootCoordinator::showAboutPageWithModel);

    QMap<QString, QVariant> properties;
    properties["viewModel"] = QVariant::fromValue<MainVM *>(vm);
    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo("qml/pages/MainPage.qml"), properties);
}

void RootCoordinator::showAboutPage()
{
    auto vm = new AboutVM();
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    QMap<QString, QVariant> properties;
    properties["viewModel"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo("qml/pages/AboutPage.qml"), properties);
}

void RootCoordinator::showAboutPageWithInt(int value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, []() { qDebug() << "lambda bar"; });

    QMap<QString, QVariant> properties;
    properties["viewModel"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo("qml/pages/AboutPage.qml"), properties);
}

void RootCoordinator::showAboutPageWithString(QString value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    QMap<QString, QVariant> properties;
    properties["viewModel"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo("qml/pages/AboutPage.qml"), properties);
}

void RootCoordinator::showAboutPageWithModel(CustomModel value)
{
    auto vm = new AboutVM(value);
    QObject::connect(vm, &AboutVM::bar, this, [=]() { qDebug() << "lambda bar"; });

    QMap<QString, QVariant> properties;
    properties["viewModel"] = QVariant::fromValue<AboutVM*>(vm);
    Smoozy::pushNamedPage(qmlCoordinatorInstance.data(), Aurora::Application::pathTo("qml/pages/AboutPage.qml"), properties);
}
