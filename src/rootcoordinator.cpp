#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

#include "easyutils.h"
#include "mainvm.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
    rootView = QSharedPointer<QQuickView>(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));

    auto qi = Easy::findQuickViewChildByObjectName(rootView.data(), "rootCoordinatorQml");
    qmlCoordinatorInstance = QSharedPointer<QQuickItem>(qi);
}

void RootCoordinator::start() {
    rootView->show();

    auto mainPage = Easy::createPage(rootView.data(), "qml/pages/MainPage.qml");

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<MainVM *>(new MainVM());

    Easy::pushPage(qmlCoordinatorInstance.data(), mainPage, properties);
}

