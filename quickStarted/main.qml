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
}
