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

    //qtcreator�п�ֱ�Ӵ�qml�ļ����б༭
    m_pquickWidget->setSource(QUrl("qrc:/test.qml"));

    //����ǰ��������Ϊqml�������ԣ�����qml��ִ�вۺ�����ע���źŵĶ����Сд����
    m_pquickWidget->rootContext()->setContextProperty("myWidget", this);

    //ͨ��setLayout��qmlҳ�����õ�widget����ʾ
    m_pquickWidget->setLayout(m_layout);

    //qml�źţ�c++��
    connect((QObject*)m_pquickWidget->rootObject(), SIGNAL(btnClicked()),this, SLOT(slotBtnClicked()));
    //c++�źţ�qml��
    
    //qml״̬�ı��ź�
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

    //��ʱ״̬�Ѿ���Ready
    QQuickWidget::Status st = m_pquickWidget->status();

    //rootObject()��������Rectangle���󣬿���ͨ��QObject�޸����ԣ�Ҳ��ͨ��QQuickItem��Ĭ�Ϻ����޸�����
    ((QObject*)m_pquickWidget->rootObject())->setProperty("height", 500);
    m_pquickWidget->rootObject()->setWidth(400);

    //�޸�qmlԪ�ص����ԣ�ͨ����qml�����objectName:"����"�����ʣ��ǵü�����
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
