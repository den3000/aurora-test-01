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

AboutVM::AboutVM(CustomModel value)
{
    qDebug()
            << "model name: " << value.name
            << " model desc: " << value.description
            << " model amount: " << value.amount;

}

AboutVM::~AboutVM() { qDebug() << "AboutVM destroyed"; }

void AboutVM::foo() const
{
    qDebug() << "foo invoked ";
}

void AboutVM::updateParent(QObject * value)
{
    setParent(value);
}
