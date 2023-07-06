import QtQuick 2.0
import QtQuick.LocalStorage 2.0

QtObject {
    property var db;

    function createBooksTable() {
        db.transaction(function (tx) {
            tx.executeSql(
                        "CREATE TABLE IF NOT EXISTS books (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            author TEXT NOT NULL,
                            title TEXT NOT NULL,
                            tp INTEGER NOT NULL);"
                        );
        });
    }

    function insertBook(author, title, tp) {
        db.transaction(function (tx) {
            tx.executeSql(
                        "INSERT INTO books
                            (author, title, tp) VALUES(?, ?, ?);",
                        [author, title, tp]
                        );
        });
    }

    function updateBook(id, author, title) {
        db.transaction(function (tx) {
            tx.executeSql(
                        "UPDATE books
                            SET author = ?, title = ?
                        WHERE id = ?;",
                        [author, title, id]
                        );
        });
    }

    function retrieveBooks(callback) {
        db.readTransaction(function (tx) {
            var result = tx.executeSql("SELECT * FROM books;");
            callback(result.rows);
        });
    }

    function deleteBook(id) {
        db.transaction(function (tx) {
            tx.executeSql("DELETE FROM books WHERE id = ?;",
                          [id]);
        });
    }

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("books", "1.0");
        createBooksTable();

//        if (db.version === "1.0") {
//            db.changeVersion("1.0", "1.1", function(tx) {
//                tx.executeSql("INSERT INTO books VALUES(?, ?, ?)",
//                              ["Leo Tolstoy","Anna Karenina", "1300"]);
//            });
//        }
    }
}
