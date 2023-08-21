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

    CppToQmlMemoryTestAbstractListModel * alModelNoParent;
    CppToQmlMemoryTestAbstractListModel * alModelWithParent;
    QSharedPointer<CppToQmlMemoryTestAbstractListModel> spAlModelNoParent;
    QSharedPointer<CppToQmlMemoryTestAbstractListModel> spAlModelWithParent;
    
    Q_PROPERTY(CppToQmlMemoryTestAbstractListModel * alModelNoParent READ getAlModelNoParent NOTIFY alModelNoParentChanged)
    Q_PROPERTY(CppToQmlMemoryTestAbstractListModel * alModelWithParent READ getAlModelWithParent NOTIFY alModelWithParentChanged)
    Q_PROPERTY(CppToQmlMemoryTestAbstractListModel * spAlModelNoParent READ getAlModelNoParentFromSp NOTIFY spAlModelNoParentChanged)
    Q_PROPERTY(CppToQmlMemoryTestAbstractListModel * spAlModelWithParent READ getAlModelWithParentFromSp NOTIFY spAlModelWithParentChanged)

public:

    explicit CppToQmlMemoryTestVM(QObject *parent = nullptr) : QObject(parent) {
        qDebug() << "Created";
        modelNoParent = new CppToQmlMemoryTestModel("modelNoParent", nullptr);
        modelWithParent = new CppToQmlMemoryTestModel("modelWithParent", this);
        spModelNoParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelNoParent", nullptr));
        spModelWithParent = QSharedPointer<CppToQmlMemoryTestModel>(new CppToQmlMemoryTestModel("spModelWithParent", this));

        alModelNoParent = new CppToQmlMemoryTestAbstractListModel("alModelNoParent", nullptr);
        alModelWithParent = new CppToQmlMemoryTestAbstractListModel("alModelWithParent", this);
        spAlModelNoParent = QSharedPointer<CppToQmlMemoryTestAbstractListModel>(new CppToQmlMemoryTestAbstractListModel("spAlModelNoParent", nullptr));
        spAlModelWithParent = QSharedPointer<CppToQmlMemoryTestAbstractListModel>(new CppToQmlMemoryTestAbstractListModel("spAlModelWithParent", this));
    }
    
    ~CppToQmlMemoryTestVM() { qDebug() << "Released"; };

    CppToQmlMemoryTestModel * getModelNoParent() { return modelNoParent; };
    CppToQmlMemoryTestModel * getModelWithParent() { return modelWithParent; };
    CppToQmlMemoryTestModel * getModelNoParentFromSp() { return spModelNoParent.data(); };
    CppToQmlMemoryTestModel * getModelWithParentFromSp() { return spModelWithParent.data(); };

    Q_INVOKABLE CppToQmlMemoryTestAbstractListModel * getAlModelNoParent() { return alModelNoParent; };
    Q_INVOKABLE CppToQmlMemoryTestAbstractListModel * getAlModelWithParent() { return alModelWithParent; };
    Q_INVOKABLE CppToQmlMemoryTestAbstractListModel * getAlModelNoParentFromSp() { return spAlModelNoParent.data(); };
    Q_INVOKABLE CppToQmlMemoryTestAbstractListModel * getAlModelWithParentFromSp() { return spAlModelWithParent.data(); };

signals:

    void alModelNoParentChanged();
    void alModelWithParentChanged();
    void spAlModelNoParentChanged();
    void spAlModelWithParentChanged();

private:
};

#endif // CPPTOQMLMEMORYTESTVM_H
