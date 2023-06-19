#include "aboutvm.h"
#include <QDebug>

AboutVM::AboutVM(QObject *parent) : QObject(parent)
{

}

AboutVM::AboutVM(int value)
{
    qDebug() << "int value " << value;
}

AboutVM::AboutVM(QString value)
{
    qDebug() << "string value " << value;
}

void AboutVM::foo() const
{
    qDebug() << "foo invoked ";
}
