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

    QSharedPointer<QQuickView> appRoot();

private:
    QQuickItem * findQuickViewChildByObjectName(QQuickView * quickView, const char * objectName);
    QQuickItem * findQuickViewPropertyByPropertyName(QQuickView * quickView, const char * propertyName);

signals:
};

#endif // ROOTCOORDINATOR_H
