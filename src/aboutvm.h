#ifndef ABOUTVM_H
#define ABOUTVM_H

#include <QObject>

class AboutVM : public QObject
{
    Q_OBJECT
public:
    explicit AboutVM(QObject *parent = nullptr);

    Q_INVOKABLE void foo() const;

signals:
    void bar();
};

#endif // ABOUTVM_H
