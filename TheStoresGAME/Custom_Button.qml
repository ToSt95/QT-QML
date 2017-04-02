import QtQuick 2.0


Rectangle
{
    id:button
    property alias source : img.source
    color: "transparent"
    Accessible.onPressAction:
    {
        button.clicked()
    }

    signal clicked

    Image
    {
        id:img
        anchors.fill: parent

    }

    MouseArea
    {
        id: mouseArea
        onClicked: parent.clicked()
        anchors.fill: parent
    }




}
