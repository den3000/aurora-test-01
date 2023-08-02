#ifndef ROOTCOORDINATOR_H
#define ROOTCOORDINATOR_H

#include <QObject>
#include <QtQuick>

#include "mainvm.h"
#include "aboutvm.h"
#include "bookslistqueryvm.h"
#include "bookslistmodelvm.h"
#include "bookquerytable.h"
#include "sqlitedb.h"

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
    QSharedPointer<BookQueryTable> bookQueryTable;

public slots:
    void showAboutPage();
    void showAboutPageWithInt(int value);
    void showAboutPageWithString(QString value);
    void showAboutPageWithModel(CustomModel value);
    void showSqliteCpp();
    void showSqliteQueryModelCpp();
};

#endif // ROOTCOORDINATOR_H
