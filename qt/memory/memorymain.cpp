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

QString MemoryMain::getPicPathByid(int id)
{
    QString path = CARD_PATH + cardNums->at(id) + ".png";
    return path;
}

void MemoryMain::showImageAndLabel(QString path, QString text, bool ispic)
{
    getShowWin()->showImageAndLabel(path, text, ispic);
}

void MemoryMain::init()
{
    widgetLayout = new QHBoxLayout();
    initUI();
    isShowPic = false;
    readAllCardInfoFromFile(CARD_NAME_PATH);
    initSrand();
    initMenuBar();
    initBackground();
    justStart = true;
    mode = studyMode;
    initScope();
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
        switch (mode) {
        case studyMode:
        case checkMode:
            if(!isShowPic){
                isShowPic = true;
                showImageAndLabel(currPath, currNumText + " " + cardNames->at(currID), isShowPic);
            }else{

                if((currID == getLast() && mode == studyMode) || (fromID != -1 && backStack.size() + 1 == learnNum)){
                    qDebug() << "rr";
                    getStateWin()->stopTimerWin();
                    QString msg = "Congratulations, You've finished the study.\nDid you want to continue study?";
                    //msg += "cost " + QString::number(getStateWin()->getTimerWinSec()) + " seconds";

                    int choose = QMessageBox::information(this, "Info", msg,
                                                          QMessageBox::Ok, QMessageBox::Cancel);

                    if(choose == QMessageBox::Ok){
                        getStateWin()->startTimeWin();
                        resetLearn();
                    }

                }else{
                    isShowPic = false;
                    showImageAndLabel(currPath, currNumText + " " + cardNames->at(currID), isShowPic);
                    backStack.push(currID);
                    updateByID(getNextID());
                    updateStateUI();
                }
            }
            break;
        case trainMode:
            getTrainWin()->nextShow();
            break;
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_Up:
        switch (mode) {
        case studyMode:
        case checkMode:
            if(!isShowPic){
                //回退到上一个
                if(!backStack.isEmpty()){
                    int last = backStack.pop();
                    updateByID(last);
                    updateStateUI();
                }else{
                    QMessageBox::information(this, "提示", "已经是第一个了",
                                             QMessageBox::Ok);
                }
            }else{
                isShowPic = false;
                updateByID(currID);
            }
            break;
        case trainMode:
            bool ok = getTrainWin()->lastShow();
            if(!ok){
                QMessageBox::information(this, "提示", "已经是第一个了",
                                         QMessageBox::Ok);
            }
            break;
        }
        break;
    default:
        break;
    }

}

void MemoryMain::updateByID(int id)
{
    currPath = getPicPathByid(id);
    currNumText = cardNums->at(id);
    currID = id;

    showImageAndLabel(currPath, currNumText, isShowPic);
}

void MemoryMain::initMenuBar()
{
    menuBar = new QMenuBar(this);

    menuBar->setFixedSize(QSize(this->width(), menuBar->height()));

    QMenu* fileMenu = menuBar->addMenu(tr("&File"));
    QAction* exitAction = fileMenu->addAction("Exit");

    QMenu* settingMenu = menuBar->addMenu(tr("&Setting"));
    QMenu* modeMenu = settingMenu->addMenu(tr("&mode"));
    QAction* scopeMenuAction = settingMenu->addAction(tr("&study scope"));

    QAction *stydyModeAction = new QAction("&stydy mode");
    QAction *checkModeAction = new QAction("&check mode");
    QAction *trainModeAction = new QAction("&train mode");
    stydyModeAction->setCheckable(true);
    checkModeAction->setCheckable(true);
    trainModeAction->setCheckable(true);

    QActionGroup* modeActionGroup = new QActionGroup(this);
    modeActionGroup->addAction(stydyModeAction);
    modeActionGroup->addAction(checkModeAction);
    modeActionGroup->addAction(trainModeAction);
    stydyModeAction->setChecked(true);
    modeActionGroup->setExclusive(true);

    modeMenu->addActions(modeActionGroup->actions());

    connect(stydyModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseStydyMode(bool)));
    connect(checkModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseCheckMode(bool)));
    connect(scopeMenuAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseScope()));
    connect(trainModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseTrainMode(bool)));
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
    //主界面
    leftWidget = new ShowWin(this);
    //学习模式的进度条
    rightWidget = new StateWin(this);
    updateLayout();
    setMinimumSize(QSize(1077, 913));

    this->resize(QSize(1077, 913));
}

void MemoryMain::initScope()
{
    //学习范围
    learnNum = -1;
    fromID = -1;
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
    }else if(mode == checkMode){
        if(fromID != -1)
            return getRandomByFromTo(fromID, toID);
        else
            return getRandCardNum(getTrueSize());
    }
    return -1;
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
        getStateWin()->updateStateUI(showID, getNumSize());
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

void MemoryMain::updateLayout()
{
    if(leftWidget != nullptr)
        widgetLayout->addWidget(leftWidget, 4);
    if(rightWidget != nullptr)
        widgetLayout->addWidget(rightWidget, 1);

    this->setLayout(widgetLayout);
}

StateWin *MemoryMain::getStateWin()
{
    return (StateWin*)(rightWidget);
}

ShowWin *MemoryMain::getShowWin()
{
    return (ShowWin*)(leftWidget);
}

TrainWin *MemoryMain::getTrainWin()
{
    return (TrainWin*)(leftWidget);
}

int MemoryMain::getNumByText(QString data)
{
    for (int i = 0; i < cardNums->size(); ++i){
        if(cardNums->at(i) == data)
            return i;
    }
    return -1;
}

void MemoryMain::resetLearn()
{
    backStack.clear();
    isShowPic = false;
    if(fromID != -1){
        learnNum = dialog->getTotal();
        currID = fromID;
    }else{
        currID = 0;
    }
    updateByID(currID);
    updateStateUI();
    getStateWin()->resetTimerWin();

}

int MemoryMain::getRandomByFromTo(int from, int to)
{
    return rand() % (to - from) + from + 1;
}

void MemoryMain::slotChooseStydyMode(bool triggle)
{
    if(triggle){
        mode = studyMode;
        leftWidget->close();
        leftWidget = new ShowWin(this);
        leftWidget->show();
        rightWidget->show();
        isShowPic = false;
        showImageAndLabel(currPath, currNumText, isShowPic);
        initScope();

        updateLayout();
        updateStateUI();
    }
}

void MemoryMain::slotChooseCheckMode(bool triggle)
{
    if(triggle){
        mode = checkMode;
        leftWidget->close();
        leftWidget = new ShowWin(this);
        leftWidget->show();
        isShowPic = false;
        initScope();

        currID = getNextID();
        updateByID(currID);

        updateLayout();
        updateStateUI();
    }
}

void MemoryMain::slotChooseTrainMode(bool triggle)
{
    if(triggle){
        //rightWidget->hide();
        getStateWin()->resetTimerWin();
        leftWidget->close();
        leftWidget = new TrainWin(this);
        leftWidget->show();
        mode = trainMode;
        updateLayout();
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
            fromID = dialog->getStartID();
            currID = fromID;
            updateByID(currID);
            updateStateUI();
            getStateWin()->resetTimerWin();
        }else if(mode == checkMode){
            currID = getNextID();
            learnNum = dialog->getTotal();
            fromID = dialog->getStartID();
            toID = dialog->getToID();

            backStack.clear();

            updateByID(currID);
            updateStateUI();
            getStateWin()->resetTimerWin();
        }
    }
}




