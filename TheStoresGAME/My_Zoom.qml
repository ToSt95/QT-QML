import QtQuick 2.0

Rectangle
{
    id:root
    anchors.fill: root
    color: "#202020"




    MouseArea
    {
        id:z1
        anchors.fill: parent

        onClicked:
        {
            fade_in.start()
            t1.aaa = window_main.source_page_zoom
            t1.start()

        }
    }

    Image
    {
        id:bg
        anchors.fill: parent
        source: window_main.source_zoom_image
        anchors.margins: 40

    }

    Rectangle
    {
        id: fade_out
        anchors.fill: parent
        color: "black"

        ParallelAnimation
        {
            running: true
            NumberAnimation { target: fade_out; property: "opacity"; to: 0; duration: 1000 }
        }

        ParallelAnimation
        {
            id:fade_in
            running: false
            NumberAnimation { target: fade_out; property: "opacity"; to: 1; duration: 1000 }
        }

    }




}
