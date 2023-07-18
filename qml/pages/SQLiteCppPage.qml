import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property SqliteCppVM viewModel
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
                    text: qsTr("Edit")
//                    onClicked: showEditItemDialog(model, index)
                }
                MenuItem {
                    text: qsTr("Add new here")
//                    onClicked: showCreateItemDialog(index)
                }
                MenuItem {
                    text: qsTr("Add new below")
//                    onClicked: showCreateItemDialog(index+1)
                }
                MenuItem {
                    text: qsTr("Remove")
//                    onClicked: {
//                        dao.deleteBook(id)
//                        booksListModel.remove(index)
//                    }

                }
                MenuItem {
                    text: qsTr("Move to top")
//                    onClicked: {
//                        dao.moveToTop(model.id, index)

//                        var from = index
//                        booksListModel.move(from, 0, 1)
//                        for (var i = 0; i <= from; i++) {
//                            booksListModel.set(i, {
//                                                   position: i
//                                               });
//                        }
//                    }
                }
            }
            Label {
                x: Theme.horizontalPageMargin
                anchors.verticalCenter: parent.verticalCenter
                text: model.display
//                text: "#" + position + " " + title + " by " + author + ", " + totalPages + " pages"
            }
        }

        model: viewModel
    }

}
