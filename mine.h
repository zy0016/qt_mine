#ifndef MINE_H
#define MINE_H
class QTimer;

#include <QtWidgets/qwidget.h>
#include <QMouseEvent>
#include <QVector>
//#define DIFF_PRIMARY
//#define DIFF_MIDDLE
//#define DIFF_ADVANCED

//#ifdef DIFF_PRIMARY
//#define CHESSNUM 8
//#define MINESNUM 10
//#define HX1                    100                                    //????????
//#define HY1                    3                                    //????????
//#define BH                    40                                    //???
//#define BW                    BH                                    //???
//#elif defined DIFF_MIDDLE
//#define CHESSNUM 16
//#define MINESNUM 40
//#define HX1                    50                                    //????????
//#define HY1                    3                                    //????????
//#define BH                    30                                    //???
//#define BW                    BH                                    //???
//#else
//#define CHESSNUM 40
//#define MINESNUM 100
//#define HX1                    5                                    //????????
//#define HY1                    3                                    //????????
//#define BH                    20                                    //???
//#define BW                    BH                                    //???
//#endif
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
  //bool bBroken;//true:the grid has been clicked by mouse left button,false:the grid hasn't been click by mouse left button
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
    MineField( QWidget *parent=0,CHESS_DIFFICULTY chess_level = Difficult_Easy);

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
     //bool bGameResult;//true:success,false:fail.
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
     //CHESSMANTYPE sChessmine[CHESSNUM][CHESSNUM];
     //CHESSMANTYPE sChessmine_easy[CHESSNUM_EASY][CHESSNUM_EASY];
     //CHESSMANTYPE sChessmine_mid[CHESSNUM_MID][CHESSNUM_MID];
};
#endif // MINE_H
