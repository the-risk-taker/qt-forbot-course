import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 320
    height: 480
    title: qsTr("IPC - Client Side")

    function send() {
        if(textFieldMessage.text.length > 0) {
            client.writeToServer(textFieldMessage.text)

            textAreaOutput.text += "Client:\t" + textFieldMessage.text + " (" + new Date().toLocaleTimeString("hh:mm") + ")\n"
            textFieldMessage.text = ""
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.margins: 15

        spacing: 10
        anchors.fill: parent

        RowLayout {
            id: rowLayout

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            TextField {
                id: textFieldAddress

                text: "localhost"
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("enter server address")
                selectByMouse: true
                enabled: !client.connected

                Layout.fillWidth: true
                Layout.preferredHeight: 48
            }

            TextField {
                id: textFieldPort

                text: "5555"
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("enter port value")
                selectByMouse: true
                enabled: !client.connected

                Layout.fillWidth: true
                Layout.preferredHeight: 48
            }
        }

        Button {
            id: buttonConnect

            text: qsTr("Connect to server")
            highlighted: true
            enabled: !client.connected

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            onClicked: client.connectToServer(textFieldAddress.text, textFieldPort.text)
        }

        Button {
            id: buttonDisonnect

            text: qsTr("Disconnect from server")
            highlighted: true
            enabled: client.connected

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            onClicked: client.disconnectFromServer()
        }

        RowLayout {
            TextField {
                id: textFieldMessage

                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("enter mesage content here")
                enabled: client.connected
                focus: true

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
                enabled: client.connected

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
                    target: client
                    onMessageFromServer: textAreaOutput.text += "Server:\t" + _data + " (" + new Date().toLocaleTimeString("hh:mm") + ")\n"
                }
            }
        }
    }
}
