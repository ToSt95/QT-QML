import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtMultimedia 5.8
import QtQuick.Layouts 1.3
import "pick_item.js" as MyScript

Rectangle
{

    id:root
    anchors.fill: parent
    color: "transparent"

    Image
    {
        id:background
        source:"/img/tlo.png"
        anchors.fill: parent


        Audio
        {
            id: next
            source: "/mp3/3.mp3"
            volume: 1
        }

        Rectangle
        {
            border.width: 1
            id:strona_lewa
            width: parent.width/2
            height: parent.height
            color: "transparent"
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom




            Rectangle
            {
                id: obraz
                property bool zz: false
                border.width: 3
                border.color: "gray"
                width: parent.width
                color: "transparent"
                height: parent.height/3

                anchors.left: parent.left
                anchors.top: parent.top
                anchors.right: parent.right

                anchors.leftMargin: 35
                anchors.rightMargin: 50
                anchors.topMargin: 25

                MouseArea
                {
                    id:z1
                    anchors.fill: parent

                    onClicked:
                    {
                        window_main.source_page_zoom = "gameplay.qml"
                        window_main.source_zoom_image = img_1.source
                        next_page.source = "/My_Zoom.qml"

                    }
                }

                Image
                {
                    id:img_1
                    anchors.fill: obraz
                    anchors.rightMargin: 3
                    anchors.bottomMargin: 3
                    anchors.leftMargin: 3
                    anchors.topMargin: 3
                    source:"/img/p2.jpg"
                }



            }

            Rectangle
            {
                border.width: 1
                id:tekst
                width: parent.width
                color: "transparent"

                height: parent.height/3

                anchors.left: parent.left
                anchors.top: obraz.bottom
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.leftMargin: 25
                anchors.rightMargin: 40
                anchors.topMargin: 15
                anchors.bottomMargin: 20

                Text
                {
                    id:tresc
                    color: "#FFFFFF"
                    anchors.fill: parent
                    text:"Lorem ipsum dolor sit amet enim. Etiam ullamcorper.Suspendisse a pellentesque dui, non felis.Maecenas malesuada elit lectus felis,malesuada ultricies. Curabitur et ligula.Ut molestie a, ultricies porta urna.Vestibulum commodo volutpat a, convallis ac,laoreet enim. Phasellus fermentumin, dolor. Pellentesque facilisis. Nulla imperdiet sit amet magna.Vestibulum dapibus,maris nec malesuada fames ac turpis velit, rhoncus eu, luctus etinterdum adipiscing wisi."
                    anchors.rightMargin: 10
                    anchors.bottomMargin: 10
                    anchors.leftMargin: 10
                    anchors.topMargin: 10
                    elide: Text.ElideMiddle
                    renderType: Text.QtRendering
                    font.weight: Font.Light
                    font.pointSize: 17
                    font.family: loader_font.name
                    fontSizeMode: Text.Fit
                    textFormat: Text.RichText
                    verticalAlignment: Text.AlignTop
                    horizontalAlignment: Text.horizontalCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere



                }

            }
        }

        Rectangle
        {
            id:strona_prawa
            width: parent.width/2
            height: parent.height
            border.width: 1
            color: "transparent"
            anchors.right: parent.right
            anchors.left: strona_lewa.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.leftMargin: 30
            anchors.rightMargin: 20

            Rectangle
            {
                id: eq
                width: parent.width
                height: parent.height/3
                border.width: 1
                color: "transparent"
                anchors.left: parent.left
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.margins: 10

                Custom_EQ
                {


                }
            }

            Rectangle
            {
                id: diag
                width: parent.width
                height: parent.height/2
                color: "transparent"
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10
                anchors.bottomMargin: 20

                Rectangle
                {
                    id:option_1
                    color:"transparent"
                    border.width: 1
                    width:parent.width/2
                    height: parent.height/2
                    anchors.top: parent.top
                    anchors.left: parent.left

                    Text
                    {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: "Go Stage_1";
                        color:m_1.containsMouse ? "#808080" : "white"
                        elide: Text.ElideMiddle
                        renderType: Text.QtRendering
                        font.weight: Font.Light
                        font.pointSize: 17
                        font.family: loader_font.name
                        fontSizeMode: Text.Fit
                        textFormat: Text.RichText
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.horizontalCenter

                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere


                        MouseArea
                        {
                            id:m_1
                            anchors.fill: parent
                            hoverEnabled: true
                            onClicked:
                            {
                                parent.color = "#808080"
                                fade_in.start()
                                t1.aaa = "nn.qml"
                                t1.start()
                                next.play()
                            }

                        }
                    }
                }

                Rectangle
                {
                    id:option_2
                    width:parent.width/2
                    height: parent.height/2
                    anchors.top: parent.top
                    anchors.right: parent.right
                    color:"transparent"
                    border.width: 1
                    Text
                    {

                        anchors.fill: parent
                        anchors.margins: 5
                        text: "Dead End";
                        color:m_2.containsMouse ? "#808080" : "white"
                        elide: Text.ElideMiddle
                        renderType: Text.QtRendering
                        font.weight: Font.Light
                        font.pointSize: 17
                        font.family: loader_font.name
                        fontSizeMode: Text.Fit
                        textFormat: Text.RichText
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignJustify
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                        MouseArea
                        {
                            anchors.fill: parent
                            id:m_2
                            hoverEnabled: true
                            onClicked:
                            {
                                parent.color = "#808080"
                                t1.aaa = "menu.qml"
                                t1.start()
                                fade_in.start()
                                next.play()
                            }


                        }
                    }
                }
                Rectangle
                {
                    id:option_3
                    width:parent.width/2
                    height: parent.height/2
                    anchors.bottom: parent.bottom
                    anchors.left: parent.left
                    color:"transparent"
                    border.width: 1
                    Text
                    {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: "Optional Item";
                        color:m_3.containsMouse ? "#808080" : "white"
                        elide: Text.ElideMiddle
                        renderType: Text.QtRendering
                        font.weight: Font.Light
                        font.pointSize: 17
                        font.family: loader_font.name
                        fontSizeMode: Text.Fit
                        textFormat: Text.RichText
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignJustify
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                        MouseArea
                        {
                            id:m_3
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked:
                            {
                                parent.color = "#808080"

                                MyScript.pick(i_i2);

                            }

                        }

                    }
                }
                /*Rectangle
                {
                    id:option_4
                    width:parent.width/2
                    height: parent.height/2
                    anchors.bottom: parent.bottom
                    anchors.right: parent.right
                    color:"transparent"
                    border.width: 1
                    Text
                    {
                        anchors.fill: parent
                        anchors.margins: 5
                        text: "Option 4";

                        color:m_4.containsMouse ? "#808080" : "white"
                        elide: Text.ElideMiddle
                        renderType: Text.QtRendering
                        font.weight: Font.Light
                        font.pointSize: 17
                        font.family: loader_font.name
                        fontSizeMode: Text.Fit
                        textFormat: Text.RichText
                        verticalAlignment: Text.AlignTop
                        horizontalAlignment: Text.AlignJustify
                        wrapMode: Text.WrapAtWordBoundaryOrAnywhere

                        MouseArea
                        {
                            id:m_4
                            anchors.fill: parent
                            hoverEnabled: true

                            onClicked:
                            {



                            }

                        }
                    }
                }*/
            }
        }
    }

    Rectangle
    {
        id: fade_out
        anchors.fill: parent
        color: "black"

        ParallelAnimation
        {
            id:fade
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



