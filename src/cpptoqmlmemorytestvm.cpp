#include "cpptoqmlmemorytestvm.h"

CppToQmlMemoryTestVM::CppToQmlMemoryTestVM(QObject *parent) : QObject(parent)
{
    qDebug() << "Created";
    modelNoParent = new CppToQmlMemoryTestModel(QString("modelNoParent"), nullptr);
    modelWithParent = new CppToQmlMemoryTestModel(QString("modelWithParent"), this);
    spModelNoParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelNoParent", nullptr));
    spModelWithParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelWithParent", this));
}

CppToQmlMemoryTestVM::~CppToQmlMemoryTestVM()
{
    qDebug() << "Released";
}

CppToQmlMemoryTestModel *CppToQmlMemoryTestVM::getModelNoParent()
{
    return modelNoParent;
}

CppToQmlMemoryTestModel *CppToQmlMemoryTestVM::getModelWithParent()
{
    return modelWithParent;
}

CppToQmlMemoryTestModel *CppToQmlMemoryTestVM::getModelNoParentFromSp()
{
    return spModelNoParent.data();
}

CppToQmlMemoryTestModel *CppToQmlMemoryTestVM::getModelWithParentFromSp()
{
    return spModelWithParent.data();
}

CppToQmlMemoryTestModel::CppToQmlMemoryTestModel(QObject *parent) : QObject(parent)
{
    tag = "default";
    qDebug() << tag << " created";
}

CppToQmlMemoryTestModel::CppToQmlMemoryTestModel(QString tag, QObject *parent) : QObject(parent)
{
    this->tag = tag;
    qDebug() << tag << " created";
}

CppToQmlMemoryTestModel::~CppToQmlMemoryTestModel()
{
    qDebug() << tag << " released";
}

void CppToQmlMemoryTestModel::foo()
{
    qDebug() << tag;
}
