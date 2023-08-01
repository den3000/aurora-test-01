import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property SqlQueryVM viewModel
    onViewModelChanged: viewModel.parent = this
    objectName: "sqliteCppPage"
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        header: PageHeader {
            title: qsTr("Sql Query Model")
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
                    onClicked: viewModel.queryModel().remove(index)

                }
                MenuItem {
                    text: qsTr("Move to top")
                    onClicked: viewModel.queryModel().moveToTop(index)
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
                text: "#" + model.position + " id:" + model.id + " " + model.title + " by " + model.author + ", " + model.tp + " pages"
            }

            onClicked: showEditItemDialog(model, index)
        }

        model: viewModel.queryModel()
    }

    function showCreateItemDialog(position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))
        dialog.dialogTitle = qsTr("Create new item")
        dialog.accepted.connect(function() {
            viewModel.queryModel().insert(dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages, position)
        })
    }

    function showEditItemDialog(model, position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))

        dialog.bookAuthor = model.author
        dialog.bookTitle = model.title
        dialog.bookTotalPages = model.tp

        dialog.dialogTitle = qsTr("Edit existing item")
        dialog.accepted.connect(function() {
            model.author = dialog.bookAuthor
            model.title = dialog.bookTitle
            model.tp = dialog.bookTotalPages
        })
    }

}
