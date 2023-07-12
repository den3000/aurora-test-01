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

    function insertBook(author, title, tp, callback) {
        db.transaction(function (tx) {
            var result = tx.executeSql(
                        "INSERT INTO books
                            (author, title, tp) VALUES(?, ?, ?);",
                        [author, title, tp]
                        );

            callback(result.insertId)
//            console.log("InsertedId = " + result.insertId);
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

    function retrieveBooksTotalPages(callback) {
        db.readTransaction(function (tx) {
            var result = tx.executeSql(
                        "SELECT SUM(tp) AS tpSum FROM books"
                        );
            callback(result.rows.item(0).tpSum)
        });

//        var database = LocalStorage.openDatabaseSync("books", "1.0");
//        database.readTransaction(function (tx) {
//            var result = tx.executeSql(
//                        "SELECT SUM(tp) AS tpSum FROM books");
//            callback(result.rows.item(0).tpSum)
//        });
    }

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("books", "1.1");
        createBooksTable();

        if (db.version === "1.0") {
            console.log("Updating DB from 1.0 to 1.1")
            db.changeVersion("1.0", "1.1", function(tx) {
                tx.executeSql("INSERT INTO books (author, title, tp) VALUES(?, ?, ?)",
                              ["Leo Tolstoy","Anna Karenina", "1300"]);
            });
        } else {
            console.log("DB version is up to date")
        }
    }
}
