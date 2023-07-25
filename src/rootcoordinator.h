#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "mainvm.h"
#include "aboutvm.h"
#include "sqlitecppvm.h"
#include "bookdao.h"

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
    QSharedPointer<BookDao> bookDao;

public slots:
    void showAboutPage();
    void showAboutPageWithInt(int value);
    void showAboutPageWithString(QString value);
    void showAboutPageWithModel(CustomModel value);
    void showSqliteCpp();
};

#endif // ROOTCOORDINATOR_H
