import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property CppToQmlMemoryTestVM viewModel
    onViewModelChanged: {
        viewModel.parent = this

        var v1 = viewModel.getModelNoParent().foo()
        var v2 = viewModel.getModelWithParent().foo()
        var v3 = viewModel.getModelNoParentFromSp().foo()
        var v4 = viewModel.getModelWithParentFromSp().foo()
    }
    allowedOrientations: Orientation.All

    PageHeader {
        title: qsTr("Cpp To Qml Memory Test Page")
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Execute foo()"
            onClicked: {
                var v1 = viewModel.getModelNoParent().foo()
                var v2 = viewModel.getModelWithParent().foo()
                var v3 = viewModel.getModelNoParentFromSp().foo()
                var v4 = viewModel.getModelWithParentFromSp().foo()
            }
        }
    }

}
