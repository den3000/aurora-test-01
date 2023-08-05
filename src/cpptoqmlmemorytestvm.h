#ifndef CPPTOQMLMEMORYTESTVM_H
#define CPPTOQMLMEMORYTESTVM_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QSharedPointer>

// TODO: we also need some abstract item model
// or table model example for for demonstration
// of mem menagement with lists

class CppToQmlMemoryTestModel : public QObject
{
    Q_OBJECT
public:    
    explicit CppToQmlMemoryTestModel(QObject *parent = nullptr);
    explicit CppToQmlMemoryTestModel(QString tag, QObject *parent = nullptr);
    ~CppToQmlMemoryTestModel();

    Q_INVOKABLE void foo();
private: 
    QString tag;
};

class CppToQmlMemoryTestVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit CppToQmlMemoryTestVM(QObject *parent = nullptr);
    ~CppToQmlMemoryTestVM();

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelNoParent();
    Q_INVOKABLE CppToQmlMemoryTestModel * getModelWithParent();

    Q_INVOKABLE CppToQmlMemoryTestModel * getModelNoParentFromSp();
    Q_INVOKABLE CppToQmlMemoryTestModel * getModelWithParentFromSp();

signals:
private:
    CppToQmlMemoryTestModel * modelNoParent;
    CppToQmlMemoryTestModel * modelWithParent;

    QSharedPointer<CppToQmlMemoryTestModel> spModelNoParent;
    QSharedPointer<CppToQmlMemoryTestModel> spModelWithParent;
};

#endif // CPPTOQMLMEMORYTESTVM_H
