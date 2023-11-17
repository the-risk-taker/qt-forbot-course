import QtQuick 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
   id: applicationWindow

   visible: true
   width: 640
   height: 480
   title: qsTr("Freezing UI")

   Column {
       anchors.centerIn: parent
       spacing: 10

       BusyIndicator {
           anchors.horizontalCenter: parent.horizontalCenter
       }

       Button {
           id: button

           anchors.horizontalCenter: parent.horizontalCenter
           text: "Click me"

           onClicked: {
               enabled = false
               calculations.heavyCalculations()
           }

           Connections {
               target: calculations
               onFinished: button.enabled = true
           }

           Connections {
               target: calculations
               onResult: console.log("Result of calculations: ", result)
           }
       }

       ProgressBar {
           id: progressBar

           value: 0.0
           anchors.horizontalCenter: parent.horizontalCenter

           Connections {
               target: calculations
               onProgress: progressBar.value = value;
           }
       }
   }
}
