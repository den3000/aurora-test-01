#ifndef EASYUTILS_H
#define EASYUTILS_H

#include <QObject>
#include <QtQuick>

#include <auroraapp.h>

namespace Easy
{
    inline QQuickItem * findQuickViewChildByObjectName(QQuickView * quickView, const char * objectName) {
        return quickView->rootObject()->findChild<QQuickItem *>(objectName);
    }

    inline QQuickItem * findQuickViewPropertyByPropertyName(QQuickView * quickView, const char * propertyName){
        QVariant propertyVariant = quickView->rootObject()->property(propertyName);
        QObject * propertyObject = qvariant_cast<QObject *>(propertyVariant);
        return qobject_cast<QQuickItem *>(propertyObject);
    }

    inline QQmlComponent * createPage(QQuickView * rootView, const char * pageName){
        return new QQmlComponent(
                    rootView->engine(),
                    Aurora::Application::pathTo(pageName),
                    rootView->rootObject()
                    );
    }

    inline bool pushPage(QQuickItem * qmlCoordinatorInstance, QQmlComponent * page, QMap<QString, QVariant> properties){
        return QMetaObject::invokeMethod(
                    qmlCoordinatorInstance,
                    "push",
                    Q_ARG(QVariant, QVariant::fromValue(page)),
                    Q_ARG(QVariant, QVariant::fromValue(properties))
                    );;
    }
}

#endif // EASYUTILS_H
