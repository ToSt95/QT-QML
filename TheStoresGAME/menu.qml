import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import QtMultimedia 5.8




Rectangle
{

    id:root
    anchors.fill: parent
    color: "transparent"

    Image
    {
        anchors.fill: parent
        source:"/img/2.jpg"

        Image
        {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            source:"/img/3.png"
        }
        //
        Column
        {
            id: menu
            spacing:10
            anchors.centerIn: parent

            Custom_Button
            {
                id: newgame
                source:"/img/5.png"
                width: 150
                height: 100

                onClicked:
                {
                    fade_out.start()
                    t1.aaa = "nn.qml"
                    t1.start()

                }

            }

            Custom_Button
            {
                id:settings
                source:"/img/4.png"
                width: 150
                height: 100
                onClicked:

                {

                }

            }


            Custom_Button
            {

                id:ess
                source:"/img/6.png"
                width: 150
                height: 100
                onClicked:
                {
                    fade_out.start()
                    window_main.close()

                }

            }
        }

    }

    Rectangle
    {
        id: black
        anchors.fill: parent
        color: "black"

        ParallelAnimation
        {
            id: fade_in
            running: true
            NumberAnimation { target: black; property: "opacity"; to: 0; duration: 2000 }
        }

        ParallelAnimation
        {
            id:fade_out
            running: false
            NumberAnimation { target: black; property: "opacity"; to: 1; duration: 2000 }
        }

    }

    Timer
    {
        id:t1
        interval: 2000;
        running: false;
        property url aaa
        onTriggered:
        {
            next_page.source = aaa;
        }
    }




}






