#include "memorymain.h"

MemoryMain::MemoryMain(QWidget *parent) :
    QWidget(parent)
{
    init();
    //startProg();
}

MemoryMain::~MemoryMain()
{
}

void MemoryMain::init()
{
    widgetLayout = new QHBoxLayout();
    learnScopeEntity = LearnScopeEntity::crateEmptyLearnScopeEntity();

    isShowPic = false;
    readAllCardInfoFromFile(CARD_NAME_PATH);

    initUI();
    initSrand();
    initMenuBar();
    initBackground();
    justStart = true;
    mode = studyModezzzzzz;
    initScope();

    initMode();
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

    //TODO from file
    unfamiliarList = new QList<int>();
    unfamiliarId = -1;
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
    //getShowWin()->showImageAndLabel(path, text, ispic);
}



int MemoryMain::getNumSize()
{
    if(learnNum == -1)
        return getTrueSize();

    switch (mode) {
    case studyModezzzzzz:{
        int sizeT = getLast() - fromID + 1;
        return learnNum > sizeT ? sizeT : learnNum;
        break;
    }
    case checkModezzzzzzzzzzzz:
        return learnNum;
        break;
    case trainModezzzzzzzzzzzz:
        break;
    case unfamiliarModezzzzzzzzzz:
        return unfamiliarList->size();
        break;
    default:
        assert(0);
    }

    return -1;
}

void MemoryMain::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Down:
    case Qt::Key_Right:
        handleKeyNext();
        break;
    case Qt::Key_Left:
    case Qt::Key_Up:
        handleKeyLast();
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


