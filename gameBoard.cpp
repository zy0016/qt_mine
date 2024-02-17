/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "gameBoard.h"
#include "button.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPushButton>
#include <QTranslator>

gameBoard::gameBoard(QWidget *parent,QString en,QString cn)
    : QWidget(parent), en_qm(en),cn_qm(cn)
{
    mineCount = MINESNUM_EASY;

    qMineChess = new MineField( this ,Difficult_Easy,en_qm,cn_qm);
    aboutButton = createButton(tr("About"), SLOT(aboutClicked()));
    newgameButton = createButton(tr("New Game"), SLOT(newgame()));
    quitButton = createButton(tr("Quit"), SLOT(quitClicked()));

    //QPushButton *quitButton = new QPushButton("Quit");
    //connect(quitButton , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    QComboDifficult = new QComboBox();
    QComboDifficult->setFont( QFont( "Times", 20 ) );
    QComboDifficult->addItem(tr("Easy"));
    QComboDifficult->addItem(tr("Middle"));
    //QComboDifficult->addItem(tr("Hard"));
    connect(QComboDifficult,SIGNAL(activated(int)),this,SLOT(Difficult(int)));

    QComboLanguage = new QComboBox;
    QComboLanguage->setFont( QFont( "Times", 20 ) );
    QComboLanguage->addItem("中文");
    QComboLanguage->addItem("English");
    connect(QComboLanguage,SIGNAL(activated(int)),this,SLOT(Language(int)));

    lcdTimer = new LcdNumber(this);
    lcdTimer->setFont(QFont("Times",9,QFont::Bold));
    lcdTimer->display(0);
    lcdTimer->setGeometry(600,100,20,20);
    connect(this,SIGNAL(signals_setTime(int)),lcdTimer,SLOT(slot_timer_display(int)));

    lcdminenum = new LcdNumber(this);
    lcdminenum->setFont(QFont("Times",9,QFont::Bold));
    lcdminenum->display((int)mineCount);
    connect(qMineChess,SIGNAL(MineNumberValueChange(int)),this,SLOT(slot_display(int)));

    //timer
    qMineTimer = new QTimer(this);
    connect(qMineTimer,SIGNAL(timeout()),this,SLOT(MiningTimer()));
    //////////////////////////////////////////////////////////////
    connect(qMineChess,SIGNAL(StartMineTimer()),this,SLOT(slot_StartMine()));
    connect(qMineChess,SIGNAL(StopMineTimer()),this,SLOT(slot_StopMine()));
    connect(qMineChess,SIGNAL(ClearMineTime()),this,SLOT(slot_ClearMineTime()));

//    QHBoxLayout *firstlineLayout = new QHBoxLayout;
    QVBoxLayout *mineLayout = new QVBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(newgameButton,0,0);
    gridLayout->addWidget(QComboDifficult,0,1);
    gridLayout->addWidget(QComboLanguage,0,2);
    gridLayout->addWidget(aboutButton,0,3);
    gridLayout->addWidget(quitButton,0,4);
    gridLayout->addWidget(lcdminenum,0,5);
    gridLayout->addWidget(lcdTimer,0,6);

    mineLayout->addWidget(qMineChess);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(gridLayout);
    layout->addLayout(mineLayout);
    this->setLayout(layout);

    setWindowTitle(tr("mine"));
    setMinimumSize(670,670);
    setMaximumSize(670,670);
    qMineChess->NewGame(Difficult_Easy);
}

void gameBoard::Language(int l)
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
    aboutButton->setText(tr("About"));
    newgameButton->setText(tr("New Game"));
    quitButton->setText(tr("Quit"));
    QComboDifficult->setItemText(0,tr("Easy"));
    QComboDifficult->setItemText(1,tr("Middle"));
    qMineChess->SetLanguage(l);
}

void gameBoard::aboutClicked()
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
    QMessageBox::about(this,tr("about mine"),tr("1.0 version Copyright 12-01-2023 zhaoyong"));
}
void gameBoard::newgame()
{
    lcdTimer->display(0);
    int i = QComboDifficult->currentIndex();
    switch (i)
    {
    case 0:
        qMineChess->NewGame(Difficult_Easy);
        break;
    case 1:
        qMineChess->NewGame(Difficult_Middle);
        break;
    }
}

void gameBoard::quitClicked()
{
    QCoreApplication::quit();
}

Button *gameBoard::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void gameBoard::Difficult(int d)
{
    qWarning("Difficult for %d\n",d);
    switch (d)
    {
    case 0:
        qMineChess->NewGame(Difficult_Easy);
        break;
    case 1:
        qMineChess->NewGame(Difficult_Middle);
        break;
    }
}

void gameBoard::slot_StartMine()
{
  qWarning("slot_StartMine");
  if (qMineTimer->isActive())
    return;
  iTimerCount = 0;
  qMineTimer->start(1000);
}
void gameBoard::slot_StopMine()
{
  qWarning("slot_StopMine");
  iTimerCount = 0;
  qMineTimer->stop();
}
void gameBoard::slot_ClearMineTime()
{
  qWarning("slot_ClearMineTime");
  iTimerCount = 0;
  signals_setTime(iTimerCount);
}

void gameBoard::MiningTimer()
{
  //if (qMineTimer->isActive())
  //  return;
  //lcdTimer->display(++iTimerCount);
  iTimerCount++;
  //signals_setTime(iTimerCount);
  lcdTimer->display((int)iTimerCount);//OK
  qWarning("Timer begin:%d",iTimerCount);
}

void gameBoard::slot_display(int v)
{
    lcdminenum->display(v);
}
void gameBoard::slot_timer_display(int v)
{
    lcdTimer->display(v);
}
