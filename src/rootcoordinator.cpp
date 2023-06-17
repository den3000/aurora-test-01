#include "rootcoordinator.h"

#include <QString>
#include <QDebug>

#include <QtQuick>

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{

}

QSharedPointer<QQuickView> RootCoordinator::appRoot() {
    QSharedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo("qml/DiAndNavExample.qml"));
    view->rootObject()->setProperty("myStr", "AppWindow_strFromCpp");
    view->show();

    QQmlComponent mainPage(
                view->engine(),
                Aurora::Application::pathTo("qml/pages/MainPage.qml"),
                view->rootObject()
                );

    QMap<QString, QVariant> properties;
    properties["myStr"] = "MainPage_strFromCpp";

    QQuickItem * rootCoordinator = findQuickViewChildByObjectName(view.data(), "rootCoordinatorQml");
    QMetaObject::invokeMethod(
                rootCoordinator,
                "push",
                Q_ARG(QVariant, QVariant::fromValue(&mainPage)),
                Q_ARG(QVariant, QVariant::fromValue(properties))
                );

    return view;
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


