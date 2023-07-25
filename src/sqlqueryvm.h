#ifndef SQLQUERYVM_H
#define SQLQUERYVM_H

#include <QObject>

class SqlQueryVM : public QObject
{
    Q_OBJECT
public:
    explicit SqlQueryVM(QObject *parent = nullptr);

signals:

};

#endif // SQLQUERYVM_H
