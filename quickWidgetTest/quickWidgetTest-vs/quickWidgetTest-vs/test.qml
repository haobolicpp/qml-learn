import QtQuick 2.3
import QtQuick.Controls 2.0

Rectangle {
    id:root
    objectName: "root"
    width: 200
    height: 150
    color: "#e8d0d0"

    signal btnClicked()

    Connections{
        target: myWidget
        onSignalWidget:{
            t2.text = "onSignalWidget"
        }
    }

    Button{
        id : btn
        objectName:"btn"
        text: "按钮"
        onClicked: {
            btnClicked()
        }

    }

    Text {
        id:t
        height: 28
        objectName: "t"
        anchors.top: btn.bottom
        text: "Hello, World!"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
    }

    Rectangle{
        id:rect
        objectName: "rect"
        anchors.top : t.bottom
        width: 100
        height: 50
        color: "yellow"
    }

    Text {
        id:t2
        height: 28
        objectName: "t2"
        anchors.top: rect.bottom
        text: "123!"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 12
    }

    TextEdit{
        id:te
        objectName: "te"
        anchors.top: t2.bottom
    }
	
}
