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
    void signalWidget(); //定义的时候必须小写开头！！Qml中On+大写开头

private slots:
    void slotBtnClicked();

private:
    Ui::CMyWidgetClass ui;

    QVBoxLayout * m_layout;
    QQuickWidget *m_pquickWidget;
};
