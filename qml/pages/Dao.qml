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
                            tp INTEGER NOT NULL,
                            position INTEGER NOT NULL);"
                        );
        });
    }

    function moveToTop(id, position) {
        db.transaction(function (tx) {
            tx.executeSql("
                        UPDATE books
                        SET position = position + 1
                        WHERE position < ?
                        ;",
                        position
                        )

            tx.executeSql("
                        UPDATE books
                        SET position = 0
                        WHERE id = ?
                        ;",
                        id
                        )

        })
    }

    function insertBook(author, title, tp, position, callback) {
        db.transaction(function (tx) {
            tx.executeSql("
                        UPDATE books
                        SET position = position + 1
                        WHERE position >= ?
                        ;",
                        position
                        )
            var result = tx.executeSql(
                        "
                        INSERT INTO books
                        (author, title, tp, position)
                        VALUES(?, ?, ?, ?)
                        ;",
                        [author, title, tp, position]
                        )
            callback(parseInt(result.insertId, 10))
        });
    }

    function updateBook(id, author, title, totalPages) {
        db.transaction(function (tx) {
            tx.executeSql(
                        "UPDATE books
                            SET author = ?, title = ?, tp = ?
                        WHERE id = ?;",
                        [author, title, totalPages, id]
                        );
        });
    }

    function retrieveBooks(callback) {
        db.readTransaction(function (tx) {
            var result = tx.executeSql("SELECT * FROM books ORDER BY position ASC;");
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
    }

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("books", "");
        console.log("DB current version " + db.version)

        createBooksTable();

        if (db.version === "1.1") {
            console.log("Updating DB from 1.1 to 1.2")
            db.changeVersion("1.1", "1.2", function(tx) {
                tx.executeSql("ALTER TABLE books ADD position INTEGER NOT NULL default '-1';")
            })
        } else if (db.version === "1.0" || db.version === "") {
            console.log("Updating DB from 1.0 to 1.1")
            db.changeVersion("", "1.1", function(tx) {
                tx.executeSql("INSERT INTO books (author, title, tp) VALUES(?, ?, ?)",
                              ["Leo Tolstoy","Anna Karenina", "1300"]);
            });
        } else {
            console.log("DB version is up to date")
        }
    }
}
