#### 1. 用c++扩展qml
`参考例程 extending-qml，`从*QQuickPaintedItem*派生一个自定义界面类，可以通过qmlRegisterType注册到qml引擎中，其中可以定义`属性、方法、信号`供qml使用。 
##### 1.1. 属性
属性定义非常简单，通过下面三个部分即可定义,qml中可直接使用
```cpp
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QColor color READ color WRITE setColor)
 
    QString name() const;
    void setName(const QString &name);
    QColor color() const;
    void setColor(const QColor &color);

private:
    QString m_name;
    QColor m_color;
```
##### 1.2. 方法
方法分为普通方法和信号，普通方法用如下定义：
```cpp
Q_INVOKABLE void clearChart();
```
在qml中可直接调用：
```qml
MouseArea {
        anchors.fill: parent
        onClicked: aPieChart.clearChart()
    }
```
信号解释来自chatgpt,问题是“qml中使用c++信号”：    
在C++类中声明信号：在你的C++类中，使用signals关键字声明一个信号。
```cpp
class MyCustomClass : public QObject
{
    Q_OBJECT
public:
    explicit MyCustomClass(QObject *parent = nullptr);

signals:
    void customSignal();
};
```
在C++类中触发信号：在适当的时机，通过调用信号来触发它。

```cpp
void MyCustomClass::triggerSignal()
{
    emit customSignal();
}
```
在QML中连接信号并处理：在QML代码中，可以连接到C++类的信号，并在信号触发时执行相应的操作。
```qml
import MyNamespace 1.0
MyCustomClass {
    id: myObject
    onCustomSignal: {
        console.log("Custom signal received!")
    }
}
```
在这个示例中，我们导入了包含自定义类型的命名空间，并创建了一个名为myObject的自定义类型对象。我们使用onCustomSignal语法连接到了customSignal信号，并在信号触发时打印消息。

请注意，在连接信号时，信号名称需要遵循Qt的命名约定，即在信号名称前面加上on前缀。

通过以上步骤，你可以在QML中使用C++信号并进行相应的处理。当C++类触发信号时，QML代码中连接的信号处理函数将被执行。

##### 1.3. 绑定【重要！！】
通过属性绑定，可以实现QML与C++之间的属性交互，使得数据在两者之间保持同步。
以下摘录chatgpt“qml调用c++时，属性绑定如何实现”的回答：

在QML中调用C++时，可以通过属性绑定将QML中的属性与C++对象的属性进行关联。属性绑定可以实现数据的双向绑定，使得在QML中修改属性时能够自动更新对应的C++对象属性，反之亦然。
以下是实现属性绑定的步骤：
在C++类中声明属性：在你的C++类中，使用Q_PROPERTY宏声明一个属性。
```cpp
class MyCustomClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
public:
    explicit MyCustomClass(QObject *parent = nullptr);

    QString getText() const;
    void setText(const QString& newText);

signals:
    void textChanged();

private:
    QString m_text;
};
```
在C++类中实现属性的访问函数：在C++类中实现属性的读取和写入函数。
```cpp
QString MyCustomClass::getText() const
{
    return m_text;
}

void MyCustomClass::setText(const QString& newText)
{
    if (m_text != newText) {
        m_text = newText;
        emit textChanged();
    }
}
```
在QML中绑定属性：在QML代码中，可以使用属性绑定将QML中的属性与C++对象的属性进行关联。

```qml
import MyNamespace 1.0

MyCustomClass {
    id: myObject
}

Text {
    text: myObject.text // 将QML中的text属性与C++对象的text属性进行绑定
}

TextField {
    text: myObject.text // 将C++对象的text属性与QML中的text属性进行双向绑定
}
```
在这个示例中，我们首先导入了包含自定义类型的命名空间，并创建了一个名为myObject的自定义类型对象。然后，我们使用属性绑定将Text组件的text属性与C++对象的text属性进行绑定，这意味着当C++对象的text属性发生变化时，Text组件的文本内容也会自动更新。**同样地，我们将TextField组件的text属性与C++对象的text属性进行双向绑定，这意味着当在QML中修改TextField的文本内容时，C++对象的text属性也会相应更新。**

##### 1.4. 自定义属性
c++类中的属性，可自定义，比如：
```cpp
Q_PROPERTY(PieSlice* pieSlice READ pieSlice WRITE setPieSlice)
Q_PROPERTY(QQmlListProperty<PieSlice> slices READ slices)
```
main函数中需要将自定义的类进行注册：
```cpp
qmlRegisterType<PieSlice>("Charts", 1, 0, "PieSlice");
```
##### 1.5. 插件
可以通过qtcreator的新建项目向导构建qml插件。
那么如何导入插件进行使用呢？目前看到有两种方法：
```cpp
//第一种是qt示例中的，利用addImportPath将插件目录添加到qml引擎查找模块的目录
view.engine()->addImportPath(app.applicationDirPath() + "/../PlugIns");
//qml文件中直接import Charts 1.0就可以了
```

```cpp
//第二种方法
qmlRegisterType<MyPlugin>("MyPlugin", 1, 0, "MyPlugin");
//qml文件中直接import Charts 1.0就可以了，这种方法还未测试，dll库放哪里也需要验证
```