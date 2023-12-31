import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property BooksListQueryVM viewModel
    onViewModelChanged: viewModel.parent = this
    objectName: "sqliteCppPage"
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("SQLite CPP DB")
        }

        delegate: ListItem {
            menu: ContextMenu {
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
                    onClicked: viewModel.remove(model.id, index)

                }
                MenuItem {
                    text: qsTr("Move to top")
                    onClicked: viewModel.moveToTop(model.id, index)
                }
            }
            Label {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                leftPadding: 8
                rightPadding: 8
                truncationMode: TruncationMode.Elide
                maximumLineCount: 1
                text: "#" + model.position + " id:" + model.id + " " + model.title + " by " + model.author + ", " + model.totalPages + " pages"
            }

            onClicked: showEditItemDialog(model, index)
        }

        model: viewModel
    }

    function showCreateItemDialog(position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))
        dialog.dialogTitle = qsTr("Create new item")
        dialog.accepted.connect(function() {
            viewModel.insert(dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages, position)
        })
    }

    function showEditItemDialog(model, position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))

        dialog.bookAuthor = model.author
        dialog.bookTitle = model.title
        dialog.bookTotalPages = model.totalPages

        dialog.dialogTitle = qsTr("Edit existing item")
        dialog.accepted.connect(function() {
            viewModel.update(model.id, dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages, position)
        })
    }

}
