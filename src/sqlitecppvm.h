#ifndef SQLITECPPVM_H
#define SQLITECPPVM_H

#include <QAbstractListModel>
#include <QtSql>

struct BookModel;

class SQLiteCppVM : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject * parent READ parent WRITE setParent)

public:
    enum BookModelRoles {
        Author = Qt::UserRole + 1,
        Title = Qt::UserRole + 2,
        TotalPages = Qt::UserRole + 3,
        Position = Qt::UserRole + 4
    };
    Q_ENUM(BookModelRoles)

    explicit SQLiteCppVM(QObject *parent = nullptr);
    ~SQLiteCppVM();

    virtual int rowCount(const QModelIndex&) const { return books.size(); }
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    
    void openDb();
    QList<BookModel> getAllBooks();
    void insert(BookModel book);
    Q_INVOKABLE void insert(const QString author, const QString title, const int totalPages, const int position);
    Q_INVOKABLE void remove(const int id, const int position);
    void closeDb();

signals:

private: 
    QList<BookModel> books;
};

struct BookModel
{
    explicit BookModel(const int id, const QString author, const QString title, const int totalPages, const int position);

    int id;
    QString author;
    QString title;
    int totalPages;
    int position;
};

#endif // SQLITECPPVM_H
