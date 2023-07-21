#include "bookdao.h"

BookDao::BookDao()
{

}

void BookDao::openDb()
{
    auto db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");

    if (!db.open()) {
       qDebug() << "Error: connection with database failed";
    } else {
       qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    query.prepare("CREATE TABLE IF NOT EXISTS books ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "author TEXT NOT NULL,"
        "title TEXT NOT NULL,"
        "tp INTEGER NOT NULL,"
        "position INTEGER NOT NULL);"
    );
    
    if (!query.exec()) { qDebug() << "Create table error:" << query.lastError(); }
}

QList<BookModel> BookDao::getAllBooks()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM books ORDER BY position ASC;");

    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    int idxId = query.record().indexOf("id");
    int idxAuthor = query.record().indexOf("author");
    int idxTitle = query.record().indexOf("title");
    int idxTp = query.record().indexOf("tp");
    int idxPosition = query.record().indexOf("position");

    auto result = QList<BookModel>();

    while (query.next()) 
    {
        auto id = query.value(idxId).toInt();
        auto author = query.value(idxAuthor).toString();
        auto title = query.value(idxTitle).toString();
        auto tp = query.value(idxTp).toInt();
        auto position = query.value(idxPosition).toInt();

        result.append(BookModel(id, author, title, tp, position));
    }
    
    return result;
}

int BookDao::insert(BookModel book)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE books "
        "SET position = position + 1 "
        "WHERE position >= ?;"
    );
    query.addBindValue(book.position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare(
        "INSERT INTO books "
        "(author, title, tp, position) "
        "VALUES(?, ?, ?, ?);"
    );
    query.addBindValue(book.author);
    query.addBindValue(book.title);
    query.addBindValue(book.totalPages);
    query.addBindValue(book.position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    return query.lastInsertId().toInt();
}

void BookDao::remove(const int id, const int position)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE books "
        "SET position = position - 1 "
        "WHERE position >= ?;"
    );
    query.addBindValue(position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare("DELETE FROM books WHERE id = ?;");
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }
}

void BookDao::moveToTop(const int id, const int position)
{
    QSqlQuery query;
    query.prepare(
        "UPDATE books "
        "SET position = position + 1 "
        "WHERE position < ?;"
    );
    query.addBindValue(position);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }

    query.prepare(
        "UPDATE books "
        "SET position = 0 "
        "WHERE id = ?;"
    );
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }
}

void BookDao::update(const int id, const QString author, const QString title, const int totalPages)
{
    QSqlQuery query;

    query.prepare(
        "UPDATE books "
        "SET author = ?, title = ?, tp = ? "
        "WHERE id = ?;"
    );
    query.addBindValue(author);
    query.addBindValue(title);
    query.addBindValue(totalPages);
    query.addBindValue(id);
    if (!query.exec()) { qDebug() << "Failed: " << query.lastError(); }
}

void BookDao::closeDb()
{
    {
        // this additional scope is necessary, because allows
        // to release db object after it was closed but before
        // removeDatabase will be called
        auto db = QSqlDatabase::database();
        db.close();
    }
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}

BookModel::BookModel(const int id, const QString author, const QString title, const int totalPages, const int position) {
    this->id = id;
    this->author = author;
    this->title = title;
    this->totalPages = totalPages;
    this->position = position;
}
