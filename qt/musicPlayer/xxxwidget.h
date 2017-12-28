#ifndef XXXWIDGET_H
#define XXXWIDGET_H

#include <QWidget>

namespace Ui {
class XXXWidget;
}

class XXXWidget : public QWidget
{
    Q_OBJECT

public:
    explicit XXXWidget(QWidget *parent = 0);
    ~XXXWidget();

private:
    Ui::XXXWidget *ui;
};

#endif // XXXWIDGET_H
