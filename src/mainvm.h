#ifndef MAINVM_H
#define MAINVM_H

#include <QObject>

class MainVM : public QObject
{
    Q_OBJECT
public:
    explicit MainVM(QObject *parent = nullptr);

    Q_INVOKABLE void foo() const;
signals:

};

#endif // MAINVM_H
