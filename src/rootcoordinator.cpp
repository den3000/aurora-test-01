#include "rootcoordinator.h"

RootCoordinator::RootCoordinator(QObject *parent) : QObject(parent)
{

}

QUrl RootCoordinator::appRootUrl()
{
    return Aurora::Application::pathTo(QStringLiteral("qml/DiAndNavExample.qml"));
}
