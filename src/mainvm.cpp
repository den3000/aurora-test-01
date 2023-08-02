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

void MainVM::memTest()
{
    auto f1 = new Foo1();
    auto f21 = new Foo2();
    auto f22 = new Foo2(this);

    delete f1;
    delete f21;

    t1 = new BookModelTable();
    t2 = new BookModelTable(this);

}
