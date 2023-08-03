#include "cpptoqmlmemorytestvm.h"

CppToQmlMemoryTestVM::CppToQmlMemoryTestVM(QObject *parent) : QObject(parent)
{
    qDebug() << "Created";
}

CppToQmlMemoryTestVM::~CppToQmlMemoryTestVM()
{
    qDebug() << "Released";
}

CppToQmlMemoryTestModel::CppToQmlMemoryTestModel(QObject *parent)
{
    tag = "default";
    qDebug() << tag << " created";
}

CppToQmlMemoryTestModel::CppToQmlMemoryTestModel(QString tag, QObject *parent)
{
    this->tag = tag;

    qDebug() << tag << " created";
}

CppToQmlMemoryTestModel::~CppToQmlMemoryTestModel()
{
    qDebug() << tag << " released";
}
