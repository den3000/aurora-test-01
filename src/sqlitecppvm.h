#ifndef SQLITECPPVM_H
#define SQLITECPPVM_H

#include <QAbstractListModel>

struct BookModel;

class SQLiteCppVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    explicit SQLiteCppVM(QObject *parent = nullptr);

    virtual int rowCount(const QModelIndex&) const { return books.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;

signals:

private: 
    QList<BookModel> books;
};

struct BookModel
{
    explicit BookModel(const QString author, const QString title, const int totalPages, const int position);

    QString author;
    QString title;
    int totalPages;
    int position;
};

#endif // SQLITECPPVM_H
