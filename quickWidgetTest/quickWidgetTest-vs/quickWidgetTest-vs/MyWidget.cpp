#include <qmessagebox.h>
#include <QtQuick/qquickitem.h>
#include <QtQml/qqmlcontext.h>
#include "MyWidget.h"

CMyWidget::CMyWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    m_layout = new QVBoxLayout(this);

    m_pquickWidget = new QQuickWidget(this);

    //qtcreator中可直接打开qml文件进行编辑
    m_pquickWidget->setSource(QUrl("qrc:/test.qml"));

    //将当前对象设置为qml引擎属性，方便qml中执行槽函数，注意信号的定义大小写问题
    m_pquickWidget->rootContext()->setContextProperty("myWidget", this);

    //通过setLayout将qml页面设置到widget中显示
    m_pquickWidget->setLayout(m_layout);

    //qml信号，c++槽
    connect((QObject*)m_pquickWidget->rootObject(), SIGNAL(btnClicked()),this, SLOT(slotBtnClicked()));
    //c++信号，qml槽
    
    //qml状态改变信号
    connect(m_pquickWidget, &QQuickWidget::statusChanged, [&](QQuickWidget::Status status) {
        if (status == QQuickWidget::Ready) {
        }
        else if (status == QQuickWidget::Loading)
        {
        }
        else if (status == QQuickWidget::Error)
        {
        }
        else
        {
        }
    });

    //此时状态已经是Ready
    QQuickWidget::Status st = m_pquickWidget->status();

    //rootObject()是最外层的Rectangle对象，可以通过QObject修改属性，也可通过QQuickItem的默认函数修改属性
    ((QObject*)m_pquickWidget->rootObject())->setProperty("height", 500);
    m_pquickWidget->rootObject()->setWidth(400);

    //修改qml元素的属性，通过在qml中添加objectName:"名称"来访问，记得加引号
    QList<QObject*> list = ((QObject*)m_pquickWidget->rootObject())->findChildren<QObject*>();
    QString strName;
    foreach(QObject* child, list) {
        /*QQuickItem* item = qobject_cast<QQuickItem*>(child);*/
        if (child) {
            strName = child->objectName();
        }
    }
    m_pquickWidget->show();
}

CMyWidget::~CMyWidget()
{}

void CMyWidget::slotBtnClicked()
{
    QObject *myTextItem = ((QObject*)m_pquickWidget->rootObject())->findChild<QObject*>("t");
    myTextItem->setProperty("text", "button clicked!");
    emit signalWidget();
}
