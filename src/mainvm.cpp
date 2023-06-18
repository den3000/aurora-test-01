#include "mainvm.h"
#include <QDebug>

MainVM::MainVM(QObject *parent) : QObject(parent)
{

}

void MainVM::foo() const
{
    qDebug() << "foo invoked";
}
