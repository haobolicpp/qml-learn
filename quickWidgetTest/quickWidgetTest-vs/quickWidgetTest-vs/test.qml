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

    Slider {
        width: 500 
		MouseArea {
                id: mouseArea
                anchors.fill: parent
                propagateComposedEvents: true
                onReleased: {
                    console.log("clicked blue")
					mouse.accepted = false
                }
            }
    }

	
}
