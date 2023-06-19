import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        // (1) identifier
        id: thisLabel
        // (2) set x- and y-position
        x: 24; y: 16
        // (3) bind height to 2 * width 【属性绑定】
        width: parent.width/2
        height: 2 * width
        // (4) custom property
        property int times: 24
        // (5) property alias 别名
        property alias anotherTimes: thisLabel.times
        // (6) set text appended by value
        text: "Greetings " + times
        // (7) font is a grouped property 组属性
        font.family: "Ubuntu"
        font.pixelSize: 24
        // (8) KeyNavigation is an attached property ？
        //KeyNavigation.tab: otherLabel
        // (9) signal handler for property changes 属性改变会激发信号，下面是处理该信号的绑定
        onHeightChanged: console.log('height:', height)
        // focus is neeed to receive key events 是否接收键盘的事件
        focus: false
        // change color based on focus value
        color: focus?"green":"black"
    }
    Text {
        id: label
        x: 24; y: 50
        // custom counter property for space presses
        property int spacePresses: 0
        text: "Space pressed: " + spacePresses + " times"
        // (1) handler for text changes
        onTextChanged: console.log("text changed to:", text)
        // need focus to receive key events
        focus: true
        // (2) handler with some JS
        Keys.onSpacePressed: {
            increment()
        }
        // clear the text on escape 【属性绑定】关键，按下Esc后，text的赋值操作会将属性的绑定清空！
        Keys.onEscapePressed: {
            label.text = ''
        }
        // (3) a JS function
        function increment() {
            spacePresses = spacePresses + 1
        }
    }

    Rectangle {
        id: rect1
        x: 12; y: 120
        width: 76; height: 96
        color: "lightsteelblue"
        MouseArea {
            id: area
            width: parent.width
            height: parent.height
            onClicked: rect2.visible = !rect2.visible
        }
    }
    Rectangle {
        id: rect2
        x: 112; y: 120
        width: 76; height: 96
        border.color: "lightsteelblue"
        border.width: 4
        radius: 8
    }
    Rectangle {
        id: rect3
        x: 212; y: 120
        width: 176; height: 96
        gradient: Gradient {
            GradientStop { position: 0.0; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "slategray" }
        }
        border.color: "slategray"
    }

    Text {
        id:t2
        x:250;y:300
        width: 40; height: 50
        text: 'A very long text'
        font.pointSize: 20
        // '...' shall appear in the middle
        //elide: Text.ElideMiddle
        // red sunken text styling
        styleColor: '#FF4444'
        // align text to the top
        verticalAlignment: Text.AlignTop
        // only sensible when no elide mode
        // wrapMode: Text.WordWrap
    }

    //自定义按钮
    Button{
        id:btn
        x:250;y:250
        text: "my button"
        onClicked: {
            t2.text = "hello button"
        }
    }

    //定位元素
    Column{
        id:col
        anchors.bottom:
    }
}

