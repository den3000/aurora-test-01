#include "mainvm.h"
#include <QDebug>

CustomModel::CustomModel(const QString name, const QString description, const int amount) {
    this->name = name;
    this->description = description;
    this->amount = amount;
};

MainVM::MainVM(QObject *parent) : QObject(parent)
{
    models
            << CustomModel("axolotl", "desc3", 30)
            << CustomModel("quokka" , "desc4", 40)
            << CustomModel("pitahui" , "desc5", 50);
}

MainVM::~MainVM() { qDebug() << "MainVM destroyed"; }

void MainVM::foo() const
{
    qDebug() << "foo invoked";
}

void MainVM::openAboutPageWithModel(int idx)
{
    emit gotoAboutPageWithModel(models[idx]);
}
