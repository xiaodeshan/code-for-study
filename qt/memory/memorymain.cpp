#include "memorymain.h"
#include "ui_memorymain.h"

MemoryMain::MemoryMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryMain)
{
    ui->setupUi(this);

    init();

    randShow();
}

MemoryMain::~MemoryMain()
{
    delete ui;
}


void MemoryMain::getAllCardInfo(QString path)
{
    QFile file(path);
    cardNums = new QStringList();
    cardNames = new QStringList();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();

        line.replace('\t', ' ');

        QStringList listLine = line.split(' ');
        QString name = listLine.at(0);
        QString num = listLine.at(listLine.size() - 1);

        qDebug() << "line " << line << " name = " << name << " num = " << num;
        cardNums->append(num);
        cardNames->append(name);
        //qDebug() << line;
    }
}

int MemoryMain::getRandCardNum(int size)
{
    return rand() % size;
}

void MemoryMain::initRand()
{
    srand(time(0));
}

QString MemoryMain::getPathByid(int id)
{
    QString path = CARD_PATH + cardNums->at(id) + ".png";
    return path;
}

void MemoryMain::showImageAndLabel(QString path, QString text)
{
    qDebug() << "path " << path << " text" << text;
    if(!path.isEmpty()){
        QImage image(path);
        ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    }

    if(!text.isEmpty() && isShowNum){
        ui->numLabel->setText(text);
    }

    if(!isShowNum){
        ui->numLabel->setText("");
    }
}

void MemoryMain::init()
{
    isShowNum = false;
    getAllCardInfo(CARD_NAME_PATH);
    initRand();
    initMenuBar();
    initBackground();
}

int MemoryMain::getNumSize()
{
    if(cardNums == nullptr)
        return 0;
    return cardNums->size();
}

void MemoryMain::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Down:
    case Qt::Key_Right:
        if(!isShowNum){
            isShowNum = true;
            QString cardName = cardNames->at(currID);
            showImageAndLabel(currPath, currNumText + " " + cardName);
        }else{
            isShowNum = false;
            backStack.push(currID);
            randShow();
            qDebug() << "id input stack" << currID;
        }
        break;
    case Qt::Key_Left:
        if(!isShowNum){
            //回退到上一个
            if(!backStack.isEmpty()){
                int last = backStack.pop();
                qDebug() << "id out stack" << last;
                updateByID(last);
            }else{
                QMessageBox::information(this, "提示", "已经是第一个了",
                                         QMessageBox::Ok);
            }
        }else{
            ui->numLabel->setText("");
            isShowNum = false;
        }
        break;
    default:
        break;
    }
}

void MemoryMain::randShow()
{
    int randID = getRandCardNum(getNumSize());
    updateByID(randID);
}

void MemoryMain::updateByID(int id)
{
    currPath = getPathByid(id);
    qDebug() << "id = " << id << " path = " + currPath;
    currNumText = cardNums->at(id);
    currID = id;

    QString cardName = cardNames->at(id);
    showImageAndLabel(currPath, currNumText + " " + cardName);

    qDebug() << "id = " << id << " path = " + currPath;
}

void MemoryMain::initMenuBar()
{
    menuBar = new QMenuBar(this);
    //menuBar->setAttribute();

    QMenu* fileMenu = menuBar->addMenu(tr("&设置"));
    fileMenu->addAction("模式");
}

void MemoryMain::initBackground()
{
    QPalette pal(this->palette());

    //设置背景黑色
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}




