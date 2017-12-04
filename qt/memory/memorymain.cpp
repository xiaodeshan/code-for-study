#include "memorymain.h"

MemoryMain::MemoryMain(QWidget *parent) :
    QWidget(parent)
{
    init();

    startProg();
}

MemoryMain::~MemoryMain()
{
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
        imageLabel->setPixmap(QPixmap::fromImage(image));
    }

    if(!text.isEmpty() && isShowNum){
        numLabel->setText(text);
    }

    if(!isShowNum){
        numLabel->setText("");
    }
}

void MemoryMain::init()
{
    initUI();
    isShowNum = false;
    readAllCardInfoFromFile(CARD_NAME_PATH);
    initSrand();
    initMenuBar();
    initBackground();
    justStart = true;
    mode = studyMode;
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
            if(currID == getNumSize() - 1 && mode == studyMode){
                QMessageBox::information(this, "提示", "恭喜，已经完成了学习",
                                         QMessageBox::Ok);
            }else{
                isShowNum = false;
                backStack.push(currID);

                updateByID(getNextID());
                updateStateUI();
            }
        }
        break;
    case Qt::Key_Left:
        if(!isShowNum){
            //回退到上一个
            if(!backStack.isEmpty()){
                int last = backStack.pop();
                //qDebug() << "id out stack" << last;
                updateByID(last);
                updateStateUI();
            }else{
                QMessageBox::information(this, "提示", "已经是第一个了",
                                         QMessageBox::Ok);
            }
        }else{
            numLabel->setText("");
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

void MemoryMain::initUI()
{
    widgetLayout = new QHBoxLayout();
    QVBoxLayout *leftLayout = new QVBoxLayout();

    imageLabel = new QLabel(this);
    numLabel = new QLabel(this);
    numLabel->setFont(QFont("Times", 30, QFont::Bold));

    leftLayout->addWidget(imageLabel, 0, Qt::AlignCenter);
    leftLayout->addWidget(numLabel, 0, Qt::AlignCenter);

    //学习模式的进度条
    stateLayout = new QVBoxLayout();
    rightWidget = new QWidget(this);

    QLabel *stateTextLabel = new QLabel("学习进度");
    stateTextLabel->setFont(QFont("Times", 30, QFont::Bold));
    processTextLabel = new QLabel("0/0");
    processTextLabel->setFont(QFont("Times", 20, QFont::Bold));
    stateProcessBar = new QProgressBar(this);
    stateProcessBar->setMaximum(100);
    stateProcessBar->setMinimum(0);
    stateProcessBar->setValue(0);
    stateProcessBar->setTextVisible(false);

    stateLayout->addWidget(stateTextLabel, 0, Qt::AlignTop);
    stateLayout->addWidget(processTextLabel, 0, Qt::AlignTop);
    stateLayout->addWidget(stateProcessBar, 0, Qt::AlignTop);
    stateLayout->addStretch();
    stateLayout->setContentsMargins(20, 20, 20, 0);

    rightWidget->setLayout(stateLayout);

    widgetLayout->addLayout(leftLayout, 4);
    widgetLayout->addWidget(rightWidget, 1);

    this->setLayout(widgetLayout);
}

int MemoryMain::getNextID()
{
    if(mode == studyMode){
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
    updateStateUI();
}

void MemoryMain::updateStateUI()
{
    if(mode == studyMode){
        QString processText = QString::number(currID + 1) + "/" + QString::number(getNumSize());
        processTextLabel->setText(processText);
        stateProcessBar->setValue(100 * (currID + 1) / getNumSize());
    }
}

void MemoryMain::slotChooseStydyMode(bool triggle)
{
    if(triggle){
        mode = studyMode;
        rightWidget->show();

        updateStateUI();
    }

}

void MemoryMain::slotChooseCheckMode(bool triggle)
{
    if(triggle){
        rightWidget->hide();
        mode = checkMode;
    }
}




