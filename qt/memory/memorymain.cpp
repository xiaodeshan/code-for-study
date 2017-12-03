#include "memorymain.h"
#include "ui_memorymain.h"

MemoryMain::MemoryMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemoryMain)
{
    ui->setupUi(this);

    init();

    startProg();
}

MemoryMain::~MemoryMain()
{
    delete ui;
}


void MemoryMain::readAllCardInfoFromFile(QString path)
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

        //qDebug() << "line " << line << " name = " << name << " num = " << num;
        cardNums->append(num);
        cardNames->append(name);
        //qDebug() << line;
    }
}

int MemoryMain::getRandCardNum(int size)
{
    return rand() % size;
}

void MemoryMain::initSrand()
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
    //qDebug() << "path " << path << " text" << text;
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
    readAllCardInfoFromFile(CARD_NAME_PATH);
    initSrand();
    initMenuBar();
    initBackground();
    justStart = true;
    mode = stydyMode;
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

            updateByID(getNextID());
            //qDebug() << "id input stack" << currID;
        }
        break;
    case Qt::Key_Left:
        if(!isShowNum){
            //回退到上一个
            if(!backStack.isEmpty()){
                int last = backStack.pop();
                //qDebug() << "id out stack" << last;
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

void MemoryMain::updateByID(int id)
{
    currPath = getPathByid(id);
    //qDebug() << "id = " << id << " path = " + currPath;
    currNumText = cardNums->at(id);
    currID = id;

    QString cardName = cardNames->at(id);
    showImageAndLabel(currPath, currNumText + " " + cardName);

    //qDebug() << "id = " << id << " path = " + currPath;
}

void MemoryMain::initMenuBar()
{
    menuBar = new QMenuBar(this);
    //menuBar->setAttribute();

    QMenu* fileMenu = menuBar->addMenu(tr("&设置"));
    QMenu* modeMenu = fileMenu->addMenu(tr("&模式"));

    QAction *stydyModeAction = new QAction("学习模式");
    QAction *checkModeAction = new QAction("检查模式");
    stydyModeAction->setCheckable(true);
    checkModeAction->setCheckable(true);

    QActionGroup* modeActionGroup = new QActionGroup(this);
    modeActionGroup->addAction(stydyModeAction);
    modeActionGroup->addAction(checkModeAction);
    stydyModeAction->setChecked(true);
    modeActionGroup->setExclusive(true);

    modeMenu->addActions(modeActionGroup->actions());
    //fileMenu->addAction("模式");

    connect(stydyModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseStydyMode(bool)));
    connect(checkModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseCheckMode(bool)));
}

void MemoryMain::initBackground()
{
    QPalette pal(this->palette());

    //设置背景黑色
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

int MemoryMain::getNextID()
{
    if(mode == stydyMode){
        if(justStart){
            justStart = false;
            return 0;
        }else{
            return (currID + 1) % getNumSize();
        }
    }else{
        return getRandCardNum(getNumSize());
    }
}

void MemoryMain::startProg()
{
    updateByID(getNextID());
}

void MemoryMain::slotChooseStydyMode(bool triggle)
{
    if(triggle)
        mode = stydyMode;
}

void MemoryMain::slotChooseCheckMode(bool triggle)
{
    if(triggle)
        mode = checkMode;
}




