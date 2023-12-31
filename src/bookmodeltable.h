#ifndef BOOKMODELTABLE_H
#define BOOKMODELTABLE_H

#include <QObject>
#include <QSqlTableModel>

// this include is required to access QSqlRecord type
#include <QSqlRecord>

class BookModelTable;

struct IBooksModelTableProvider {
    virtual BookModelTable * booksModelTable(QObject *parent = nullptr) const = 0;
};

class BookModelTable : public QSqlTableModel
{
    Q_OBJECT
public:

    enum BookQueryRoles {
        Id = Qt::UserRole + 1,
        Author = Qt::UserRole + 2,
        Title = Qt::UserRole + 3,
        TotalPages = Qt::UserRole + 4,
        Position = Qt::UserRole + 5
    };
    Q_ENUM(BookQueryRoles)

    explicit BookModelTable(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~BookModelTable();

    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    Q_INVOKABLE void moveToTop(const int position);
    Q_INVOKABLE void remove(const int position);
    Q_INVOKABLE void insert(const QString author, const QString title, const int totalPages, const int position);

signals:

private:
    template<typename F>
    void updateRecordsInRange(const int start, const int end, const bool executeSubmitAll, F && lambda) {
        for (int row = start; row < end; row++) {
            auto r = record(row);
            lambda(row, r);
            setRecord(row, r);
        }

        if (executeSubmitAll) { submitAll(); }
    };

};

#endif // BOOKMODELTABLE_H
