import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    property PageStack pageStack

    objectName: "rootCoordinatorQml"

    function push(page, properties) {
        pageStack.push(page, properties)
    }
}
