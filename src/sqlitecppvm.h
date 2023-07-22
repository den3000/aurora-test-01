#ifndef SQLITECPPVM_H
#define SQLITECPPVM_H

#include <QAbstractListModel>
#include "bookdao.h"

class SQLiteCppVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    enum BookModelRoles {
        Id = Qt::UserRole + 1,
        Author = Qt::UserRole + 2,
        Title = Qt::UserRole + 3,
        TotalPages = Qt::UserRole + 4,
        Position = Qt::UserRole + 5
    };
    Q_ENUM(BookModelRoles)

    explicit SQLiteCppVM(QObject *parent = nullptr) : QAbstractListModel(parent) { };
    explicit SQLiteCppVM(BookDao * bookDao, QObject *parent = nullptr);
    ~SQLiteCppVM();

    virtual int rowCount(const QModelIndex&) const { return books.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    Q_INVOKABLE void insert(const QString author, const QString title, const int totalPages, const int position);
    Q_INVOKABLE void remove(const int id, const int position);
    Q_INVOKABLE void moveToTop(const int id, const int position);
    Q_INVOKABLE void update(const int id, const QString author, const QString title, const int totalPages, const int position);

signals:

private: 
    QList<BookModel> books;
    BookDao *dao;
};

#endif // SQLITECPPVM_H
