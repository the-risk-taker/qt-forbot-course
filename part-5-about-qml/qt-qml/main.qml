import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
   visible: true
   width: 640
   height: 480
   title: qsTr("Hello World")

   Button {
       id: button
       text: "Close"
       highlighted: true

       anchors.centerIn: parent

       onClicked: {
           timer.start()
           console.log("Button was clicked")
       }
   }

   Timer {
       id: timer
       interval: 2000 // podawany w ms

       onTriggered: Qt.quit()
   }
}
