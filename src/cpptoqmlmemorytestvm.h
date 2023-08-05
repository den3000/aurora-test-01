#ifndef CPPTOQMLMEMORYTESTVM_H
#define CPPTOQMLMEMORYTESTVM_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QSharedPointer>

/*
    declaration in header, implementation in source
        vs
    declaration and implementation in header

    I will be using both in header here as an example, but in general
    this is a separate topic with some pros and cons that should be
    considered separately
*/

#include "cpptoqmlmemorytestmodel.h"
#include "cpptoqmlmemorytestabstractlistmodel.h"

class CppToQmlMemoryTestVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

    CppToQmlMemoryTestModel * modelNoParent;
    CppToQmlMemoryTestModel * modelWithParent;
    QSharedPointer<CppToQmlMemoryTestModel> spModelNoParent;
    QSharedPointer<CppToQmlMemoryTestModel> spModelWithParent;
    
    Q_PROPERTY(CppToQmlMemoryTestModel * modelNoParent READ getModelNoParent)
    Q_PROPERTY(CppToQmlMemoryTestModel * modelWithParent READ getModelWithParent)
    Q_PROPERTY(CppToQmlMemoryTestModel * spModelNoParent READ getModelNoParentFromSp)
    Q_PROPERTY(CppToQmlMemoryTestModel * spModelWithParent READ getModelWithParentFromSp)

public:

    explicit CppToQmlMemoryTestVM(QObject *parent = nullptr) : QObject(parent) {
        qDebug() << "Created";
        modelNoParent = new CppToQmlMemoryTestModel("modelNoParent", nullptr);
        modelWithParent = new CppToQmlMemoryTestModel("modelWithParent", this);
        spModelNoParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelNoParent", nullptr));
        spModelWithParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelWithParent", this));
    }
    
    ~CppToQmlMemoryTestVM() { qDebug() << "Released"; };

    CppToQmlMemoryTestModel * getModelNoParent() { return modelNoParent; };
    CppToQmlMemoryTestModel * getModelWithParent() { return modelWithParent; };
    CppToQmlMemoryTestModel * getModelNoParentFromSp() { return spModelNoParent.data(); };
    CppToQmlMemoryTestModel * getModelWithParentFromSp() { return spModelWithParent.data(); };

signals:

private:
};

// TODO: we also need some abstract item model
// or table model example for for demonstration
// of mem menagement with lists

#endif // CPPTOQMLMEMORYTESTVM_H
