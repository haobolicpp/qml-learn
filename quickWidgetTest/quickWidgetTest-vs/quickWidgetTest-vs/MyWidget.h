#pragma once

#include <QtWidgets/QWidget>
#include "ui_MyWidget.h"

class CMyWidget : public QWidget
{
    Q_OBJECT

public:
    CMyWidget(QWidget *parent = nullptr);
    ~CMyWidget();

private:
    Ui::CMyWidgetClass ui;
};
