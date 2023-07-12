import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    Dao { id: dao }

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("SQLite QML DB")
        }

        delegate: ListItem {
            menu: ContextMenu {
                MenuItem {
                    text: qsTr("Edit")
//                    onClicked: listModel.remove(index)
                }
                MenuItem {
                    text: qsTr("Add new here")
                    onClicked: showCreateItemDialog(index)
                }
                MenuItem {
                    text: qsTr("Add new below")
                    onClicked: showCreateItemDialog(index+1)
                }
                MenuItem {
                    text: qsTr("Remove")
                    onClicked: {
                        dao.deleteBook(id)
                        booksListModel.remove(index)
                    }

                }
                MenuItem {
                    text: qsTr("Move to top")
//                    onClicked: listModel.moveToTop(index)
                }
            }
            Label {
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                 text: "#" + position + " " + title + " by " + author + ", " + totalPages + " pages"
            }
        }

        model: ListModel { id: booksListModel }
    }

    function reloadAllBooks() {
        booksListModel.clear();
        dao.retrieveBooks(function (books) {
            for (var i = 0; i < books.length; i++) {
                var book = books.item(i);
                booksListModel.append(
                            {
                                id: book.id,
                                author: book.author,
                                title: book.title,
                                totalPages: book.tp,
                                position: book.position
                            }
                            );
            }
        });
    }

    function showCreateItemDialog(position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))
        dialog.dialogTitle = qsTr("Create new item")
        dialog.accepted.connect(function() {
            console.log(qsTr("Accepted done"))
            dao.insertBook(dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages,
               function(insertId) {
                   console.log("InsertId = " + insertId)
               }
            )
            reloadAllBooks()
        })
    }


    Component.onCompleted: {
        reloadAllBooks()
    }
}
