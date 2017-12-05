#include "showwin.h"

ShowWin::ShowWin(QWidget *parent) : QWidget(parent)
{
    initUi();
}

void ShowWin::initUi()
{
    QVBoxLayout *leftLayout = new QVBoxLayout();

    imageLabel = new QLabel(this);
    numLabel = new QLabel(this);
    numLabel->setFont(QFont("Times", 80, QFont::Bold));

    leftLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(numLabel, 0, Qt::AlignCenter);
    leftLayout->setContentsMargins(0, 0, 0, 30);

    this->setLayout(leftLayout);
}

void ShowWin::showImageAndLabel(QString path, QString text, bool ispic)
{
    if(ispic){
        numLabel->setFont(QFont("Times", 30, QFont::Bold));
    }else{
        numLabel->setFont(QFont("Times", 80, QFont::Bold));
    }
    //qDebug() << "path " << path << " text" << text;
    if(!path.isEmpty() && ispic){
        imageLabel->show();
        QImage image(path);
        imageLabel->setPixmap(QPixmap::fromImage(image));
    }

    if(!text.isEmpty()){
        numLabel->setText(text);
    }

    if(!ispic){
        imageLabel->hide();
        numLabel->setFont(QFont("Times", 80, QFont::Bold));
    }
}
