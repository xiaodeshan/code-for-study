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
        if(!isShowPic){
            isShowPic = true;

            QString cardName = cardNames->at(currID);
            showImageAndLabel(currPath, currNumText + " " + cardNames->at(currID), isShowPic);
        }else{

            if((currID == getLast() && mode == studyMode) || (fromID != -1 && backStack.size() + 1 == learnNum)){
                QMessageBox::information(this, "提示", "恭喜，已经完成了学习",
                                         QMessageBox::Ok);
            }else{
                isShowPic = false;
                showImageAndLabel(currPath, currNumText + " " + cardNames->at(currID), isShowPic);
                backStack.push(currID);
                updateByID(getNextID());
                updateStateUI();
            }
            //qDebug() << (learnNum - 1) << " " << backStack.size();
        }

        if(mode == trainMode){
            TrainWin* temp = ((TrainWin*)(leftWidget));
            temp->nextShow();
        }
        break;
    case Qt::Key_Left:
    case Qt::Key_Up:
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

    QMenu* fileMenu = menuBar->addMenu(tr("&文件"));
    QAction* exitAction = fileMenu->addAction("退出");

    QMenu* settingMenu = menuBar->addMenu(tr("&设置"));
    QMenu* modeMenu = settingMenu->addMenu(tr("&模式"));
    QAction* scopeMenuAction = settingMenu->addAction(tr("&学习范围"));

    QAction *stydyModeAction = new QAction("学习模式");
    QAction *checkModeAction = new QAction("检查模式");
    QAction *trainModeAction = new QAction("检查模式");
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
        rightWidget->hide();
        mode = checkMode;
    }
}

void MemoryMain::slotChooseTrainMode(bool triggle)
{
    if(triggle){
        rightWidget->hide();
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




