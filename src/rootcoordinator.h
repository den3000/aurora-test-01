#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "mainvm.h"
#include "aboutvm.h"

class RootCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit RootCoordinator(QObject *parent = nullptr);
    ~RootCoordinator();

    void start();

private:
    QSharedPointer<QQuickView> rootView;
    QSharedPointer<QQuickItem> qmlCoordinatorInstance;

public slots:
    void showAboutPage();
    void showAboutPageWithInt(int value);
    void showAboutPageWithString(QString value);
    void showAboutPageWithModel(CustomModel value);
};

#endif // ROOTCOORDINATOR_H
