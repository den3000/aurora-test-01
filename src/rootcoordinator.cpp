#include "rootcoordinator.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{

}

QSharedPointer<QQuickView> RootCoordinator::appRoot() {
    QSharedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/DiAndNavExample.qml")));
    view->show();
    return view;
}