void MemoryMain::initBackground()
{
    QPalette pal(this->palette());
    //setting background color
    pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void MemoryMain::initUI()
{
    setMinimumSize(QSize(1077, 913));

    this->resize(QSize(1077, 913));
}

void MemoryMain::initScope()
{
    //study scope
    learnNum = -1;
    fromID = -1;
}

void MemoryMain::initMode()
{
    // 开始是学习模式
    currModeContext = new StudyMode(this);
    currModeContext->handlerChoosen();
}

int MemoryMain::getNextID()
{
    switch (mode) {
    case studyModezzzzzz:{
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
    }
        break;
    case checkModezzzzzzzzzzzz:{
        if(fromID != -1)
            return getRandomByFromTo(fromID, toID);
        else
            return getRandCardNum(getTrueSize());
    }
        break;
    case trainModezzzzzzzzzzzz:
        break;
    case unfamiliarModezzzzzzzzzz:{
        if(unfamiliarId == -1){
            return -1;
        }
        unfamiliarId = unfamiliarId + 1;
        if(unfamiliarId == unfamiliarList->size()){
            unfamiliarId = 0;
        }
        return unfamiliarList->at(unfamiliarId);
    }
        break;
    default:
        break;
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
    if(mode == studyModezzzzzz){
        int showID = currID;
        if(fromID != -1)
            showID = currID - fromID;
        //getStateWin()->updateStateUI(showID, getNumSize());
    }else if(unfamiliarModezzzzzzzzzz){
        int showID = unfamiliarList->at(unfamiliarId);
        //getStateWin()->updateStateUI(showID, getNumSize());
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
    if(mode == unfamiliarModezzzzzzzzzz){
        qDebug() << unfamiliarList;
        return unfamiliarList->at(unfamiliarList->size() - 1);
    }

    if(fromID == -1)
        return getTrueSize() - 1;

    int last = fromID + learnNum - 1;
    if(last > getTrueSize() - 1)
        last = getTrueSize() - 1;

    return last;
}

void MemoryMain::updateLayout(QWidget *mainPageWidget, QWidget *rightStatusWidget)
{   
    if(mainPageWidget != nullptr)
        widgetLayout->addWidget(mainPageWidget, 4);
    if(rightStatusWidget != nullptr)
        widgetLayout->addWidget(rightStatusWidget, 1);

    this->setLayout(widgetLayout);
}


//TrainWin *MemoryMain::getTrainWin()
//{
//    return (TrainWin*)(leftWidget);
//}

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
    //getStateWin()->resetTimerWin();
}

int MemoryMain::getRandomByFromTo(int from, int to)
{
    return rand() % (to - from) + from + 1;
}

void MemoryMain::copyText(QString text)
{
    QClipboard *clipboard = QApplication::clipboard();   //get the pointer of clipboard
    //QString originalText = clipboard->text();          //get the text of clipboard
    clipboard->setText(text);                            //set clipboard text
}

bool MemoryMain::isEnded()
{
    switch (mode) {
    case studyModezzzzzz:
        return currID == getLast();
        break;
    case checkModezzzzzzzzzzzz:
        return fromID != -1 && backStack.size() + 1 == learnNum;
        break;
    case trainModezzzzzzzzzzzz:
        break;
    case unfamiliarModezzzzzzzzzz:
        if(backStack.size() + 1 == unfamiliarList->size()){
            return true;
        }
        break;
    default:
        assert(0);
        return false;
    }

    return false;
}

void MemoryMain::handleKeyNext()
{
    currModeContext->handlerNext();
//    switch (mode) {
//    case studyModezzzzzz:
//    case checkModezzzzzzzzzzzz:
//    case unfamiliarModezzzzzzzzzz:
//        currModeContext->handlerNext();
//        break;
//    case trainModezzzzzzzzzzzz:
//        getTrainWin()->nextShow();
//        break;
//    }
}

void MemoryMain::handleKeyLast()
{
    currModeContext->handlerLast();

//    switch (mode) {
//    case studyModezzzzzz:
//    case checkModezzzzzzzzzzzz:
//        currModeContext->handlerLast();
//    case trainModezzzzzzzzzzzz:{
//        bool ok = getTrainWin()->lastShow();
//        if(!ok){
//            QMessageBox::information(this, "info", "It is the first one",
//                                     QMessageBox::Ok);
//        }
//        break;
//    }
//    case unfamiliarModezzzzzzzzzz:
//        break;
//    }
}

LearnScopeEntity MemoryMain::getLearnScopeEntity()
{
    return *learnScopeEntity;
}

void MemoryMain::slotChooseStydyMode(bool triggle)
{
    if(triggle){
        currModeContext = new StudyMode(this);
        currModeContext->handlerChoosen();
    }
}

void MemoryMain::slotChooseCheckMode(bool triggle)
{
    if(triggle){
        mode = checkModezzzzzzzzzzzz;
        //leftWidget->close();
        //leftWidget = new ShowWin(this);
        //leftWidget->show();
        isShowPic = false;
        initScope();

        currID = getNextID();
        updateByID(currID);

        //updateLayout();
        updateStateUI();
    }
}

void MemoryMain::slotChooseTrainMode(bool triggle)
{
    if(triggle){
        //rightWidget->hide();
        //getStateWin()->resetTimerWin();
        //leftWidget->close();
        //leftWidget = new TrainWin(this);
        //leftWidget->show();
        mode = trainModezzzzzzzzzzzz;
        //updateLayout();
    }
}

void MemoryMain::slotunfamiliarMode(bool triggle)
{
    if(triggle){
        mode = unfamiliarModezzzzzzzzzz;

        //leftWidget->close();
        //leftWidget = new ShowWin(this);
        //leftWidget->show();
        //rightWidget->show();
        isShowPic = false;
        backStack.clear();
        updateByID(unfamiliarList->at(0));
        unfamiliarId = 0;
        showImageAndLabel(currPath, currNumText, isShowPic);
        //getStateWin()->resetTimerWin();
        initScope();

        //updateLayout();
        updateStateUI();
    }
}

void MemoryMain::slotChooseScope()
{
    dialog = new LearnScopeDialog(this);
    int result = dialog->exec();

    if(result){
        backStack.clear();

        if(mode == studyModezzzzzz){
            learnNum = dialog->getTotal();
            fromID = dialog->getStartID();
            currID = fromID;
            updateByID(currID);
            updateStateUI();
            //getStateWin()->resetTimerWin();
        }else if(mode == checkModezzzzzzzzzzzz){
            currID = getNextID();
            learnNum = dialog->getTotal();
            fromID = dialog->getStartID();
            toID = dialog->getToID();

            backStack.clear();

            updateByID(currID);
            updateStateUI();
            //getStateWin()->resetTimerWin();
        }
    }
}

void MemoryMain::slotAddToUnfamiliar(int id)
{
    for(int i = 0; i < unfamiliarList->size(); i++){
        if(unfamiliarList->at(i) == id){
            return;
        }
    }

    unfamiliarList->append(id);
}

void MemoryMain::slotCopyText()
{
    copyText(currNumText);
}

void MemoryMain::slotAddToUnfamiliarAction()
{
    emit signalAddToUnfamiliar(currID);
}

void MemoryMain::initMenuBar()
{
    menuBar = new QMenuBar(this);
    menuBar->setFixedSize(QSize(this->width(), menuBar->height()));

    QMenu* fileMenu = menuBar->addMenu(tr("&文件"));
    QAction* exitAction = fileMenu->addAction("退出");

    QMenu* settingMenu = menuBar->addMenu(tr("&设置"));
    QMenu* modeMenu = settingMenu->addMenu(tr("&模式"));
    QAction* scopeMenuAction = settingMenu->addAction(tr("&学习范围"));

    QAction *stydyModeAction = new QAction("&学习模式");
    QAction *checkModeAction = new QAction("&检查模式");
    QAction *trainModeAction = new QAction("&训练模式");
    QAction *unfamiliarModeAction = new QAction("&不熟悉模式");

    stydyModeAction->setCheckable(true);
    checkModeAction->setCheckable(true);
    trainModeAction->setCheckable(true);
    unfamiliarModeAction->setCheckable(true);

    QActionGroup* modeActionGroup = new QActionGroup(this);
    modeActionGroup->addAction(stydyModeAction);
    modeActionGroup->addAction(checkModeAction);
    modeActionGroup->addAction(trainModeAction);
    modeActionGroup->addAction(unfamiliarModeAction);

    stydyModeAction->setChecked(true);
    modeActionGroup->setExclusive(true);

    modeMenu->addActions(modeActionGroup->actions());

    connect(stydyModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseStydyMode(bool)));
    connect(checkModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseCheckMode(bool)));
    connect(scopeMenuAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseScope()));
    connect(trainModeAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseTrainMode(bool)));
    connect(unfamiliarModeAction, SIGNAL(triggered(bool)), this, SLOT(slotunfamiliarMode(bool)));

    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MemoryMain::contextMenuEvent(QContextMenuEvent *)
{
    QMenu *popMenu = new QMenu(this);

    QAction *copyAction = new QAction("复制文字");
    QAction *addToDonotKnowAction = new QAction("添加为陌生");

    popMenu->addAction(copyAction);
    popMenu->addAction(addToDonotKnowAction);

    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(slotCopyText()));
    connect(addToDonotKnowAction, SIGNAL(triggered(bool)), this, SLOT(slotAddToUnfamiliarAction()));
    connect(this, SIGNAL(signalAddToUnfamiliar(int)), this, SLOT(slotAddToUnfamiliar(int)));

    popMenu->exec(QCursor::pos());
}
