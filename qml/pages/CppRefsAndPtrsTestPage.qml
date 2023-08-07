import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property CppRefsAndPtrsTestVM viewModel
    onViewModelChanged: viewModel.parent = this
    allowedOrientations: Orientation.All

    PageHeader {
        title: qsTr("Cpp To Qml Memory Test Page")
    }
}

