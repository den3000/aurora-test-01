#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include <auroraapp.h>

#include <QObject>
#include <QtQuick>

class RootCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit RootCoordinator(QObject *parent = nullptr);

    void start();

private:
    QQuickItem * findQuickViewChildByObjectName(QQuickView * quickView, const char * objectName);
    QQuickItem * findQuickViewPropertyByPropertyName(QQuickView * quickView, const char * propertyName);

    QSharedPointer<QQuickView> rootView;
    QSharedPointer<QQuickItem> qmlCoordinatorInstance;

signals:
};

#endif // ROOTCOORDINATOR_H
