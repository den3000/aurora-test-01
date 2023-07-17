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
                    onClicked: showEditItemDialog(model, index)
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
                    onClicked: {
                        dao.moveToTop(model.id, index)
                        reloadAllBooks()
                    }
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

    function showCreateItemDialog(position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))
        dialog.dialogTitle = qsTr("Create new item")
        dialog.accepted.connect(function() {
            dao.insertBook(dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages, position,
               function(insertId) {
                   console.log("InsertId = " + insertId)

                   booksListModel.insert(position, {
                                             id: insertId,
                                             author: dialog.bookAuthor,
                                             title: dialog.bookTitle,
                                             totalPages: dialog.bookTotalPages,
                                             position: position
                                         })

                   for (var i = position + 1; i < booksListModel.count; i++) {
                       booksListModel.set(i, {
                                              position: i
                                          });
                   }
               }
            )
        })
    }

    function showEditItemDialog(model, position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))

        dialog.bookAuthor = model.author
        dialog.bookTitle = model.title
        dialog.bookTotalPages = model.totalPages

        dialog.dialogTitle = qsTr("Edit existing item")
        dialog.accepted.connect(function() {
            dao.updateBook(model.id, dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages)

            booksListModel.set(position, {
                                   id: model.id,
                                   author: dialog.bookAuthor,
                                   title: dialog.bookTitle,
                                   totalPages: dialog.bookTotalPages
                               })
        })
    }

    function reloadAllBooks() {
        booksListModel.clear()
        dao.retrieveBooks(function (books) {
            for (var i = 0; i < books.length; i++) {
                var book = books.item(i)
                booksListModel.append({
                                id: book.id,
                                author: book.author,
                                title: book.title,
                                totalPages: book.tp,
                                position: book.position
                            })
            }
        })
    }

    Component.onCompleted: {
        reloadAllBooks()
    }
}
