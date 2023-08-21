#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "mainvm.h"
#include "aboutvm.h"
#include "bookslistqueryvm.h"
#include "bookslistmodelvm.h"
#include "sqlitedb.h"
#include "cpptoqmlmemorytestvm.h"
#include "cpprefsandptrstestvm.h"

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
    QSharedPointer<SQLiteDb> sqliteDb;

public slots:
    void showAboutPage();
    void showAboutPageWithInt(int value);
    void showAboutPageWithString(QString value);
    void showAboutPageWithModel(CustomModel value);
    void showSqliteCpp();
    void showSqliteQueryModelCpp();
    void showCppToQmlMemoryTest();
    void showCppRefsAndPtrsTest();
};

#endif // ROOTCOORDINATOR_H
