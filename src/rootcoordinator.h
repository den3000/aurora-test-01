#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include "auroraapp.h"

#include <QObject>
#include <QtQuick>

class RootCoordinator : public QObject
{
    Q_OBJECT
public:
    explicit RootCoordinator(QObject *parent = nullptr);

    QUrl appRootUrl();
signals:

};

#endif // ROOTCOORDINATOR_H
