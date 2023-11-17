import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QProcess with AVRDUDE")

    ColumnLayout {
        id: columnLayout
        anchors.margins: 15

        spacing: 10
        anchors.fill: parent

        Button {
            id: buttonSearch

            text: qsTr("Search")
            highlighted: true

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            onClicked: comboBoxDevice.model = serialPortDevices.searchAndGetConnectedDevices()
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.preferredHeight: 48

            ComboBox {
                id: comboBoxDevice

                model: ListModel {}
                enabled: (comboBoxDevice.model.length > 0)

                Layout.fillWidth: true
                Layout.preferredHeight: 48
            }

            Button {
                id: buttonNumberOfDevices

                highlighted: true
                enabled: (comboBoxDevice.model.length > 0)
                text: (comboBoxDevice.model.length > 0) ? comboBoxDevice.model.length.toString() : "0"

                Layout.preferredHeight: 48
            }
        }

        TextField {
            id: textFieldBinary

            placeholderText: qsTr("path to binary")
            selectByMouse: true
            horizontalAlignment: Text.AlignHCenter
            enabled: (comboBoxDevice.model.length > 0)

            Layout.fillWidth: true
            Layout.preferredHeight: 48
        }

        Button {
            id: buttonUpload

            text: qsTr("Upload")
            highlighted: true
            enabled: (comboBoxDevice.model.length > 0) && textFieldBinary.text.match(".hex")

            Layout.fillWidth: true
            Layout.preferredHeight: 48

            onClicked: processRunner.run(comboBoxDevice.currentText, textFieldBinary.text)
        }

        ScrollView {
            id: scrollView

            Layout.fillHeight: true
            Layout.fillWidth: true

            TextArea {
                id: textAreaOutput

                font.pointSize: 8
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft

                readOnly: true
                selectByMouse: true

                Layout.fillHeight: true
                Layout.fillWidth: true

                Connections {
                    target: processRunner
                    onOutput: {
                        textAreaOutput.text = _output

                        // przewijanie w dół ScrollView: https://forum.qt.io/topic/94073/change-position-of-a-scrollview/5
                        scrollView.contentItem.contentY = textAreaOutput.height - scrollView.contentItem.height
                    }
                }
            }
        }
    }
}
