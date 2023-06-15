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

    view->rootObject()->setProperty("myStr", "ApplicationWindow_strFromCpp");
    QVariant urlMainPage = Aurora::Application::pathTo("qml/pages/MainPage.qml");
    QMetaObject::invokeMethod(view->rootObject(), "push",
            Q_ARG(QVariant, urlMainPage));

    view->show();


//    QVariant navStack = view->rootObject()->property("pageStack");
//    qDebug() << navStack;

    return view;
}

