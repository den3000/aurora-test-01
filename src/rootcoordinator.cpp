#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

#include "mainvm.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{
    rootView = QSharedPointer<QQuickView>(Aurora::Application::createView());
    rootView->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));

    qmlCoordinatorInstance = QSharedPointer<QQuickItem>(findQuickViewChildByObjectName(rootView.data(), "rootCoordinatorQml"));
}

void RootCoordinator::start() {

    rootView->show();

    QQmlComponent mainPage(
                rootView->engine(),
                Aurora::Application::pathTo("qml/pages/MainPage.qml"),
                rootView->rootObject()
                );

    QMap<QString, QVariant> properties;
    properties["model"] = QVariant::fromValue<MainVM *>(new MainVM());

    QMetaObject::invokeMethod(
                qmlCoordinatorInstance.data(),
                "push",
                Q_ARG(QVariant, QVariant::fromValue(&mainPage)),
                Q_ARG(QVariant, QVariant::fromValue(properties))
                );
}

QQuickItem *RootCoordinator::findQuickViewChildByObjectName(QQuickView *quickView, const char *objectName)
{
    return quickView->rootObject()->findChild<QQuickItem *>(objectName);
}

QQuickItem *RootCoordinator::findQuickViewPropertyByPropertyName(QQuickView *quickView, const char *propertyName)
{
    QVariant propertyVariant = quickView->rootObject()->property(propertyName);
    QObject * propertyObject = qvariant_cast<QObject *>(propertyVariant);
    return qobject_cast<QQuickItem *>(propertyObject);
}


