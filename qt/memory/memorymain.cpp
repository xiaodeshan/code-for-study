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

QStringList* MemoryMain::getAllCardNum(QString path)
{
    QDir* dir = new QDir(path);
    QStringList* list = new QStringList();
    if (!dir->exists()){
        return nullptr;
    }

    QFileInfoList fileinfoList = dir->entryInfoList();
    for (int i = 0; i < fileinfoList.size(); ++i) {
        QFileInfo fileInfo = fileinfoList.at(i);
        list->append(fileInfo.baseName());
    }
    return list;
}

QStringList *MemoryMain::getAllCardName(QString path)
{
    QFile file(path);
    QStringList* list = new QStringList();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return nullptr;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        list->append(line);

        qDebug() << line;
    }

    return list;
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
    cardNums = getAllCardNum(CARD_PATH);
    cardNames = getAllCardName(CARD_NAME_PATH);
    initRand();
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
            randShow();
        }
        break;
    default:
        break;
    }
}

void MemoryMain::randShow()
{
    int randID = getRandCardNum(getNumSize());

    currPath = getPathByid(randID);
    currNumText = cardNums->at(randID);
    currID = randID;

    QString cardName = cardNames->at(randID);
    showImageAndLabel(currPath, currNumText + " " + cardName);
}




