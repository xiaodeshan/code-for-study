#include "xxxwidget.h"
#include "ui_xxxwidget.h"

XXXWidget::XXXWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::XXXWidget)
{
    ui->setupUi(this);
}

XXXWidget::~XXXWidget()
{
    delete ui;
}
