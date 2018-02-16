import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Window 2.2
import QtQuick.Controls.Styles 1.4

Window
{
    id: mainWindow
    visible: true
    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width
    title: qsTr("tic tac toe")


    Rectangle
    {
       id: fields
       anchors.left: parent.left
       height: parent.height *0.8
       width: parent.width
       gradient: Gradient
              {
                   GradientStop {
                       position: 0.0
                       SequentialAnimation on color {
                           loops: Animation.Infinite
                           ColorAnimation { from: "#ffffff"; to: "#3a3a3a"; duration: 5000 }
                           ColorAnimation { from: "#3a3a3a"; to: "#ffffff"; duration: 5000 }
                       }
                   }
                   GradientStop {
                       position: 1.0
                       SequentialAnimation on color {
                           loops: Animation.Infinite
                           ColorAnimation { from: "#ffffff"; to: "#3a3a3a"; duration: 5000 }
                           ColorAnimation { from: "#3a3a3a"; to: "#ffffff"; duration: 5000 }
                       }
                   }
               }
       GridLayout
       {
           id: grid
           rows: 3
           columns: 3
           columnSpacing: 1
           rowSpacing: 1
           anchors.centerIn: parent

           BoardField
           {
              rowInfo:1
              columnInfo:1
           }
           BoardField
           {
              rowInfo:1
              columnInfo:2
           }
           BoardField
           {
               rowInfo:1
               columnInfo:3
           }
           BoardField
           {
               rowInfo:2
               columnInfo:1
           }
           BoardField
           {
               rowInfo:2
               columnInfo:2
           }
           BoardField
           {
               rowInfo:2
               columnInfo:3
           }
           BoardField
           {
               rowInfo:3
               columnInfo:1
           }
           BoardField
           {
               rowInfo:3
               columnInfo:2
           }
           BoardField
           {
               rowInfo:3
               columnInfo:3
           }
       }
    }
    Rectangle
    {
           id: subMenu
           anchors.bottom: parent.bottom
           height: parent.height*0.2
           width: parent.width
           color: "#231f1f"
           border.color: "#545454"
           border.width: 5

           signal restartGameButtonClicked

           Button
           {
               id:restartGameButton
               width: 150
               height: 50
               anchors.verticalCenter: parent.verticalCenter
               anchors.left:parent.left
               anchors.margins: 50;

               text: "NEXT ROUND"

               background: Rectangle{
                   color: "#adabab"
                   border.color: "white"
                   border.width: 1
                   radius: 2
               }

               onClicked:
               {
                   subMenu.restartGameButtonClicked();
               }
           }
           Text
           {
               id: currentPlayerLabel
               anchors.verticalCenter: parent.verticalCenter
               anchors.horizontalCenter: parent.horizontalCenter
               anchors.margins: 50;
               color:"white"
               font.family: "Helvetica"
               font.pointSize: 15;
               font.bold: true
           }
           Text
           {
               id: scoreLabel
               anchors.verticalCenter: parent.verticalCenter
               anchors.right:parent.right
               anchors.margins: 50;

               color:"white"
               font.family: "Helvetica"
               font.pointSize: 25;
               font.bold: true
           }
    }
}
