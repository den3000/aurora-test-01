#ifndef CPPTOQMLMEMORYTESTVM_H
#define CPPTOQMLMEMORYTESTVM_H

#include <QObject>
#include <QString>
#include <QDebug>

class CppToQmlMemoryTestModel : public QObject
{
    Q_OBJECT
public:    
    explicit CppToQmlMemoryTestModel(QObject *parent = nullptr);
    explicit CppToQmlMemoryTestModel(QString tag, QObject *parent = nullptr);
    ~CppToQmlMemoryTestModel();

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

signals:

};

#endif // CPPTOQMLMEMORYTESTVM_H
