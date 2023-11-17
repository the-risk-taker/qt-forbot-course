import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

ApplicationWindow {
    id: applicationWindow

    property bool isConnected: rover.isConnected

    title: qsTr("Rover")
    visible: true
    minimumWidth: column.width * 1.2; minimumHeight: column.height * 2.0
    width: minimumWidth; height: minimumHeight

    Column {
        id: column

        spacing: 20
        anchors.centerIn: parent

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: goForward

                enabled: startStop.highlighted
                highlighted: true
                icon.source: "/media/icons/keyboard_arrow_up-24px.svg"

                onPressed: rover.goForward()
                onReleased: rover.stop()
            }
        }

        Row {
            spacing: 40
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: goLeft

                enabled: startStop.highlighted
                highlighted: true
                icon.source: "/media/icons/keyboard_arrow_left-24px.svg"

                onPressed: rover.goLeft()
                onReleased: rover.stop()
            }

            Button {
                id: startStop

                property bool isWorking: false

                icon.source: isWorking ? "qrc:/media/icons/power-24px.svg" : "qrc:/media/icons/power_off-24px.svg"

                highlighted: isWorking && isConnected

                onClicked: isWorking = !isWorking
            }

            Button {
                id: goRight

                enabled: startStop.highlighted
                highlighted: true
                icon.source: "/media/icons/keyboard_arrow_right-24px.svg"

                onPressed: rover.goRight()
                onReleased: rover.stop()
            }
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: goBackward

                enabled: startStop.highlighted
                highlighted: true
                icon.source: "/media/icons/keyboard_arrow_down-24px.svg"

                onPressed: rover.goBackward()
                onReleased: rover.stop()
            }
        }

        Slider {
            id: controlLevel

            width: column.width
            enabled: startStop.highlighted

            from: 0; to: 100; stepSize: 0.1
            value: to * 0.2

            onValueChanged: rover.controlLevel = value

            ToolTip {
                parent: controlLevel.handle
                visible: controlLevel.pressed
                text: controlLevel.value.toFixed(1)
            }
        }
    }

    Rectangle {
        id: footer

        anchors.bottom: parent.bottom
        width: parent.width; height: 25

        color: Material.accent

        Row {
            id: row

            anchors.fill: parent

            BusyIndicator {
                id: status

                anchors.verticalCenter: parent.verticalCenter
                height: parent.height + 3; width: height
                Material.accent: "white"

                running: isConnected
            }
        }
    }

    Connections {
        target: rover
        onIsConnectedChanged: console.log("Stan połączenia się zmienił!")
    }
}

