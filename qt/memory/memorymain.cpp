#include "memorymain.h"

MemoryMain::MemoryMain(QWidget *parent) :
    QWidget(parent)
{
    init();
}

MemoryMain::~MemoryMain()
{
}

void MemoryMain::init()
{
    widgetLayout = new QHBoxLayout();
    learnScopeEntity = LearnScopeEntity::crateEmptyLearnScopeEntity();

    readAllCardInfoFromFile(CARD_NAME_PATH);
    initMode();
    initUI();
    initMenuBar();
    initBackground();
    initScope();
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

QString MemoryMain::getPicPathByid(int id)
{
    QString path = CARD_PATH + cardNums->at(id) + ".png";
    return path;
}


void MemoryMain::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
    case Qt::Key_Down:
    case Qt::Key_Right:
        currModeContext->handlerNext();
        break;
    case Qt::Key_Left:
    case Qt::Key_Up:
        currModeContext->handlerLast();
        break;
    default:
        break;
    }

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
    learnScopeEntity = LearnScopeEntity::crateEmptyLearnScopeEntity();
}

void MemoryMain::initMode()
{
    // 开始是学习模式
    currModeContext = new StudyMode(this);
    currModeContext->handlerChoosen();

    initModeList();
}

void MemoryMain::initModeList()
{
    modeList.append(new StudyMode(this));
    modeList.append(new CheckMode(this));
    modeList.append(new TrainMode(this));
    modeList.append(new UnfamilarMode(this));
}

void MemoryMain::bindModeToMenu(QMenu *modeMenu)
{
    QActionGroup* modeActionGroup = new QActionGroup(this);
    modeActionGroup->setExclusive(true);

    for(int i = 0; i < modeList.size(); i++){
        QAction *action = new QAction("&" + modeList.at(i)->getModeName());

        action->setCheckable(true);
        if(i == 0)
            action->setChecked(true);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(slotModeClick()));

        modeActionGroup->addAction(action);

        if(action->text() == "&陌生模式"){
            UnfamilarMode*  unfamilarMode = (UnfamilarMode*)modeList.at(i);
            connect(this, SIGNAL(signalAddToUnfamiliar(int)), unfamilarMode, SLOT(slotAddToUnfamiliar(int)));
        }
    }

    modeMenu->addActions(modeActionGroup->actions());
}

int MemoryMain::getTrueSize()
{
    if(cardNums == nullptr)
        return 0;
    return cardNums->size();
}

void MemoryMain::updateLayout(QWidget *mainPageWidget, QWidget *rightStatusWidget)
{   
    if(mainPageWidget != nullptr)
        widgetLayout->addWidget(mainPageWidget, 4);
    if(rightStatusWidget != nullptr)
        widgetLayout->addWidget(rightStatusWidget, 1);

    this->setLayout(widgetLayout);
}

void MemoryMain::copyText(QString text)
{
    QClipboard *clipboard = QApplication::clipboard();   //get the pointer of clipboard
    //QString originalText = clipboard->text();          //get the text of clipboard
    clipboard->setText(text);                            //set clipboard text
}

LearnScopeEntity MemoryMain::getLearnScopeEntity()
{
    return *learnScopeEntity;
}

void MemoryMain::slotCopyText()
{
    //copyText(currNumText);
}

void MemoryMain::slotAddToUnfamiliarAction()
{
    emit signalAddToUnfamiliar(currModeContext->getCurrId());
}

void MemoryMain::slotModeClick()
{
    QAction* senderAction = (QAction*)sender();

    // 投递到对应的处理函数
    for(int i = 0; i < modeList.size(); i++){
        //qDebug() << modeList.at(i)->getModeName() << " text" << senderAction->text();
        if("&" + modeList.at(i)->getModeName() == senderAction->text()){
            currModeContext->handlerLeft();
            currModeContext = modeList.at(i);
            currModeContext->handlerChoosen();
            break;
        }

    }
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

    bindModeToMenu(modeMenu);

    connect(scopeMenuAction, SIGNAL(triggered(bool)), this, SLOT(slotChooseScope()));
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

    popMenu->exec(QCursor::pos());
}
