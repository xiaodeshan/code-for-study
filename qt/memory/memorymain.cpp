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

    //学习范围
    learnNum = -1;
    fromID = -1;
}

int MemoryMain::getNumSize()
{
    if(learnNum == -1)
        return getTrueSize();
    if(mode == checkMode)
        return learnNum;
    else{
        int sizeT = getLast() - fromID + 1;
        return learnNum > sizeT ? sizeT : learnNum;
    }

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

            if((currID == getLast() && mode == studyMode) || (fromID != -1 && backStack.size() + 1 == learnNum)){
                QMessageBox::information(this, "提示", "恭喜，已经完成了学习",
                                         QMessageBox::Ok);
            }else{
                isShowNum = false;
                backStack.push(currID);

                updateByID(getNextID());
                updateStateUI();
            }
            //qDebug() << (learnNum - 1) << " " << backStack.size();
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

    QMenu* fileMenu = menuBar->addMenu(tr("&文件"));
    QAction* exitAction = fileMenu->addAction("退出");

    QMenu* settingMenu = menuBar->addMenu(tr("&设置"));
    QMenu* modeMenu = settingMenu->addMenu(tr("&模式"));
    QAction* scopeMenuAction = settingMenu->addAction(tr("&学习范围"));

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
    connect(scopeMenuAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseScope()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
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
            if(fromID == -1)
                return (currID + 1) % getNumSize();
            else{
                int last = getLast();

                if(currID == last)
                    return fromID;
                return currID + 1;
            }
        }
    }else{
        return getRandCardNum(getTrueSize());
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
        int showID = currID;
        if(fromID != -1)
            showID = currID - fromID;
        QString processText = QString::number(showID + 1) + "/" + QString::number(getNumSize());

        processTextLabel->setText(processText);
        stateProcessBar->setValue(100 * (showID + 1) / getNumSize());

    }
}

int MemoryMain::getTrueSize()
{
    if(cardNums == nullptr)
        return 0;
    return cardNums->size();
}

int MemoryMain::getLast()
{
    if(fromID == -1)
        return getTrueSize() - 1;

    int last = fromID + learnNum - 1;
    if(last > getTrueSize() - 1)
        last = getTrueSize() - 1;
    return last;
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

void MemoryMain::slotChooseScope()
{
    dialog = new LearnScopeDialog(this);
    int result = dialog->exec();

    if(result){
        backStack.clear();

        if(mode == studyMode){
            learnNum = dialog->getTotal();
            fromID = dialog->getFrom() - 1;

            currID = fromID;
            updateByID(currID);
            updateStateUI();

        }else if(mode == checkMode){
            fromID = currID;
            learnNum = dialog->getTotal();
        }
    }
}




