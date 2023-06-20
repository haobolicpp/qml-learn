import QtQuick 2.0

//一个按钮，考虑长宽、颜色、边界颜色、文字导出，按钮响应
//这里Rectangle控制按钮区域，Text控制按钮上的颜色
Item {
    id:root
    width:100
    height:50
    property string text:"" //定义一个text，这样父元素可以绑定这个text

    Rectangle{
        id:button
        color: "#ec9a7d"
        border.color: "#e52323"
        anchors.fill: parent //将该元素填充到父元素的边界内
        Text {
            id: label
            //verticalAlignment: Text.AlignVCenter
            //horizontalAlignment: Text.AlignHCenter
            anchors.centerIn: parent //在父元素中居中，上面两个不起作用！
            text: root.text //【关键】将根元素的text放到这里显示！
        }
    }

    MouseArea{
        anchors.fill: parent //鼠标感知区域为整个父元素
        onClicked: {
           root.clicked()
        }
    }
    signal clicked() //自定义点击信号
}
