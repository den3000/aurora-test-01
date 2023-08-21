#ifndef CPPTOQMLMEMORYTESTABSTRACTLISTMODEL_H
#define CPPTOQMLMEMORYTESTABSTRACTLISTMODEL_H

#include <QAbstractListModel>
#include <QDebug>

class CppToQmlMemoryTestAbstractListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit CppToQmlMemoryTestAbstractListModel(QObject *parent = nullptr)
        : QAbstractListModel(parent) {
        tag = "default";
        qDebug() << tag << " created";
    };

    explicit CppToQmlMemoryTestAbstractListModel(QString tag, QObject *parent = nullptr)
        : QAbstractListModel(parent)  {
        this->tag = tag;
        qDebug() << tag << " created";
    };

    ~CppToQmlMemoryTestAbstractListModel() {
        qDebug() << tag << " released";
    };

    int rowCount(const QModelIndex&) const override { return 0; }

    QVariant data(const QModelIndex &index, int role) const override {
        Q_UNUSED(index)
        Q_UNUSED(role)
        return QVariant();
    };

    QHash<int, QByteArray> roleNames() const override { return QHash<int, QByteArray>(); };

private:
    QString tag;
};

#endif // CPPTOQMLMEMORYTESTABSTRACTLISTMODEL_H
