import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Window 2.2
import QtMultimedia 5.8



Window {

    id:window_main
    visible: true
    width: 1024
    height: 640
    //visibility: "FullScreen"
    title: qsTr("The Stories")

    property url source_zoom_image
    property url source_page_zoom



    //eq_data

    //ustawianie tła w eq
    property color c_s1: "transparent"
    property color c_s2: "transparent"
    property color c_s3: "transparent"
    property color c_s4: "transparent"

    //sprawdzanie czy slot w eq jest wolny
    property bool i_s1: true
    property bool i_s2: true
    property bool i_s3: true
    property bool i_s4: true


    Item
    {
        id:i_i1
        property int position
        property bool in_eq: false
        property bool can_get: true
        property url source
        property bool used: false
        property color cc: "red"
    }

    Item
    {
        id:i_i2
        property int position
        property bool in_eq: false
        property bool can_get: true
        property url source
        property bool used: false
        property color cc: "yellow"
    }





    FontLoader
    {
        id: loader_font
        source:"/fonts/cr.ttf"
    }
    Audio
    {
        id: playMusic
        source: "/mp3/2.mp3"
        autoPlay: true
        volume: 0.04
    }

    Timer
    {
        id:t1
        interval: 1000;
        running: false;
        property url aaa
        onTriggered:
        {
            next_page.source = aaa;

        }
    }

    Loader
    {
        id:next_page
        anchors.fill: parent
        active: true
        source: "menu.qml"
    }






}

