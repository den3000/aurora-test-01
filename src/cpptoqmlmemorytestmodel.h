#ifndef CPPTOQMLMEMORYTESTMODEL_H
#define CPPTOQMLMEMORYTESTMODEL_H

#include <QObject>
#include <QString>
#include <QDebug>

class CppToQmlMemoryTestModel : public QObject
{
    Q_OBJECT

public:
    explicit CppToQmlMemoryTestModel(QObject *parent = nullptr) : QObject(parent) {
        tag = "default";
        qDebug() << tag << " created";
    };

    explicit CppToQmlMemoryTestModel(QString tag, QObject *parent = nullptr) : QObject(parent) {
        this->tag = tag;
        qDebug() << tag << " created";
    };

    ~CppToQmlMemoryTestModel() {
        qDebug() << tag << " released";
    };

    Q_INVOKABLE void foo() {
        qDebug() << tag;
    };

private:
    QString tag;
};

#endif // CPPTOQMLMEMORYTESTMODEL_H
