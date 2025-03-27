#include <QtWidgets>
#include "paintmine.h"

paintmine::paintmine(QWidget *parent,CHESS_DIFFICULTY chess_level,QString en,QString cn):
    QWidget( parent ),level(chess_level), en_qm(en),cn_qm(cn)
{
    //setFixedSize(800, 800); // 固定大小，适合绘制正方形
    bMineDefeat = false;
    qClew = "";
}
void paintmine::NewGame(CHESS_DIFFICULTY chess_level)
{
    InitChessman(chess_level);
}
void paintmine::SetMines(int iRow,int iCol)
{
    if (sChessmine[iRow][iCol].bCheck)
        return;
    if (sChessmine[iRow][iCol].iMineNum != 0)
    {
        sChessmine[iRow][iCol].eGridType = GRID_CLICKOPEN;
        sChessmine[iRow][iCol].bCheck = true;
        return;
    }
    sChessmine[iRow][iCol].eGridType = GRID_CLICKOPEN;
    sChessmine[iRow][iCol].bCheck = true;
    if ((iRow == 0) && (iCol == 0))//1
    {
        SetMines(iRow,iCol + 1);//2
        SetMines(iRow + 1,iCol + 1);//5
        SetMines(iRow + 1,iCol);//4
    }
    else if ((iRow == 0) && (0 < iCol) && (iCol < chessnum - 1))//2
    {
        SetMines(iRow,iCol - 1);//1
        SetMines(iRow,iCol + 1);//3
        SetMines(iRow + 1,iCol - 1);//4
        SetMines(iRow + 1,iCol);//5
        SetMines(iRow + 1,iCol + 1);//6
    }
    else if ((iRow == 0) && (iCol == chessnum - 1))//3
    {
        SetMines(iRow,iCol - 1);//2
        SetMines(iRow + 1,iCol - 1);//5
        SetMines(iRow + 1,iCol);//6
    }
    else if ((0 < iRow) && (iRow < chessnum - 1) && (iCol == 0))//4
    {
        SetMines(iRow - 1,iCol);//1
        SetMines(iRow - 1,iCol + 1);//2
        SetMines(iRow,iCol + 1);//5
        SetMines(iRow + 1,iCol + 1);//8
        SetMines(iRow + 1,iCol);//7
    }
    else if ((0 < iRow) && (iRow < chessnum - 1) && (iCol == chessnum - 1))//6
    {
        SetMines(iRow - 1,iCol - 1);//2
        SetMines(iRow - 1,iCol);//3
        SetMines(iRow,iCol - 1);//5
        SetMines(iRow + 1,iCol - 1);//8
        SetMines(iRow + 1,iCol);//9
    }
    else if ((iRow == chessnum - 1) && (iCol == 0))//7
    {
        SetMines(iRow - 1,iCol);//4
        SetMines(iRow - 1,iCol + 1);//5
        SetMines(iRow,iCol + 1);//8
    }
    else if ((iRow == chessnum - 1) && (0 < iCol) && (iCol < chessnum - 1))//8
    {
        SetMines(iRow - 1,iCol - 1);//4
        SetMines(iRow - 1,iCol);//5
        SetMines(iRow - 1,iCol + 1);//6
        SetMines(iRow,iCol - 1);//7
        SetMines(iRow,iCol + 1);//9
    }
    else if ((iRow == chessnum - 1) && (iCol == chessnum - 1))//9
    {
        SetMines(iRow - 1,iCol);//6
        SetMines(iRow - 1,iCol - 1);//5
        SetMines(iRow,iCol - 1);//8
    }
    else//5
    {
        SetMines(iRow - 1,iCol - 1);//1
        SetMines(iRow - 1,iCol);//2
        SetMines(iRow - 1,iCol + 1);//3
        SetMines(iRow,iCol - 1);//4
        SetMines(iRow,iCol + 1);//6
        SetMines(iRow + 1,iCol - 1);//7
        SetMines(iRow + 1,iCol);//8
        SetMines(iRow + 1,iCol + 1);//9
    }
}
void paintmine::mousePressEvent( QMouseEvent * e)
{
    if ((e->pos().x() < hx1) || (e->pos().x() > hx1 + bw * chessnum))
        return;
    if ((e->pos().y() < hy1) || (e->pos().y() > hy1 + bh * chessnum))
        return;

    int irow,icol;
    if (!GetChessNumber(irow,icol,e->pos()))
    {
        return;
    }
    if (IfGameOver())
    {
        MineOver();
        return;
    }
    qWarning("mousePressEvent,irow:%d,icol:%d",irow,icol);
    BeginMine();
    if (e->button() == Qt::LeftButton)
    {
        if (sChessmine[irow][icol].bMineType)//people click the mine,game over
        {
            //display all mines and display game over.
            sChessmine[irow][icol].eGridType = GRID_DEFEAT;
            bMineDefeat = true;
            qClew = "Defeat!";
            game_result = FAIL;
            qWarning("Defeat Row:%d,Col:%d",irow,icol);
            MineOver();
        }
        else//
        {
            if (sChessmine[irow][icol].eGridType != GRID_NORMAL)
                return;
            if (sChessmine[irow][icol].iMineNum == 0)
            {
                SetMines(irow,icol);
            }
            else
            {
                sChessmine[irow][icol].eGridType = GRID_CLICKOPEN;
            }
            qWarning("Just IfGameOver");
            if (IfGameOver())
            {
                qClew = "You Win!";
                game_result = SUCCESS;
                qWarning("You Win!");
                MineOver();
            }
        }
        repaint();
    }
    else if (e->button() == Qt::RightButton)
    {
        if (sChessmine[irow][icol].eGridType == GRID_NORMAL)
        {
            sChessmine[irow][icol].eGridType = GRID_FLAG;
            SetMineNumber(1);//iFindMineNumber++;
            qWarning("You find %d mines",iFindMineNumber);
            if (IfGameOver())
            {
                qClew = "You Win!";
                game_result = SUCCESS;
                qWarning("You Win!");
                MineOver();
            }
        }
        else if (sChessmine[irow][icol].eGridType == GRID_FLAG)
        {
            qWarning("Flag");
            sChessmine[irow][icol].eGridType = GRID_INTERROGATION;
            SetMineNumber(-1);//iFindMineNumber--;
        }
        else if (sChessmine[irow][icol].eGridType == GRID_INTERROGATION)
        {
            qWarning("Interrogation");
            sChessmine[irow][icol].eGridType = GRID_NORMAL;
        }
        repaint();
    }
}
void paintmine::SetLanguage(int l)
{
    iLanguage = l;
}
void paintmine::BeginMine()
{
    qWarning("In mine.cpp, call BeginMine");
    if (bStartMine)
    {
        qWarning("The mine has started!");
        return;
    }
    bStartMine = true;
    emit StartMineTimer();
}
void paintmine::MineOver()
{
    qWarning("In mine.cpp, call MineOver");
    if (!bStartMine)
    {
        qWarning("The mine hasn't start");
        return;
    }
    bStartMine = false;
    emit StopMineTimer();
}
void paintmine::ClearTime()
{
    qWarning("call ClearTime");
    ClearMineTime();
}
void paintmine::SetMineNumber(int iValue)
{
    if (iValue > 0)
    {
        if (iFindMineNumber >= minenum)
            return;
        iFindMineNumber++;
    }
    else if (iValue < 0)
    {
        if (iFindMineNumber <= 0)
            return;
        iFindMineNumber--;
    }
    emit MineNumberValueChange(minenum - iFindMineNumber);
}
bool paintmine::GetChessNumber(int & iRow,int & iCol,const QPoint &point)
{
    int i,j;
    for (i = 0;i < chessnum;i++)
    {
        for (j = 0;j < chessnum;j++)
        {
            if ((sChessmine[i][j].qPChessman.x() < point.x()) && (point.x() < sChessmine[i][j].qPChessman.x() + bw) &&
                (sChessmine[i][j].qPChessman.y() < point.y()) && (point.y() < sChessmine[i][j].qPChessman.y() + bh))
            {
                iRow = i;
                iCol = j;
                return true;
            }
        }
    }
    return false;
}

