/*******************************************************************************
**
** Copyright (C) 2022 ru.auroraos
**
** This file is part of the My Aurora OS Application project.
**
** Redistribution and use in source and binary forms,
** with or without modification, are permitted provided
** that the following conditions are met:
**
** * Redistributions of source code must retain the above copyright notice,
**   this list of conditions and the following disclaimer.
** * Redistributions in binary form must reproduce the above copyright notice,
**   this list of conditions and the following disclaimer
**   in the documentation and/or other materials provided with the distribution.
** * Neither the name of the copyright holder nor the names of its contributors
**   may be used to endorse or promote products derived from this software
**   without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
** THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
** FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
** OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
** PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
** LOSS OF USE, DATA, OR PROFITS;
** OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE)
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
** EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
*******************************************************************************/

import QtQuick 2.0
import Sailfish.Silica 1.0
import CustomCppClasses.Module 1.0

Page {
    property MainVM model

    objectName: "mainPage"
    allowedOrientations: Orientation.All

    PageHeader {
        objectName: "pageHeader"
        title: qsTr("DI and Navigation example")
        extraContent.children: [
            IconButton {
                objectName: "aboutButton"
                icon.source: "image://theme/icon-m-about"
                anchors.verticalCenter: parent.verticalCenter

                onClicked: model.gotoAboutPage();
            }
        ]
    }

    Column {
        id: layout
        width: parent.width
        spacing: 16
        anchors.centerIn: parent

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Create AboutVM from QML"
            onClicked: {
                // Use this to push page directly, for example
                // if VM is already defined in page explicitly
                // pageStack.push(Qt.resolvedUrl("AboutPage.qml"))

                /*
                 Use this to push page and assign custom property like vm
                 The problem here is that such VM will be parented to this
                 page (the page from which new page will be pushed) and not
                 to pushed page. This need to be changed on new page side.
                */
                // var aboutVm = Qt.createQmlObject('import CustomCppClasses.Module 1.0; AboutVM {}', this, "errorLog")
                // pageStack.push(Qt.resolvedUrl("AboutPage.qml"), { "viewModel": aboutVm })

                /*
                 Use this to push page and assign custom property like vm
                 The problem here is that such VM will be parented to `pageComponent`
                 object, which is not a page, but might be called page builder.
                 So this parenting need to be changed on new page side.
                */
                var pageComponent = Qt.createComponent("AboutPage.qml")
                var aboutVm = Qt.createQmlObject('import CustomCppClasses.Module 1.0; AboutVM {}', pageComponent, "errorLog")
                pageStack.push(pageComponent, { "viewModel": aboutVm })

                // All such approaches seems unreliable as in fact
                // uses magic strings that will be hard to maintain and refactor
            }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "AboutVM with Int"
            onClicked: model.gotoAboutPageWithInt(100)
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "AboutVM with Str"
            onClicked: model.gotoAboutPageWithString("some string param")
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "AboutVM with Model"
            onClicked: model.openAboutPageWithModel(1)
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Log Context Property"
            onClicked: {
                // Since cppContextProperty was injected into QML context
                // it is available here directly
                console.log(cppContextProperty)
            }
        }

        Button {
            anchors { left: parent.left; right: parent.right; margins: Theme.horizontalPageMargin }
            text: "Invoke model.foo()"
            onClicked: model.foo()
        }
    }

    onStatusChanged: {
        switch (status) {
        case PageStatus.Inactive:
            return console.log("Inactive");
        case PageStatus.Activating:
            return console.log("Activating");
        case PageStatus.Active:
            return console.log("Active");
        case PageStatus.Deactivating:
            return console.log("Deactivating");
        }
    }
}
