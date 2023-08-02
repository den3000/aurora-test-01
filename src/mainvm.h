#ifndef MAINVM_H
#define MAINVM_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "bookmodeltable.h"

class Foo1 {
public:
    explicit Foo1() { qDebug() << "Created"; };
    ~Foo1() { qDebug() << "Released"; };
};

class Foo2 : public QObject {
    Q_OBJECT
public:
    explicit Foo2(QObject *parent = nullptr) : QObject(parent) { qDebug() << "Created"; };
    ~Foo2() { qDebug() << "Released"; };
};


class CustomModel
{
public:
    explicit CustomModel(const QString name, const QString description, const int amount);

    QString name;
    QString description;
    int amount;
};

class MainVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit MainVM(QObject *parent = nullptr);
    ~MainVM();
    Q_INVOKABLE void foo() const;
    Q_INVOKABLE void openAboutPageWithModel(int idx);
    Q_INVOKABLE void memTest();

signals:
    void gotoAboutPage();
    void gotoAboutPageWithInt(int value);
    void gotoAboutPageWithString(QString value);
    void gotoAboutPageWithModel(CustomModel model);
    void gotoSqliteCpp();
    void gotoSqliteQueryModelCpp();

private:
    QList<CustomModel> models;

    BookModelTable * t1;
    BookModelTable * t2;
};

#endif // MAINVM_H
