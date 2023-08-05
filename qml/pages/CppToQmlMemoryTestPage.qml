import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property CppToQmlMemoryTestVM viewModel
    onViewModelChanged: {
        viewModel.parent = this

        var v1 = viewModel.modelNoParent.foo()
        var v2 = viewModel.modelWithParent.foo()
        var v3 = viewModel.spModelNoParent.foo()
        var v4 = viewModel.spModelWithParent.foo()
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
                var v1 = viewModel.modelNoParent.foo()
                var v2 = viewModel.modelWithParent.foo()
                var v3 = viewModel.spModelNoParent.foo()
                var v4 = viewModel.spModelWithParent.foo()
            }
        }
    }

}
