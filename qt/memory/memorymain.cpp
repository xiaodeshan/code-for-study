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
            showImageAndLabel(currPath, currNumText);
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
    showImageAndLabel(currPath, currNumText);
}




