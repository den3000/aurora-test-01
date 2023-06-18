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
    QSharedPointer<QQuickView> rootView;
    QSharedPointer<QQuickItem> qmlCoordinatorInstance;

public slots:
    void showAboutPage();
};

#endif // ROOTCOORDINATOR_H
