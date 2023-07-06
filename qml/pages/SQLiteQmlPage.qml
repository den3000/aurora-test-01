import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    Dao { id: dao }

    PageHeader {
        id: header
        objectName: "pageHeader"
        title: qsTr("SQLite QML DB")
    }

    SilicaListView {
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        model: ListModel { id: booksListModel }
        delegate: ListItem {
            Label {
                x: Theme.horizontalPageMargin
                text: title + " by " + author
            }
        }
    }

    function selectBooks() {
        booksListModel.clear();
        dao.retrieveBooks(function (books) {
            for (var i = 0; i < books.length; i++) {
                var book = books.item(i);
                booksListModel.append(
                            {
                                id: book.id,
                                author: book.author,
                                title: book.title,
//                                total pages: book.tp
                            }
                            );
            }
        });
    }

    Component.onCompleted: {
        selectBooks()
    }

}
