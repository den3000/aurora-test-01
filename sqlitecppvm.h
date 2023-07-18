#ifndef SQLITECPPVM_H
#define SQLITECPPVM_H

#include <QObject>

class SQLiteCppVM : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SQLiteCppVM(QObject *parent = nullptr);

signals:

};

#endif // SQLITECPPVM_H
