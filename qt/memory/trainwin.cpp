#include "trainwin.h"

TrainWin::TrainWin(QWidget *parent) : QWidget(parent)
{
    init();
}

void TrainWin::init()
{
    srand(time(0));
    initUI();
}

void TrainWin::initUI()
{
    phoneLabel = new QLabel(this);
    phoneLabel->setText(randomPhone());

    QVBoxLayout *leftLayout = new QVBoxLayout();
    phoneLabel->setFont(QFont("Times", 80, QFont::Bold));

    leftLayout->addWidget(phoneLabel, 0, Qt::AlignCenter);

    this->setLayout(leftLayout);
}

QString TrainWin::randomPhone()
{
    int i;
    char p1[14][4]={"134","135","136","137","138","139","150","151","152","157","158","159","187","188"};

    std::string phoneString = p1[rand()%14];
    for(i=3;i<11;i++)
        phoneString += rand()%10 + '0';
    return QString::fromStdString(phoneString);
}

void TrainWin::nextShow()
{
    phoneLabel->setText(randomPhone());
}
