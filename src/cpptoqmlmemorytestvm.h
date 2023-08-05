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

public:
    explicit CppToQmlMemoryTestVM(QObject *parent = nullptr) : QObject(parent) {
        qDebug() << "Created";
        modelNoParent = new CppToQmlMemoryTestModel("modelNoParent", nullptr);
        modelWithParent = new CppToQmlMemoryTestModel("modelWithParent", this);
        spModelNoParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelNoParent", nullptr));
        spModelWithParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelWithParent", this));
    }
    
    ~CppToQmlMemoryTestVM() { qDebug() << "Released"; };

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelNoParent() {
        return modelNoParent;
    };

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelWithParent() {
        return modelWithParent;
    };

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelNoParentFromSp() {
        return spModelNoParent.data();
    };

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelWithParentFromSp() {
        return spModelWithParent.data();
    };

signals:

private:
    CppToQmlMemoryTestModel * modelNoParent;
    CppToQmlMemoryTestModel * modelWithParent;

    QSharedPointer<CppToQmlMemoryTestModel> spModelNoParent;
    QSharedPointer<CppToQmlMemoryTestModel> spModelWithParent;
};

// TODO: we also need some abstract item model
// or table model example for for demonstration
// of mem menagement with lists

#endif // CPPTOQMLMEMORYTESTVM_H
