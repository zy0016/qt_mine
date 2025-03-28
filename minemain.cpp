#include <QtWidgets>
#include <QIcon>
#include "minemain.h"

MainWindow::MainWindow(QWidget *parent,QString en,QString cn):en_qm(en),cn_qm(cn)
{
    (void)parent;
    icon_s.addFile("./s1.png");
    icon_f.addFile("./s2.png");

    createmenu();
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建用于绘制正方形的 minewidget
    qMineChess = new paintmine(this);
    newgameButton = createButton(tr("New Game"), SLOT(slot_newgame()));

    lcdTimer = new LcdNumber(this);
    lcdTimer->setFont(QFont("Times",9,QFont::Bold));
    lcdTimer->display(0);
    connect(this,SIGNAL(signals_setTime(int)),lcdTimer,SLOT(slot_timer_display(int)));

    lcdminenum = new LcdNumber(this);
    lcdminenum->setFont(QFont("Times",9,QFont::Bold));
    lcdminenum->display((int)mineCount);
    connect(qMineChess,SIGNAL(MineNumberValueChange(int)),this,SLOT(slot_display(int)));

    qMineTimer = new QTimer(this);
    connect(qMineTimer,SIGNAL(timeout()),this,SLOT(MiningTimer()));
    //////////////////////////////////////////////////////////////
    connect(qMineChess,SIGNAL(StartMineTimer()),this,SLOT(slot_StartMine()));
    connect(qMineChess,SIGNAL(StopMineTimer()),this,SLOT(slot_StopMine()));
    connect(qMineChess,SIGNAL(ClearMineTime()),this,SLOT(slot_ClearMineTime()));
    connect(qMineChess,SIGNAL(gamefail()),this,SLOT(slot_gamefail()));

    //QGridLayout *gridLayout = new QGridLayout;
    //QVBoxLayout *mineLayout = new QVBoxLayout;
    QHBoxLayout *firstLayut = new QHBoxLayout;
    firstLayut->addWidget(lcdTimer);
    firstLayut->addWidget(newgameButton);
    firstLayut->addWidget(lcdminenum);

    QVBoxLayout *layoutall = new QVBoxLayout;
    layoutall->addLayout(firstLayut);
    layoutall->addWidget(qMineChess);

    centralWidget->setLayout(layoutall);

    setWindowTitle(tr("mine"));
    setMinimumSize(EASY_SCREEN_SIZE_W,EASY_SCREEN_SIZE_H);
    setMaximumSize(EASY_SCREEN_SIZE_W,EASY_SCREEN_SIZE_H);
    cd = Difficult_Easy;
    newgameButton->setIcon(icon_s);
    qMineChess->NewGame(Difficult_Easy);
    move(10,10);
}
void MainWindow::slot_EasyAction()
{
    setMinimumSize(EASY_SCREEN_SIZE_W,EASY_SCREEN_SIZE_H);
    setMaximumSize(EASY_SCREEN_SIZE_W,EASY_SCREEN_SIZE_H);
    cd = Difficult_Easy;
    newgameButton->setIcon(icon_s);
    qMineChess->NewGame(Difficult_Easy);
}
void MainWindow::slot_MiddleAction()
{
    setMinimumSize(MID_SCREEN_SIZE_W,MID_SCREEN_SIZE_H);
    setMaximumSize(MID_SCREEN_SIZE_W,MID_SCREEN_SIZE_H);
    cd = Difficult_Middle;
    newgameButton->setIcon(icon_s);
    qMineChess->NewGame(Difficult_Middle);
}
void MainWindow::slot_HardAction()
{
    setMinimumSize(HARD_SCREEN_SIZE_W,HARD_SCREEN_SIZE_H);
    setMaximumSize(HARD_SCREEN_SIZE_W,HARD_SCREEN_SIZE_H);
    cd = Difficult_Hard;
    newgameButton->setIcon(icon_s);
    qMineChess->NewGame(Difficult_Hard);
}
Button *MainWindow::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
void MainWindow::createmenu()
{
    //! [1]
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
    //! [2]
    easyAct = new QAction(tr("Easy"), this);
    connect(easyAct, SIGNAL(triggered()), this, SLOT(slot_EasyAction()));
    //! [3]
    middleAct = new QAction(tr("Middle"), this);
    connect(middleAct, SIGNAL(triggered()), this, SLOT(slot_MiddleAction()));

    hardAct = new QAction(tr("hard"), this);
    connect(hardAct, SIGNAL(triggered()), this, SLOT(slot_HardAction()));

    chineseAct = new QAction("中文", this);
    connect(chineseAct, SIGNAL(triggered()), this, SLOT(slot_Chinese()));

    englishAct = new QAction("English", this);
    connect(englishAct, SIGNAL(triggered()), this, SLOT(slot_English()));

    aboutAct = new QAction(tr("About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(aboutClicked()));

    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(easyAct);
    fileMenu->addAction(middleAct);
    fileMenu->addAction(hardAct);
    fileMenu->addAction(chineseAct);
    fileMenu->addAction(englishAct);
    fileMenu->addAction(aboutAct);
    fileMenu->addAction(exitAct);
}
void MainWindow::retranslateUi()
{
    menuBar()->clear();
    createmenu();
}
void MainWindow::slot_gamefail()
{
    newgameButton->setIcon(icon_f);
}
void MainWindow::slot_display(int v)
{
    lcdminenum->display(v);
}
void MainWindow::slot_timer_display(int v)
{
    lcdTimer->display(v);
}
void MainWindow::slot_StartMine()
{
    qWarning("slot_StartMine");
    if (qMineTimer->isActive())
        return;
    iTimerCount = 0;
    qMineTimer->start(1000);
}
void MainWindow::slot_StopMine()
{
    qWarning("slot_StopMine");
    iTimerCount = 0;
    qMineTimer->stop();
}
void MainWindow::slot_ClearMineTime()
{
    qWarning("slot_ClearMineTime");
    iTimerCount = 0;
    signals_setTime(iTimerCount);
}
void MainWindow::slot_newgame()
{
    slot_timer_display(0);
    newgameButton->setIcon(icon_s);
    qMineChess->NewGame(cd);
}
void MainWindow::slot_Chinese()
{
    Language(2);
}
void MainWindow::slot_English()
{
    Language(1);
}
void MainWindow::aboutClicked()
{
    QTranslator qt;
    bool b = false;
    if (iLanguage == 1)//English
    {
        b = qt.load(en_qm);
    }
    else//Chinese
    {
        b = qt.load(cn_qm);
    }
    if (!b)
    {
        QMessageBox::about(nullptr,"about mine","I can't load qs file");
    }
    QCoreApplication::installTranslator(&qt);
    QMessageBox::about(this,tr("about mine"),tr("1.0 version Copyright 03-28-2025 zhaoyong"));
}
void MainWindow::Language(int l)
{
    QTranslator qt;
    bool b = false;
    iLanguage = l;
    if (l == 1)//English
    {
        b = qt.load(en_qm);
    }
    else//Chinese
    {
        b = qt.load(cn_qm);
    }
    if (!b)
    {
        QMessageBox::about(nullptr,"about mine","I can't load qs file");
    }
    QCoreApplication::installTranslator(&qt);
    setWindowTitle(tr("mine"));
    retranslateUi();
    qMineChess->SetLanguage(l);
}
void MainWindow::MiningTimer()
{
    //if (qMineTimer->isActive())
    //  return;
    //lcdTimer->display(++iTimerCount);
    iTimerCount++;
    //signals_setTime(iTimerCount);
    lcdTimer->display((int)iTimerCount);//OK
    qWarning("Timer begin:%d",iTimerCount);
}
