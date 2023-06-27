#ifndef ABOUTVM_H
#define ABOUTVM_H

#include <QObject>

#include "mainvm.h"

class AboutVM : public QObject
{
    Q_OBJECT

public:
    explicit AboutVM(QObject *parent = nullptr);
    explicit AboutVM(int value);
    explicit AboutVM(QString value);
    explicit AboutVM(CustomModel value);
    ~AboutVM();

    Q_INVOKABLE void foo() const;
    Q_INVOKABLE void updateParent(QObject * value);

signals:
    void bar();
};

#endif // ABOUTVM_H
