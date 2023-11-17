import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow

    visible: true
    width: 640
    height: 480

    Column {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        spacing: 10

        // Kolejność definiowania obiektów, definiuje ich kolejność wyświetlania!

        BusyIndicator { anchors.horizontalCenter: parent.horizontalCenter }

        Button {
            text: "Wygeneruj losowy błąd"
            highlighted: true
            anchors.horizontalCenter: parent.horizontalCenter

            // tutaj otwieram okno dialogowe:
            onClicked: dialog.open()
        }
    }

    Dialog {
        id: dialog

        // Zdefiniowanie własnego property:
        property int error: 0

        anchors.centerIn: parent
        width: parent.width * 0.7

        modal: true
        title: "Uwaga!"
        closePolicy: Dialog.NoAutoClose

        onAboutToShow: {
            checkBox.checked = false
            error = Math.round(Math.random() * 1000)
        }

        Column {
            id: column

            spacing: 20
            anchors.fill: parent

            Label {
                id: label

                text: "Nieoczekiwanie wystąpił błąd numer <b>" + dialog.error + "</b>. Potwierdź przeczytanie informacji."
                wrapMode: Text.WordWrap
                textFormat: Text.RichText
                width: parent.width
            }

            CheckBox {
                id: checkBox

                text: "Zrozumiałem"
                anchors.right: parent.right
            }

            Row {
                anchors.right: parent.right
                spacing: 20

                DialogButtonBox {
                    id: ok

                    enabled: checkBox.checked
                    standardButtons: Dialog.Ok

                    onClicked: {
                        // tutaj emituje sygnał, który mogę wykorzystać "wyżej"
                        dialog.accepted()

                        // tutaj zamykam okno dialogowe
                        dialog.close()
                    }
                }

                // Możemy zdefiniować więcej przycisków z różnymi funkcjami:
                // DialogButtonBox {
                //    // ...
                //    standardButtons: Dialog.Close
                //    // ...
                // }
            }
        }
    }
}
