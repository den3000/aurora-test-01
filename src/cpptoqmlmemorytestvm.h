#ifndef CPPTOQMLMEMORYTESTVM_H
#define CPPTOQMLMEMORYTESTVM_H

#include <QObject>

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
