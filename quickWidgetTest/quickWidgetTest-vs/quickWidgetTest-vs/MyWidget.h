#pragma once

#include <QtWidgets/QWidget>
#include <QtQuickWidgets/qquickwidget.h>
#include <QVBoxLayout>
#include "ui_MyWidget.h"

class CMyWidget : public QWidget
{
    Q_OBJECT

public:
    CMyWidget(QWidget *parent = nullptr);
    ~CMyWidget();

signals:
    void signalWidget(); //�����ʱ�����Сд��ͷ����Qml��On+��д��ͷ

private slots:
    void slotBtnClicked();

private:
    Ui::CMyWidgetClass ui;

    QVBoxLayout * m_layout;
    QQuickWidget *m_pquickWidget;
};
