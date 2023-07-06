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

    function insertBook(author, title) {
    //  ...
    }

    function updateBook(id, author, title) {
    //  ...
    }

    function deleteBook(id) {
    //  ...
    }

    Component.onCompleted: {
        db = LocalStorage.openDatabaseSync("books", "1.0");
        createBooksTable();
    }
}
