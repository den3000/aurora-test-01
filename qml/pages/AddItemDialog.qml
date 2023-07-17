import QtQuick 2.0
import Sailfish.Silica 1.0

Dialog {
    property string dialogTitle

    property string bookAuthor
    property string bookTitle
    property int bookTotalPages

    DialogHeader {
        id: header
        acceptText: qsTr("Accept")
        title: dialogTitle
    }

    TextField {
        id: tfAuthor
        anchors.top: header.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter book author")
        label: qsTr("Book author")
        text: bookAuthor
    }

    TextField {
        id: tfTitle
        anchors.top: tfAuthor.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter book title")
        label: qsTr("Book title")
        text: bookTitle
    }

    TextField {
        id: tfPagesNum
        anchors.top: tfTitle.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        placeholderText: qsTr("Enter total number of pages in book")
        label: qsTr("Number of pages ")
        text: bookTotalPages === 0 ? "" : bookTotalPages
    }

    onDone: if (result == DialogResult.Accepted) {
                bookAuthor = tfAuthor.text
                bookTitle = tfTitle.text
                bookTotalPages = tfPagesNum.text
            }
}
