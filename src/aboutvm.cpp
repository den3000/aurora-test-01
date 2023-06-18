#include "aboutvm.h"
#include <QDebug>

AboutVM::AboutVM(QObject *parent) : QObject(parent)
{

}

void AboutVM::foo() const
{
    qDebug() << "foo invoked ";
}
