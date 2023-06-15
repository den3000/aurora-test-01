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

    //    QVariant navStack = view->rootObject()->property("pageStack");
    //    QObject * navStackObject = qvariant_cast<QObject *>(navStack);
    //    qDebug() << navStackObject->children();
    //    QQmlComponent * thatFackingStack = nullptr;
    //    for(const QObject * obj : navStackObject->children()) {
    //        if (qobject_cast<QQmlComponent*>(obj)) {
    ////            thatFackingStack = qobject_cast<QQmlComponent*>(obj);
    ////            break;
    //        }
    //    }
    //    qDebug() << thatFackingStack;

    QQmlComponent component(
                view->engine(),
                Aurora::Application::pathTo("qml/pages/MainPage.qml"),
                view->rootObject()
                );
//    component.setProperty("myStr", "MainPage_strFromCpp");

    QMap<QString, QVariant> properties;
    properties["myStr"] = "MainPage_strFromCpp";
    QMetaObject::invokeMethod(
                view->rootObject(),
                "push",
                Q_ARG(QVariant, QVariant::fromValue(&component)),
                Q_ARG(QVariant, QVariant::fromValue(properties))
                );

    return view;
}

