#ifndef BOOKQUERYMODEL_H
#define BOOKQUERYMODEL_H

#include <QObject>
#include <QSqlTableModel>

class BookQueryModel : public QSqlTableModel
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

    explicit BookQueryModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~BookQueryModel();

    virtual QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
    QVariant extractValue(QString name, int row, int role) const;

signals:

};

#endif // BOOKQUERYMODEL_H
