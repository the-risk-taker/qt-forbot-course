import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 320
    height: 480
    title: qsTr("IPC - Server Side")

    function send() {
        if(textFieldMessage.text.length > 0) {
            server.writeToClient(textFieldMessage.text)

            textAreaOutput.text += "Server:\t" + textFieldMessage.text + " (" + new Date().toLocaleTimeString("hh:mm") + ")\n"
            textFieldMessage.text = ""
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.margins: 15

        spacing: 10
        anchors.fill: parent

        TextField {
            id: textFieldPort

            text: "5555"
            horizontalAlignment: Text.AlignHCenter
            placeholderText: qsTr("enter port value")
            selectByMouse: true
            enabled: !server.serverStatus

            Layout.fillWidth: true
            Layout.preferredHeight: 48
        }

        Button {
            id: buttonConnect

            text: qsTr("Start server")
            highlighted: true
            enabled: !server.serverStatus

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            onClicked: server.setupServer(textFieldPort.text)
        }

        RowLayout {
            TextField {
                id: textFieldMessage

                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("enter mesage content here")
                enabled: server.serverStatus

                Layout.fillWidth: true
                Layout.preferredHeight: 48

                Keys.onPressed: {
                    if ((event.key === Qt.Key_Enter) || (event.key === Qt.Key_Return)) {
                        send()
                        event.accepted = true
                    }
                }
            }

            Button {
                text: ">"
                highlighted: true
                enabled: server.serverStatus

                onClicked: {
                    send()
                    textFieldMessage.focus = true
                }

                Layout.preferredHeight: 48
                Layout.preferredWidth: 48
            }
        }

        ScrollView {
            id: scrollView

            Layout.fillHeight: true
            Layout.fillWidth: true

            TextArea {
                id: textAreaOutput

                verticalAlignment: Text.AlignTop
                horizontalAlignment: Text.AlignLeft

                readOnly: true
                selectByMouse: true

                Layout.fillHeight: true
                Layout.fillWidth: true

                Connections {
                    target: server
                    onMessageFromClient: textAreaOutput.text += "Client:\t" + _data + " (" + new Date().toLocaleTimeString("hh:mm") + ")\n"
                }
            }
        }
    }
}
