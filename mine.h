#ifndef MINE_H
#define MINE_H
class QTimer;

#include <QtWidgets/qwidget.h>
#include <QMouseEvent>
#include <QVector>

#define CHESSNUM_EASY 8
#define MINESNUM_EASY 10

#define CHESSNUM_MID 16
#define MINESNUM_MID 40


typedef enum
  {
    GRID_NORMAL,
    GRID_FLAG,
    GRID_INTERROGATION,
    GRID_CLICKOPEN,
    GRID_DEFEAT
  }GRIDTYPE;
typedef struct
{
  bool bMineType;//true:the grid has a mine,false:the grid hasn't a mine
  int iMineNum;//if the grid hasn't a mine,recore the number that around grid has mine.
  QPoint qPChessman;//the grid coordinate
  GRIDTYPE eGridType;//when people click the grid by mouse right button,record the grid type.
  bool bCheck;//true:Be checked by recursion,false :don't check by recursion
}CHESSMANTYPE;

typedef enum
{
    Difficult_Easy,
    Difficult_Middle
    //Difficult_Hard
}CHESS_DIFFICULTY;

typedef enum
{
    SUCCESS,
    FAIL,
    PROGRESSING
}GAME_RESULT;

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
