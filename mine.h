#ifndef MINE_H
#define MINE_H
class QTimer;
#include "mine_normal.h"

#include <QtWidgets/qwidget.h>
#include <QMouseEvent>
#include <QVector>

class MineField : public QWidget
{
    Q_OBJECT
public:
    MineField( QWidget *parent=0,CHESS_DIFFICULTY chess_level = Difficult_Easy,
               QString en="",QString cn="");

public slots:
    void NewGame(CHESS_DIFFICULTY chess_level = Difficult_Easy);
    void SetLanguage(int l);

private slots:

signals:
 void MineNumberValueChange(int iValue);
 void StartMineTimer();
 void StopMineTimer();
 void ClearMineTime();
protected:
     void  paintEvent( QPaintEvent * ) override;
     void  mousePressEvent( QMouseEvent * e) override;
     //void  mouseMoveEvent( QMouseEvent * );
     //void  mouseReleaseEvent( QMouseEvent * );

private:
     void InitChessman(CHESS_DIFFICULTY chess_level = Difficult_Easy);
     bool IfGameOver();
     bool IfExistMineInCurrentCol(int icol);
     bool GetChessNumber(int & iRow,int & iCol,const QPoint &point);
     void SetMines(int iRow,int iCol);
     void DrawMineNumber(int i,int j);
     void SetMineNumber(int iValue);
     void BeginMine();
     void MineOver();
     void ClearTime();
     //////
     int iFindMineNumber;//Find the mine number
     bool bMineDefeat;//true:mine defeat,display game over,false:game doesn't over,
     bool bStartMine;//true:begin mine,false:don't begin mine
     QString en_qm;
     QString cn_qm;
     CHESS_DIFFICULTY level;
     GAME_RESULT game_result;
     int iLanguage;
     int hx1;
     int hy1;
     int bh;
     int bw;
     int RowCount;
     int ColCount;
     int chessnum;
     int minenum;
     QString qClew;
     QVector<QVector<CHESSMANTYPE>> sChessmine;
};
#endif // MINE_H
