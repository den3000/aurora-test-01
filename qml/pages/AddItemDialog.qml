import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string dialogTitle

    property string itemName
    property string itemDescription
    property int itemAmount

    DialogHeader {
        id: header
        acceptText: qsTr("Accept")
        title: dialogTitle
    }

    TextField {
        id: nameField
        anchors.top: header.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter item name")
        label: qsTr("Item name")
        text: "P"
    }

    TextField {
        id: descField
        anchors.top: nameField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter item description")
        label: qsTr("Item description")
        text: "PP"
    }

    TextField {
        id: amountField
        anchors.top: descField.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter item description")
        label: qsTr("Item description")
        text: "10"
    }

    onDone: if (result == DialogResult.Accepted) {
                itemName = nameField.text
                itemDescription = descField.text
                itemAmount = amountField.text
            }
}
