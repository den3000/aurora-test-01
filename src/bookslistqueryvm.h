#ifndef BOOKSLISTQUERYVM_H
#define BOOKSLISTQUERYVM_H

#include <QAbstractListModel>
#include "functional"

#include "sqlitedb.h"

class BooksListQueryVM : public QAbstractListModel
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

    explicit BooksListQueryVM(QObject *parent = nullptr) : QAbstractListModel(parent) { };
    explicit BooksListQueryVM(IBooksQueryTableProvider * bookQueryTable, QObject *parent = nullptr);
    ~BooksListQueryVM();

    virtual int rowCount(const QModelIndex&) const { return books.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    Q_INVOKABLE void insert(const QString author, const QString title, const int totalPages, const int position);
    Q_INVOKABLE void remove(const int id, const int position);
    Q_INVOKABLE void moveToTop(const int id, const int position);
    Q_INVOKABLE void update(const int id, const QString author, const QString title, const int totalPages, const int position);

signals:

private: 
    QList<BookDao> books;
    IBooksQueryTableProvider * tableProvider;
    BookQueryTable *bookQueryTable;

    template<typename F>
    inline void updateData(const int start, const int end, F && lambda);

    // alternative lambda useage for a case when function
    // can't be defined in a header. Potential problems here
    // related to move semantics and unique ptr sharing or something
    // like that
    // #include "functional" is required to use this
    inline void updateDataAlt(const int start, const int end, std::function<void(int, BookDao &)> && lambda);
};
#endif // BOOKSLISTQUERYVM_H
