#ifndef MINEMAIN_H
#define MINEMAIN_H
#include <QMainWindow>
#include "button.h"
#include "lcdnumber.h"
#include "paintmine.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

//! [0]
class MainWindow : public QMainWindow
//! [0] //! [1]
{
    Q_OBJECT
    //! [1]

public:
    MainWindow(QWidget *parent = nullptr,QString en_qm="",QString cn_qm="");

private:
    QString en_qm;
    QString cn_qm;
    int iLanguage;
    paintmine *qMineChess;
    QTimer * qMineTimer;
    unsigned int iTimerCount;
    unsigned int mineCount;
    Button *newgameButton;
    QIcon icon_s;
    QIcon icon_f;
    CHESS_DIFFICULTY cd;
    LcdNumber * lcdminenum;
    LcdNumber * lcdTimer;
    QMenu *fileMenu;
    QAction *exitAct;
    QAction *easyAct;
    QAction *middleAct;
    QAction *hardAct;
    QAction *chineseAct;
    QAction *englishAct;
    QAction *aboutAct;
    Button *createButton(const QString &text, const char *member);
    void Language(int);
    void retranslateUi();
    void createmenu();

private slots:
    void  slot_display(int);
    void  slot_timer_display(int);
    void  slot_EasyAction();
    void  slot_MiddleAction();
    void  slot_HardAction();
    void  slot_Chinese();
    void  slot_English();
    void  MiningTimer();
    void  slot_StartMine();
    void  slot_StopMine();
    void  slot_ClearMineTime();
    void  aboutClicked();
    void  slot_newgame();
    void  slot_gamefail();

signals:
    void signals_setTime(int iTime);
};

#endif // MINEMAIN_H