bool paintmine::IfGameOver()
{
    int i,j;
    int iMineNumber = 0;
    for (i = 0;i < chessnum;i++)
    {
        for (j = 0;j < chessnum ;j++)
        {
            if ((sChessmine[i][j].eGridType == GRID_FLAG) && (sChessmine[i][j].bMineType))
                iMineNumber++;
        }
    }
    for (i = 0;i < chessnum;i++)
    {
        for (j = 0;j < chessnum ;j++)
        {
            if ((!sChessmine[i][j].bMineType) && (sChessmine[i][j].eGridType != GRID_CLICKOPEN))
                return false;
        }
    }
    return (iMineNumber == minenum);
}
void paintmine::paintEvent(QPaintEvent *event)
{
    //QPainter painter(this);
    //painter.setBrush(Qt::black); // 设置黑色画刷
    //painter.drawRect(50, 10, 40, 40); // 绘制正方形
    (void)event;
    QPainter p( this );
    QPainter pDefeat(this);
    QColor qcolor(192,192,192);
    int i,j,iLinenum;
    QImage qflag("./flag.png");
    QImage qinterrogation("./interrogation.png");
    QImage qmineblack("./blackmine.png");
    QImage qminered("./redmine.png");
    const int iPicWidth = 30,iPicHeight = 30;

    iLinenum = (chessnum + 1) * 2;

    p.setPen(Qt::black);

    for (i = 0;i < iLinenum;i++)//18??
    {
        if (i < iLinenum / 2)//??(??)
        {
            p.drawLine(hx1,hy1 + bh * i,hx1 + bw * chessnum,hy1 + bh * i);
        }
        else//??(??)
        {
            p.drawLine(hx1 + bw * (i - iLinenum / 2),hy1,hx1 + bw * (i - iLinenum / 2),hy1 + bh * chessnum);
        }
    }

    p.setBrush(qcolor);
    p.setPen(Qt::NoPen);
    if (bMineDefeat)
    {
        pDefeat.setBrush(Qt::black);
        pDefeat.setPen(Qt::NoPen);
    }
    for (i = 0;i < chessnum;i++)
    {
        for (j = 0;j < chessnum ;j++)
        {
            if (bMineDefeat)//defeat,display all mines
            {
                if (sChessmine[i][j].eGridType == GRID_DEFEAT)//display the defeat mine
                {
                    QPainter pMine( this );
                    pMine.setBrush(qcolor);
                    pMine.setPen(Qt::NoPen);
                    pMine.drawImage(sChessmine[i][j].qPChessman.x() + (bw - iPicWidth) / 2,sChessmine[i][j].qPChessman.y() + (bh - iPicHeight) / 2,qminered);
                }
                else
                {
                    if (sChessmine[i][j].bMineType)
                    {
                        QPainter pmineBlack( this );
                        pmineBlack.setBrush(qcolor);
                        pmineBlack.setPen(Qt::NoPen);
                        pmineBlack.drawImage(sChessmine[i][j].qPChessman.x() + (bw - iPicWidth) / 2,sChessmine[i][j].qPChessman.y() + (bh - iPicHeight) / 2,qmineblack);
                    }
                    else
                    {
                        QPainter p1( this );
                        p1.setBrush(qcolor);
                        p1.setPen(Qt::NoPen);
                        p1.drawRect(sChessmine[i][j].qPChessman.x(),sChessmine[i][j].qPChessman.y(),bw - 1,bh - 1);
                        DrawMineNumber(i,j);
                    }
                }
            }
            else//mineing
            {
                switch (sChessmine[i][j].eGridType)
                {
                case GRID_NORMAL:
                {
                    QPainter p1( this );
                    p1.setBrush(qcolor);
                    p1.setPen(Qt::NoPen);
                    p1.drawRect(sChessmine[i][j].qPChessman.x(),sChessmine[i][j].qPChessman.y(),bw - 1,bh - 1);
                }
                break;
                case GRID_FLAG:
                {
                    QPainter p1( this );
                    p1.setBrush(qcolor);
                    p1.setPen(Qt::NoPen);
                    p1.drawRect(sChessmine[i][j].qPChessman.x(),sChessmine[i][j].qPChessman.y(),bw - 1,bh - 1);
                    p1.drawImage(sChessmine[i][j].qPChessman.x() + (bw - iPicWidth) / 2,sChessmine[i][j].qPChessman.y() + (bh - iPicHeight) / 2,qflag);
                }
                break;
                case GRID_INTERROGATION:
                {
                    QPainter p1( this );
                    p1.setBrush(qcolor);
                    p1.setPen(Qt::NoPen);
                    p1.drawRect(sChessmine[i][j].qPChessman.x(),sChessmine[i][j].qPChessman.y(),bw - 1,bh - 1);
                    p1.drawImage(sChessmine[i][j].qPChessman.x() + (bw - iPicWidth) / 2,sChessmine[i][j].qPChessman.y() + (bh - iPicHeight) / 2,qinterrogation);
                }
                break;
                case GRID_CLICKOPEN:
                    if (sChessmine[i][j].iMineNum != 0)//display the number of the grid
                    {
                        DrawMineNumber(i,j);
                    }
                    break;
                case GRID_DEFEAT:
                    break;
                default:
                    break;
                }
            }
        }
    }
    if (bMineDefeat || IfGameOver())
    {
        QPainter p1( this );
        p1.setBrush(Qt::black);
        p1.setFont(QFont("Courier",48,QFont::Bold));

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
            //QMessageBox::about(nullptr,"about mine","mine.cpp can't load qs file");
        }
        QCoreApplication::installTranslator(&qt);
        switch (game_result)
        {
        case SUCCESS:
            p1.drawText(rect(),Qt::AlignBottom,tr("You Win!"));
            break;
        case FAIL:
            p1.drawText(rect(),Qt::AlignBottom,tr("You fail."));
            emit gamefail();
            break;
        default:
            p1.drawText(rect(),Qt::AlignBottom,qClew);
            break;
        }
    }
}
void paintmine::DrawMineNumber(int i,int j)
{
    QPainter myTxt(this);
    myTxt.setPen(Qt::black);
    myTxt.setFont(QFont("Courier",12,QFont::Bold));
    char cMineNum[5] = "";
    QString qMineNum;

    if (sChessmine[i][j].iMineNum == 0)
        return;
    sprintf(cMineNum,"%d",sChessmine[i][j].iMineNum);
    qMineNum = cMineNum;
    myTxt.drawText(sChessmine[i][j].qPChessman.x() + bw / 2 - 5,sChessmine[i][j].qPChessman.y() + bh / 2 + 4,qMineNum);
}
bool paintmine::IfExistMineInCurrentCol(int icol)
{
    int i;
    for (i = 0;i < chessnum ;i++)
    {
        if (sChessmine[i][icol].bMineType)
        {
            return true;
        }
    }
    return false;
}

