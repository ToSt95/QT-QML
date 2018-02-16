import QtQuick 2.5

Rectangle
{
    id: root
    width: 100; height: 100
    color: "white"
    border.color: "black"
    border.width: 5
    radius: 5

    signal fieldClicked

    property string imgUrl: "qrc:/IMG/blank.jpg"
    property int rowInfo
    property int columnInfo

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true

        onEntered:
        {
            root.border.color = "gray";
        }
        onExited:
        {
            root.border.color = "black";
        }
        onClicked:
        {
            root.fieldClicked();
        }
    }
    Image
    {
        id:image
        fillMode: Image.PreserveAspectFit
        smooth: true
        anchors.fill:parent
        anchors.margins: 2
        source: imgUrl
    }
}

