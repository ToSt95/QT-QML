import QtQuick 2.0
import QtQuick.Layouts 1.3



GridLayout
{

    id: grid
    anchors.centerIn: parent
    rowSpacing: 40
    columns: 4



    Rectangle
    {
        id: slot_1
        height: 60
        width: 60
        border.color: "white"
        border.width: 1
        color: c_s1


    }
    Rectangle
    {
        id: slot_2
        height: 60
        width: 60
        border.color: "white"
        border.width: 1
        color: c_s2
    }
    Rectangle
    {
        id: slot_3
        height: 60
        width: 60
        border.color: "white"
        border.width: 1
        color: c_s3
    }
    Rectangle
    {
        id: slot_4
        height: 60
        width: 60
        border.color: "white"
        border.width: 1
        color: c_s4
    }

}