void paintmine::InitChessman(CHESS_DIFFICULTY chess_level)
{
    int i,j;
    int iMinenum = 0,iMineCol,iMineCount;
    qClew           = "";
    bMineDefeat     = false;
    iFindMineNumber = 0;
    bStartMine      = false;
    level           = chess_level;
    game_result     = PROGRESSING;

    switch (chess_level)
    {
    case Difficult_Easy:
        RowCount = CHESSNUM_EASY;
        ColCount = CHESSNUM_EASY;
        chessnum = CHESSNUM_EASY;
        minenum = MINESNUM_EASY;
        hx1 = 10;
        hy1 = 3;
        bh = 40;
        bw = bh;
        break;
    case Difficult_Middle:
        RowCount = CHESSNUM_MID;
        ColCount = CHESSNUM_MID;
        chessnum = CHESSNUM_MID;
        minenum = MINESNUM_MID;
        hx1 = 10;
        hy1 = 3;
        bh = 30;
        bw = bh;
        break;
    case Difficult_Hard:
        RowCount = CHESSNUM_HARD;
        ColCount = CHESSNUM_HARD;
        chessnum = CHESSNUM_HARD;
        minenum = MINESNUM_HARD;
        hx1 = 10;
        hy1 = 3;
        bh = 30;
        bw = bh;
        break;
    }
    //////////////////////////////////////////
    if (sChessmine.size() > 0)
    {
        sChessmine.clear();
    }
    sChessmine.resize(RowCount);
    for (i = 0;i < RowCount;i++)
    {
        sChessmine[i].resize(ColCount);
    }
    for (i = 0;i < RowCount ;i++)
    {
        for (j = 0;j < ColCount;j++)
        {
            sChessmine[i][j].bMineType = false;
            sChessmine[i][j].eGridType = GRID_NORMAL;
            sChessmine[i][j].bCheck    = false;
        }
    }
    srand((unsigned)time(NULL));
    i = 0;
    while (i < chessnum)
    {
        iMineCol = rand() % chessnum;
        if ((!sChessmine[i][iMineCol].bMineType) && !IfExistMineInCurrentCol(iMineCol))
        {
            sChessmine[i][iMineCol].bMineType = true;
            sChessmine[i][iMineCol].iMineNum  = -1;//Debug
            sChessmine[i][iMineCol].qPChessman.setX(hx1 + bw * i + 1);
            sChessmine[i][iMineCol].qPChessman.setY(hy1 + bh * iMineCol + 1);
            i++;
            iMinenum++;
        }
    }
    //Second step: put the remain mines
    while (iMinenum < minenum)
    {
        i = rand() % chessnum;
        j = rand() % chessnum;
        if (!sChessmine[i][j].bMineType)
        {
            sChessmine[i][j].bMineType = true;
            sChessmine[i][j].iMineNum  = -1;//Debug
            sChessmine[i][j].qPChessman.setX(hx1 + bw * i + 1);
            sChessmine[i][j].qPChessman.setY(hy1 + bh * j + 1);
            iMinenum++;
        }
    }
    //1 2 3
    //4 5 6
    //7 8 9
    for (i = 0;i < chessnum;i++)
    {
        for (j = 0;j < chessnum;j++)
        {
            if (!sChessmine[i][j].bMineType)
            {
                iMineCount = 0;
                if ((i == 0) && (j == 0))//1
                {
                    if (sChessmine[i][j + 1].bMineType)//2
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//4
                        iMineCount++;
                    if (sChessmine[i + 1][j + 1].bMineType)//5
                        iMineCount++;
                }
                else if ((i == 0) && (0 < j) && (j < chessnum - 1))//2
                {
                    if (sChessmine[i][j - 1].bMineType)//1
                        iMineCount++;
                    if (sChessmine[i][j + 1].bMineType)//3
                        iMineCount++;
                    if (sChessmine[i + 1][j - 1].bMineType)//4
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i + 1][j + 1].bMineType)//6
                        iMineCount++;
                }
                else if ((i == 0) && (j == chessnum - 1))//3
                {
                    if (sChessmine[i][j - 1].bMineType)//2
                        iMineCount++;
                    if (sChessmine[i + 1][j - 1].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//6
                        iMineCount++;
                }
                else if ((0 < i) && (i < chessnum - 1) && (j == 0))//4
                {
                    if (sChessmine[i - 1][j].bMineType)//1
                        iMineCount++;
                    if (sChessmine[i - 1][j + 1].bMineType)//2
                        iMineCount++;
                    if (sChessmine[i][j + 1].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i + 1][j + 1].bMineType)//8
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//7
                        iMineCount++;
                }
                else if ((0 < i) && (i < chessnum - 1) && (j == chessnum - 1))//6
                {
                    if (sChessmine[i - 1][j - 1].bMineType)//2
                        iMineCount++;
                    if (sChessmine[i - 1][j].bMineType)//3
                        iMineCount++;
                    if (sChessmine[i][j - 1].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i + 1][j - 1].bMineType)//8
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//9
                        iMineCount++;
                }
                else if ((i == chessnum - 1) && (j == 0))//7
                {
                    if (sChessmine[i - 1][j].bMineType)//4
                        iMineCount++;
                    if (sChessmine[i - 1][j + 1].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i][j + 1].bMineType)//8
                        iMineCount++;
                }
                else if ((i == chessnum - 1) && (0 < j) && (j < chessnum - 1))//8
                {
                    if (sChessmine[i - 1][j - 1].bMineType)//4
                        iMineCount++;
                    if (sChessmine[i - 1][j].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i - 1][j + 1].bMineType)//6
                        iMineCount++;
                    if (sChessmine[i][j - 1].bMineType)//7
                        iMineCount++;
                    if (sChessmine[i][j + 1].bMineType)//9
                        iMineCount++;
                }
                else if ((i == chessnum - 1) && (j == chessnum - 1))//9
                {
                    if (sChessmine[i - 1][j].bMineType)//6
                        iMineCount++;
                    if (sChessmine[i - 1][j - 1].bMineType)//5
                        iMineCount++;
                    if (sChessmine[i][j - 1].bMineType)//8
                        iMineCount++;
                }
                else//5
                {
                    if (sChessmine[i - 1][j - 1].bMineType)//1
                        iMineCount++;
                    if (sChessmine[i - 1][j].bMineType)//2
                        iMineCount++;
                    if (sChessmine[i - 1][j + 1].bMineType)//3
                        iMineCount++;
                    if (sChessmine[i][j - 1].bMineType)//4
                        iMineCount++;
                    if (sChessmine[i][j + 1].bMineType)//6
                        iMineCount++;
                    if (sChessmine[i + 1][j - 1].bMineType)//7
                        iMineCount++;
                    if (sChessmine[i + 1][j].bMineType)//8
                        iMineCount++;
                    if (sChessmine[i + 1][j + 1].bMineType)//9
                        iMineCount++;
                }
                sChessmine[i][j].iMineNum = iMineCount;
                sChessmine[i][j].qPChessman.setX(hx1 + bw * i + 1);
                sChessmine[i][j].qPChessman.setY(hy1 + bh * j + 1);
            }
        }
    }
    /////////////////////////////////////////
    SetMineNumber(iFindMineNumber);
    ClearTime();
    repaint();
}
