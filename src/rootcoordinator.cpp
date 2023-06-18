#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

#include "smoozyutils.h"
#include "mainvm.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
    rootView = QSharedPointer<QQuickView>(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));

    auto qi = Smoozy::findQuickViewChildByObjectName(rootView.data(), "rootCoordinatorQml");
    qmlCoordinatorInstance = QSharedPointer<QQuickItem>(qi);
}

void RootCoordinator::start() {
    rootView->show();

    auto mainPage = Smoozy::createPage(rootView.data(), "qml/pages/MainPage.qml");

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<MainVM *>(new MainVM());

    Smoozy::pushPage(qmlCoordinatorInstance.data(), mainPage, properties);
}

