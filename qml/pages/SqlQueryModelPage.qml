import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property BooksListModelVM viewModel
    property BookModelTable tableModel

    onViewModelChanged: {
        viewModel.parent = this
        // while this is done for convinience in qml it is important 
        // to say, that this will be required in case if this object 
        // on c++ side was initialized without a parent, otherwise it 
        // will be released immedeately after first access
        tableModel = viewModel.tableModel()
    }

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
                    onClicked: tableModel.remove(index)

                }
                MenuItem {
                    text: qsTr("Move to top")
                    onClicked: tableModel.moveToTop(index)
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

        model: tableModel
    }

    function showCreateItemDialog(position) {
        var dialog = pageStack.push(Qt.resolvedUrl("AddItemDialog.qml"))
        dialog.dialogTitle = qsTr("Create new item")
        dialog.accepted.connect(function() {
            tableModel.insert(dialog.bookAuthor, dialog.bookTitle, dialog.bookTotalPages, position)
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
