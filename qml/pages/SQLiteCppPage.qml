import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property SqliteCppVM viewModel
    onViewModelChanged: viewModel.parent = this

    objectName: "sqliteCppPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("SQLite CPP DB")
    }
}
